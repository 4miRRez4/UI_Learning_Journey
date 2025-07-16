using BookStore.Dtos.Auth;

namespace BookStore.Services.Interfaces
{
    public interface IAuthService
    {
        Task<AuthResult> RegisterAsync(RegisterDto request);
        Task<string> LoginAsync(LoginDto loginDto);
        Task<string> GenerateJwtToken(ApplicationUser user)
    }
}