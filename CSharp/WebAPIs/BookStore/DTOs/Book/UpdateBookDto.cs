using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.Book
{
	public class UpdateBookDto
	{
		[MaxLength(100)]
		public string? Title { get; set; }

		[MaxLength(500)]
		public string? Description { get; set; }

		public DateTime? PublishDate { get; set; }

		[MaxLength(50)]
		public string? Genre { get; set; }

        [Range(0, double.MaxValue, ErrorMessage = "Price must be a positive number")]
        public decimal? Price { get; set; }

        [Range(0, int.MaxValue, ErrorMessage = "Stock quantity must be a non-negative number")]
        public int? StockQuantity { get; set; }

        [MaxLength(100)]
        public string? Publisher { get; set; }

        [MaxLength(50)]
        public string? Language { get; set; }

        public List<int>? AuthorIds { get; set; }


    }
}