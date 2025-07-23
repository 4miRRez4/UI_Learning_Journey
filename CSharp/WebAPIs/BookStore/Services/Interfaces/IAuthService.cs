using BookStore.Dtos.Auth;
using BookStore.Models;

namespace BookStore.Services.Interfaces
{
    public interface IAuthService
    {
        Task<AuthResult> RegisterAsync(RegisterDto request, CancellationToken ct);
        Task<AuthResult> LoginAsync(LoginDto loginDto, CancellationToken ct);

    }
}