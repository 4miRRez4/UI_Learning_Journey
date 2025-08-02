using BookStore.Services.Interfaces;
using BookStore.Services;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using BookStore.Dtos.Auth;
using Microsoft.AspNetCore.Identity;
using System.IdentityModel.Tokens.Jwt;
using Microsoft.Extensions.Configuration;
using System.Security.Claims;
using Xunit;
using FluentAssertions;
using Moq;
using static BookStore.Tests.Fixtures.AuthServiceTests;
using BookStore.Tests.Factories;
using BookStore.Tests.Builders;

namespace BookStore.Tests.Unit.Services
{
    public class AuthServiceTests : IClassFixture<AuthServiceFixture>
    {
        private readonly AuthServiceFixture _fixture;

        public AuthServiceTests(AuthServiceFixture fixture)
        {
            _fixture = fixture;
            _fixture.UserManagerMock.Reset();
            _fixture.RoleManagerMock.Reset();
            _fixture.CustomerRepositoryMock.Reset();
        }

        #region RegisterAsync Tests

        [Fact]
        public async Task RegisterAsync_WithValidData_ReturnSuccessResult()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidRegisterDto();
            var ct = CancellationToken.None;
            var testUser = AuthTestDataFactory.CreateTestUser(request.UserName, request.Email);

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync((ApplicationUser)null);

            _fixture.UserManagerMock
                .Setup(x => x.CreateAsync(It.IsAny<ApplicationUser>(), request.Password))
                .ReturnsAsync(IdentityResult.Success);

            _fixture.UserManagerMock
                .Setup(x => x.AddToRoleAsync(It.IsAny<ApplicationUser>(), It.IsAny<string>()))
                .ReturnsAsync(IdentityResult.Success);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.RegisterAsync(request, ct);

            // Assert
            result.Should().NotBeNull();
            result.Success.Should().BeTrue();
            result.UserId.Should().NotBeNullOrEmpty();
            _fixture.CustomerRepositoryMock.Verify(
                x => x.CreateCustomerAsync(It.Is<Customer>(c =>
                    c.Email == request.Email &&
                    c.UserId == result.UserId),
                    ct),
                    Times.Once);
        }

        [Fact]
        public async Task RegisterAsync_WithExistingEmail_ReturnsFailureResult()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidRegisterDto();
            var existingUser = AuthTestDataFactory.CreateTestUser();

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync(existingUser);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.RegisterAsync(request, CancellationToken.None);

            // Assert
            var expectedResult = new AuthResultBuilder()
                .WithSuccess(false)
                .WithError("Email already in use.")
                .Build();

            result.Should().BeEquivalentTo(expectedResult);
            _fixture.UserManagerMock.Verify(
                x => x.CreateAsync(It.IsAny<ApplicationUser>(), It.IsAny<string>()),
                Times.Never);
        }

        [Fact]
        public async Task RegisterAsync_WithWeakPassword_ReturnsFailureResult()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidRegisterDto();
            var passwordErrors = new[] { "Password too short", "Password requires uppercase" };

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync((ApplicationUser)null);

            _fixture.UserManagerMock
                .Setup(x => x.CreateAsync(It.IsAny<ApplicationUser>(), request.Password))
                .ReturnsAsync(IdentityResult.Failed(passwordErrors.Select(e =>
                    new IdentityError { Description = e }).ToArray()));

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.RegisterAsync(request, CancellationToken.None);

            // Assert
            result.Should().NotBeNull();
            result.Success.Should().BeFalse();
            result.Errors.Should().Contain(passwordErrors);
            _fixture.CustomerRepositoryMock.Verify(
                x => x.CreateCustomerAsync(It.IsAny<Customer>(), It.IsAny<CancellationToken>()),
                Times.Never);
        }

        [Fact]
        public async Task RegisterAsync_WhenCancelled_ThrowsOperationCanceledException()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidRegisterDto();
            var cancellationToken = new CancellationToken(canceled: true);

            _fixture.UserManagerMock
                .Setup(x => x.CreateAsync(It.IsAny<ApplicationUser>(), It.IsAny<string>()))
                .ReturnsAsync(IdentityResult.Success);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act & Assert
            await Assert.ThrowsAsync<OperationCanceledException>(() =>
                authService.RegisterAsync(request, cancellationToken));
        }

        #endregion


        #region LoginAsync Tests

        [Fact]
        public async Task LoginAsync_WithValidCredentials_ReturnsSuccessResultWithToken()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidLoginDto();
            var testUser = AuthTestDataFactory.CreateTestUser(request.Email);

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync(testUser);

            _fixture.UserManagerMock
                .Setup(x => x.CheckPasswordAsync(testUser, request.Password))
                .ReturnsAsync(true);

            _fixture.UserManagerMock
                .Setup(x => x.GetRolesAsync(testUser))
                .ReturnsAsync(new List<string> { "Customer" });

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.LoginAsync(request, CancellationToken.None);

            // Assert
            result.Should().NotBeNull();
            result.Success.Should().BeTrue();
            result.Token.Should().NotBeNullOrEmpty();
            result.UserId.Should().Be(testUser.Id);

            var tokenHandler = new JwtSecurityTokenHandler();
            var token = tokenHandler.ReadJwtToken(result.Token);
            token.Claims.Should().Contain(c => c.Type == "email" && c.Value == testUser.Email);
        }

        [Fact]
        public async Task LoginAsync_WithInvalidEmail_ReturnsFailureResult()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidLoginDto();

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync((ApplicationUser)null);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.LoginAsync(request, CancellationToken.None);

            // Assert
            result.Should().NotBeNull();
            result.Success.Should().BeFalse();
            result.Errors.Should().Contain("invalid credentials.");
            result.Token.Should().BeNull();
        }

        [Fact]
        public async Task LoginAsync_WithInvalidPassword_ReturnsFailureResult()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidLoginDto();
            var testUser = AuthTestDataFactory.CreateTestUser(request.Email);

            _fixture.UserManagerMock
                .Setup(x => x.FindByEmailAsync(request.Email))
                .ReturnsAsync(testUser);

            _fixture.UserManagerMock
                .Setup(x => x.CheckPasswordAsync(testUser, request.Password))
                .ReturnsAsync(false);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act
            var result = await authService.LoginAsync(request, CancellationToken.None);

            // Assert
            result.Should().NotBeNull();
            result.Success.Should().BeFalse();
            result.Errors.Should().Contain("invalid credentials.");
            result.Token.Should().BeNull();
        }

        [Fact]
        public async Task LoginAsync_WhenCancelled_ThrowsOperationCanceledException()
        {
            // Arrange
            var request = AuthTestDataFactory.CreateValidLoginDto();
            var cancellationToken = new CancellationToken(canceled: true);

            var authService = new AuthService(
                _fixture.UserManagerMock.Object,
                _fixture.RoleManagerMock.Object,
                _fixture.ConfigurationMock.Object,
                _fixture.CustomerRepositoryMock.Object);

            // Act & Assert
            await Assert.ThrowsAsync<OperationCanceledException>(() =>
                authService.LoginAsync(request, cancellationToken));
        }

        #endregion
    }
}
