using BookStore.Dtos.Author;

namespace BookStore.Dtos.Book
{
    public class BookDto
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string? Description { get; set; }
        public DateTime? PublishDate { get; set; }
        public string? Genre { get; set; }
        public List<AuthorDto> Authors { get; set; } = new();
    }
}