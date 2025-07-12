using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;


namespace BookStore.Models
{
    public class Book
    {
        [Key]
        public int Id { get; set; }

        [Required]
        [MaxLength(200)]
        public string Title { get; set; }

        [Column(TypeName = "nvarchar(max)")]
        [MaxLength(500)]
        public string? Description { get; set; }

        public DateTime? PublishDate { get; set; }

        [MaxLength(50)]
        public string? Genre { get; set; }

        [Required]
        [Range(0, double.MaxValue, ErrorMessage = "Price must be a positive number")]
        public decimal Price { get; set; }

        [Required]
        [Range(0, int.MaxValue, ErrorMessage = "Stock quantity must be a non-negative number")]
        public int StockQuantity { get; set; }

        [MaxLength(100)]
        public string Publisher { get; set; }

        [MaxLength(50)]
        public string Language { get; set; }



        // navigation properties
        public ICollection<Author> Authors { get; set; } = new List<Author>();
        public ICollection<Review> Reviews { get; set; } = new List<Review>();
    }

}