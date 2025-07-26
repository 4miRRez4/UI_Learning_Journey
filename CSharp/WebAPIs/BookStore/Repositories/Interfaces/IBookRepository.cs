using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IBookRepository
    {
        Task<List<Book>> GetAllBooksAsync(bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<Book?> GetBookByIdAsync(int id, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<List<Book>> SearchBooksByTitleAsync(string title, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<Book> CreateBookAsync(Book book, CancellationToken ct = default);
        Task<Book?> UpdateBookAsync(Book book, CancellationToken ct = default);
        Task<bool> BookExistAsync(int id, CancellationToken ct = default);
        Task DeleteBookAsync(int id, CancellationToken ct = default);

        // GraphQL
        IQueryable<Book> GetAllBooksQueryable(bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        IQueryable<Book> SearchBooksByTitleQueryable(string title, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        IQueryable<Book> GetBooksByGenreQueryable(string genre, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
    }
}