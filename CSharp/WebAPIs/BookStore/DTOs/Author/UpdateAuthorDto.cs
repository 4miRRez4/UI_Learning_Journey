using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.Author
{
    public class UpdateAuthorDto
    {
        [Required]
        [MaxLength(100)]
        public string Name { get; set; }

        public DateTime? BirthDate { get; set; }
    }
}