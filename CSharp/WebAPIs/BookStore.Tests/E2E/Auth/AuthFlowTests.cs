using BookStore.Data;
using BookStore.Tests.Builders;
using Microsoft.EntityFrameworkCore;
using System.Net;
using System.Net.Http.Headers;
using System.Net.Http.Json;
using System.Text.Json;
using FluentAssertions;
using Xunit;
using Microsoft.Extensions.DependencyInjection;
using BookStore.Dtos.Auth;

namespace BookStore.Tests.E2E.Auth
{
    public class AuthFlowTests : IClassFixture<TestWebApplicationFactory>
    {
        public const string RegisterEndpoint = "/api/auth/register";
        public const string LoginEndpoint = "/api/auth/login";
        private readonly TestWebApplicationFactory _factory;
        private readonly HttpClient _client;

        public AuthFlowTests(TestWebApplicationFactory factory)
        {
            _factory = factory;
            _client = factory.CreateClient();
        }

        [Fact]
        public async Task Auth_Journey_Register_Login_Access()
        {
            // Register 
            var registerRequest = new UserRegisterDtoBuilder()
                .WithUserName("testUserName")
                .WithEmail("e2e_test_user@test.com")
                .WithPassword("UserPassword123!")
                .Build();

            var registerResponse = await _client.PostAsJsonAsync(RegisterEndpoint, registerRequest);
            registerResponse.StatusCode.Should().Be(HttpStatusCode.OK);

            var registerResult = await registerResponse.Content.ReadFromJsonAsync<JsonElement>();
            var userId = registerResult.GetProperty("userId").GetString();

            // Login 
            var loginRequest = new LoginDto
            {
                Email = registerRequest.Email,
                Password = registerRequest.Password
            };

            var loginResponse = await _client.PostAsJsonAsync(LoginEndpoint, loginRequest);
            loginResponse.StatusCode.Should().Be(HttpStatusCode.OK);

            var loginResult = await loginResponse.Content.ReadFromJsonAsync<JsonElement>();
            var token = loginResult.GetProperty("token").GetString();

            // Access protected endpoint
            _client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);

            var protectedEndpoint = "/api/order/1";
            var protectedResponse = await _client.GetAsync(protectedEndpoint);
            protectedResponse.StatusCode.Should().Be(HttpStatusCode.NotFound);

            // Verify db change 
            using (var scope = _factory.Services.CreateScope())
            {
                var db = scope.ServiceProvider.GetRequiredService<TestAppDbContext>();
                var dbUser = await db.Users.FirstOrDefaultAsync(u => u.Email == registerRequest.Email);

                dbUser.Should().NotBeNull();
                dbUser.Email.Should().Be(registerRequest.Email);
                dbUser.Id.Should().Be(userId);
            }
        }
    }
}