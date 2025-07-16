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

        private async Task<string> GenerateJwtToken(ApplicationUser user)
        {
            var claims = new List<Claim>
            {
                new Claim(JwtRegisteredClaimNames.Sub, user.Email),
                new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString()),
                new Claim(JwtRegisteredClaimNames.Email, user.Email),
                new Claim("id", user.Id)
            };

            var userRoles = await _userManager.GetRolesAsync(user);
            foreach(var userRole in userRoles)
            {
                claims.Add(new Claim(ClaimTypes.Role, userRole))
            }

            var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_configuration["Jwt:Key"]));
            var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);
            var expires = DateTime.Now.AddDays(Convert.ToDouble(_configuration["JWT:ExpireDays"]));

            var token = new JwtSecurityToken(
                _configuration["JWT:Issuer"],
                _configuration["JWT:Audience"],
                claims,
                expires: expires,
                signingCredentials: creds
            );

            return new JwtSecurityTokenHandler().WriteToken(token);
        }


        public async Task<AuthResult> LoginAsync(LoginDto request)
        {
            var user = await _userManager.FindByEmailAsync(request.Email);
            if (user == null)
            {
                return new AuthResult { Success = false, Errors = new[] { "invalid credentials." } }
            }
            ;

            var isPassValid = await _userManager.CheckPasswordAsync(user, request.Password);
            if (!isPassValid)
            {
                return new AuthResult { Success = false, Errors = new[] { "invalid credentials." } }
            }
            ;

            var token = await GenerateJwtToken(user);

            return new AuthResult
            {
                Success = true,
                Token = token,
                UserId = user.Id
            };
        }
    }