using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.User
{
    public class CreateUserDto
    {
        [Required]
        [MaxLength(50)]
        public string Username { get; set; }

        [Required]
        [MinLength(6)]
        public string Password { get; set; }

    }
}