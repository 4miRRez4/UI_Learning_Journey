using System.ComponentModel.DataAnnotations;

namespace BookStore.Application.Books.Commands
{
    public class AddBookCommand
    {
        [Required(ErrorMessage = "Title is required")]
        [MaxLength(200, ErrorMessage = "Title cannot exceed 200 characters")]
        public string Title { get; set; }

        [MaxLength(500, ErrorMessage = "Description cannot exceed 500 characters")]
        public string? Description { get; set; }

        public DateTime? PublishDate { get; set; }

        [MaxLength(50, ErrorMessage = "Genre cannot exceed 50 characters")]
        public string? Genre { get; set; }

        [Required(ErrorMessage = "Price is required")]
        [Range(0, double.MaxValue, ErrorMessage = "Price must be positive")]
        public decimal Price { get; set; }

        [Required(ErrorMessage = "Stock quantity is required")]
        [Range(0, int.MaxValue, ErrorMessage = "Stock quantity cannot be negative")]
        public int StockQuantity { get; set; }

        [MaxLength(100, ErrorMessage = "Publisher cannot exceed 100 characters")]
        public string? Publisher { get; set; }

        [MaxLength(50, ErrorMessage = "Language cannot exceed 50 characters")]
        public string? Language { get; set; }

        public List<int>? AuthorIds { get; set; }
    }
}