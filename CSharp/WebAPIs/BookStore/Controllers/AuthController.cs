using Microsoft.AspNetCore.Mvc;
using BookStore.Dtos.Auth;
using BookStore.Services.Interfaces;

namespace BookStore.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AuthController : ControllerBase
    {
        private readonly IAuthService _authService;

        public AuthController(IAuthService authService)
        {
            _authService = authService;
        }

        [HttpPost("register")]
        public async Task<IActionResult> Register([FromBody] RegisterDto request)
        {
            if (request == null)
            {
                return BadRequest("Invalid registration request.");
            }

            var result = await _authService.RegisterAsync(request);
            if (!result.Success)
            {
                return BadRequest(new { Errors = result.Errors });
            }

            return Ok(new { UserId = result.UserId });
        }

        [HttpPost("login")]
        public async Task<IActionResult> Login([FromBody] LoginDto request)
        {
            var result = await _authService.LoginAsync(request);

            if (!result.Success)
            {
                return Unauthorized(new { Errors = result.Errors });
            }

            return Ok(new { Token = result.Token, UserId = result.UserId });
        }
    }
}