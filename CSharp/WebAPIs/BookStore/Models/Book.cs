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

        [MaxLength(500)]
        public string? Description;

        public DateTime? PublishDate { get; set; }

        [MaxLength(50)]
        public string? Genre { get; set; }

        // navigation properties
        public ICollection<Author> Authors { get; set; } = new List<Author>();
        public ICollection<Review> Reviews { get; set; } = new List<Review>();
    }

}