using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.User
{
    public class CreateCustomerDto
    {
        [Required]
        [EmailAddress]
        [MaxLength(100)]
        public string Email { get; set; }

        [Required]
        [MaxLength(50)]
        public string FirstName { get; set; }

        [Required]
        [MaxLength(50)]
        public string LastName { get; set; }

        [MaxLength(20)]
        public string? Phone { get; set; }

        [MaxLength(200)]
        public string? Address { get; set; }

        public DateTime? DateOfBirth { get; set; }

        public int? UserId { get; set; }
    }
} 