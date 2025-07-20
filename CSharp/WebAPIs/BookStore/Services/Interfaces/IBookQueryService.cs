using BookStore.Models;
using BookStore.GraphQL.Types.Inputs;

namespace BookStore.Services.Interfaces
{
    public interface IBookQueryService
    {
        // GraphQL
        IQueryable<Book> GetAllBooksAsQueryable();

        IQueryable<Book> SearchBooksByTitleAsQueryable(string title);

        IQueryable<Book> GetBooksByGenreAsQueryable(string genre);

        IQueryable<Book> GetFilteredBooks(BookSearchFilter filter);
    }
}