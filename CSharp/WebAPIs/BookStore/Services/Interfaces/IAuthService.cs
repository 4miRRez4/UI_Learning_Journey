using BookStore.Dtos.Auth;
using BookStore.Models;

namespace BookStore.Services.Interfaces
{
    public interface IAuthService
    {
        Task<AuthResult> RegisterAsync(RegisterDto request);
        Task<AuthResult> LoginAsync(LoginDto loginDto);

    }
}