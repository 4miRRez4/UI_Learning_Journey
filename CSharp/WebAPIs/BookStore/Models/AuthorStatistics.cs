
namespace BookStore.Models
{
    public class AuthorStatistics
    {
        public int AuthorId { get; set; }
        public string AuthorName { get; set; }  
        public int TotalBooks { get; set; }
        public int TotalReviews { get; set; }
        public double AverageRating { get; set; }
    }
}