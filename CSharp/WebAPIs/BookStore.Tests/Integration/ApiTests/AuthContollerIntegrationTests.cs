

using BookStore.Dtos.Auth;
using Microsoft.VisualStudio.TestPlatform.TestHost;
using Moq;
using FluentAssertions;
using System.Net.Http.Json;
using System.Net;
using System.Text.Json;
using Xunit.Abstractions;
using Microsoft.VisualStudio.TestPlatform.Utilities;
using Azure.Core;
using Microsoft.AspNetCore.Mvc;
using System.Text;

namespace BookStore.Tests.Integration.ApiTests
{
    public class AuthControllerIntegrationTests : ControllerTestBase
    {
        private const string RegisterEndpoint = "api/auth/register";
        private const string LoginEndpoint = "api/auth/login";

        public AuthControllerIntegrationTests(
            CustomWebApplicationFactory<Program> factory,
            ITestOutputHelper output)
            : base(factory, output)
        {
            
        }


        #region Register Tests

        [Fact]
        public async Task Register_WithValidRequest_ReturnsOkWithUserId()
        {
            // Arrange
            var request = new RegisterDto
            {
                UserName = "testuser",
                Email = "test@example.com",
                Password = "P@ssw0rd123",
                ConfirmPassword = "P@ssw0rd123"
            };

            var expectedUserId = Guid.NewGuid().ToString();
            var expectedCustomerId = 1;

            AuthServiceMock
                .Setup(x => x.RegisterAsync(
                    It.Is<RegisterDto>(r =>
                        r.UserName == request.UserName &&
                        r.Email == request.Email),
                    It.IsAny<CancellationToken>()))
                .ReturnsAsync(new AuthResult
                {
                    Success = true,
                    UserId = expectedUserId,
                    CustomerId = expectedCustomerId,
                    Roles = new List<string> { "Customer" }
                });

            // Act
            var response = await Client.PostAsJsonAsync(RegisterEndpoint, request);
            var requestContent = await response.Content.ReadAsStringAsync();
            Output.WriteLine($"Request: {JsonSerializer.Serialize(request)}");
            Output.WriteLine($"Response: {response.StatusCode} - {requestContent}");

            // Assert
            response.StatusCode.Should().Be(HttpStatusCode.OK);

            var responseBody = await response.Content.ReadFromJsonAsync<Dictionary<string, object>>();
            responseBody.Should().ContainKey("userId");
            Guid.Parse(responseBody["userId"].ToString()).Should().Be(expectedUserId);
        }

        [Fact]
        public async Task Register_WithNullRequest_ReturnsBadRequest()
        {
            // Arrange
            var request = new HttpRequestMessage(HttpMethod.Post, RegisterEndpoint)
            {
                Content = new StringContent("null", Encoding.UTF8, "application/json")
            };

            // Act
            var response = await Client.SendAsync(request);
            var content = await response.Content.ReadAsStringAsync();

            // Assert
            response.StatusCode.Should().Be(HttpStatusCode.BadRequest);
            content.Should().Contain("A non-empty request body is required");

            AuthServiceMock.Verify(x => x.RegisterAsync(
                It.IsAny<RegisterDto>(),
                It.IsAny<CancellationToken>()), Times.Never);
        }

        [Theory]
        [InlineData(null, "test@example.com", "Valid123!", "Valid123!", "Username")] // Missing username
        [InlineData("", "test@example.com", "Valid123!", "Valid123!", "Username")] // Empty username
        [InlineData("testuser", null, "Valid123!", "Valid123!", "Email")] // Missing email
        [InlineData("testuser", "", "Valid123!", "Valid123!", "Email")] // Empty email
        [InlineData("testuser", "invalid-email", "Valid123!", "Valid123!", "Email")] // Invalid email format
        [InlineData("testuser", "test@example.com", null, null, "Password")] // Missing password
        [InlineData("testuser", "test@example.com", "short", "short", "Password")] // Short password
        [InlineData("testuser", "test@example.com", "Valid123!", null, "ConfirmPassword")] // Missing confirmation
        [InlineData("testuser", "test@example.com", "Valid123!", "", "ConfirmPassword")] // Empty confirmation
        [InlineData("testuser", "test@example.com", "Valid123!", "Mismatch123", "ConfirmPassword")] // Mismatch
        public async Task Register_WithInvalidRequest_ReturnsProperErrorMessage(
            string username, string email, string password, string confirmPassword, string expectedErrorField)
        {
            // Arrange
            var request = new RegisterDto
            {
                UserName = username,
                Email = email,
                Password = password,
                ConfirmPassword = confirmPassword
            };

            var expectedError = expectedErrorField switch
            {
                "Email" when string.IsNullOrEmpty(email) => "Email is required",
                "Email" => "Invalid email format",
                "Password" when string.IsNullOrEmpty(password) => "Password is required",
                "Password" => "Password must be at least 8 characters",
                "ConfirmPassword" when string.IsNullOrEmpty(confirmPassword) => "Confirmation is required",
                "ConfirmPassword" => "Passwords don't match",
                "Username" when string.IsNullOrEmpty(username) => "Full name is required",
                "Username" => "Username is invalid",
                _ => $"{expectedErrorField} is invalid"
            };

            // Act
            var response = await Client.PostAsJsonAsync(RegisterEndpoint, request);

            // Assert
            response.StatusCode.Should().Be(HttpStatusCode.BadRequest);

            var problemDetails = await response.Content.ReadFromJsonAsync<ValidationProblemDetails>();
            problemDetails.Should().NotBeNull();

            var allErrors = problemDetails.Errors.Values.SelectMany(x => x).ToList();
            allErrors.Should().Contain(expectedError);
        }

        #endregion



    }
}
