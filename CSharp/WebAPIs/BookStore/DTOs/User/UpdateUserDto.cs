using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.User
{
    public class UpdateUserDto
    {
        [MaxLength(50)]
        public string? Username { get; set; }

        [MinLength(6)]
        public string? Password { get; set; }

        public string? Role { get; set; }
    }
}