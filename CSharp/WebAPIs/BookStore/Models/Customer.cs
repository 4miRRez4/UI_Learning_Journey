using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace BookStore.Models
{
    public class Customer
    {
        [Key]
        public int Id { get; set; }

        public int? UserId { get; set; }

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

        [Required]
        [MaxLength(10)]
        public string? Phone { get; set; }

        [Required]
        [MaxLength(200)]
        public string? Address { get; set; }

        public DateTime? DateOfBirth { get; set; }


        [ForeignKey("UserId")]
        public User? User { get; set; }


    }
}