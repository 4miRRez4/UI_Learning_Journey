using BookStore.Models;
using BookStore.GraphQL.Types.Inputs;

namespace BookStore.Services.Interfaces
{
    public interface IBookQueryService
    {
        // GraphQL
        Task<IQueryable<Book>> GetAllBooksAsQueryable(CancellationToken ct);

        Task<IQueryable<Book>> SearchBooksByTitleAsQueryable(string title, CancellationToken ct);

        Task<IQueryable<Book>> GetBooksByGenreAsQueryable(string genre, CancellationToken ct);

        Task<IQueryable<Book>> GetFilteredBooks(BookSearchFilter filter, CancellationToken ct);
    }
}