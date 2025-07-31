
using BookStore.Dtos.Auth;
using BookStore.Models;

namespace BookStore.Tests.Factories
{
    public static class AuthTestDataFactory
    {
        public static RegisterDto CreateValidRegisterDto() => new RegisterDto
        {
            UserName = "TestUser",
            Email = "TestUser@test.com",
            Password = "TestPassword123",
            ConfirmPassword = "TestPassword123"
        };

        public static LoginDto CreateValidLoginDto() => new LoginDto
        {
            Email = "test@example.com",
            Password = "ValidPassword123!"
        };

        public static ApplicationUser CreateTestUser(string email = "TestUser@test.com", string userName = "TestUser")
        => new ApplicationUser
        {
            Id = Guid.NewGuid().ToString(),
            Email = email,
            UserName = userName
        };

    }
}
