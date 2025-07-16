using System.IdenticalModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Microsoft.AspNetCore.Identity;
using Microsoft.IdentityModel.Tokens;
using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Dtos.Auth;
using BookStore.Authorization;


namespace BookStore.Services
{
    public class AuthService : IAuthService
    {
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly RoleManager<ApplicationRole> _roleManager;
        private readonly IConfiguration _configuration;

        public AuthService(
            UserManager<ApplicationUser> userManager,
            RoleManager<ApplicationRole> roleManager,
            IConfiguration configuration)
        {
            _userManager = userManager;
            _roleManager = roleManager;
            _configuration = configuration;
        }

        public async Task<AuthResult> RegisterAsync(RegisterDto request)
        {
            var existingUser = await _userManager.FindByEmailAsync(request.Email);
            if (existingUser != null)
            {
                return new AuthResult { success = false, Errors = new[] {"Email already in use." } };
            }

            var newUser = new ApplicationUser
            {
                Email = request.Email,
                UserName = request.UserName,
            };

            var createdUser = await _userManager.CreateAsync(newUser, request.Password);

            if (!createdUser.Succeeded)
            {
                return new AuthResult
                {
                    Success = false,
                    Errors = createdUser.Errors.Select(x => x.Description)
                };
            }

            //Assign custom role by default
            await _userManager.AddToRoleAsync(newUser, UserRoles.Customer);

            var customer = new Customer
            {
                UserId = newUser.Id,
                LastName = request.FullName,
                Email = request.Email
            };
            // TODO: make a CustomerService and Repository and use in here
            _context.Customer.Add(customer);
            await _context.SaveChangedAsync();

            return new AuthResult
            {
                Success = true, 
                UserId = newUser.Id ,
                CustomerId = customer.Id,
                Roles = new List<UserRole> { UserRole.Customer }
            };
        }





    }
}