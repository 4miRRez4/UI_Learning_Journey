using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.Review
{
    public class CreateReviewDto
    {
        [Required]
        [Range(1, 5)]
        public int Rating { get; set; }

        [MaxLength(1000)]
        public string? Comment { get; set; }

        [Required]
        public int BookId { get; set; }
    }
}