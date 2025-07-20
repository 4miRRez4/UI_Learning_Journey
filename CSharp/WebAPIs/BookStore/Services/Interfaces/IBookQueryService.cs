

namespace BookStore.Services.Interfaces
{
    public interface IBookQueryService
    {
        // GraphQL
        IQueryable<Book> GetAllBooksAsQueryable();

        IQueryable<Book> SearchBooksByTitle(string title);

        IQueryable<Book> GetBooksByGenre(string genre);
    }
}