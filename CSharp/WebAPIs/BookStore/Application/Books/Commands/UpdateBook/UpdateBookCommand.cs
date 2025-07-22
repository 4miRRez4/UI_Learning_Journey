using MediatR;
using BookStore.Models;

namespace BookStore.Application.Books.Commands
{
    public class UpdateBookCommand : IRequest<Book?>
    {
        public int Id { get; set; }
        public string? Title { get; set; }
        public string? Description { get; set; }
        public DateTime? PublishDate { get; set; }
        public string? Genre { get; set; }
        public decimal? Price { get; set; }
        public int? StockQuantity { get; set; }
        public string? Publisher { get; set; }
        public string? Language { get; set; }
        public List<int>? AuthorIds { get; set; }
    }
}