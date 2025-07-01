namespace BookStore.Dtos.Review
{
    public class ReviewDto
    {
        public int Id { get; set; }
        public int Rating { get; set; }
        public string? Comment { get; set; }
        public DateTime CreatedAt { get; set; }
        public UserDto User { get; set; }
        public BookDto Book { get; set; }
    }
}