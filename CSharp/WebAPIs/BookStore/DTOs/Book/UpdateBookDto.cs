using System.ComponentModel.DataAnnotations;

namespace BookStore.Dtos.Book
{
	public class UpdateBookDto
	{
		[Required]
		[MaxLength(100)]
		public string Title { get; set; }

		[MaxLength(500)]
		public string? Description { get; set; }

		public DateTime? PublishDate { get; set; }

		[MaxLength(50)]
		public string? Genre { get; set; }
	}
}