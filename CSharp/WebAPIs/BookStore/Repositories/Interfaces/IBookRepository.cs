using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IBookRepository
    {
        IQueryable<Book> GetAllBooksAsQueryable();
        Task<List<Book>> GetAllBooksAsync(CancellationToken ct);
        Task<Book?> GetBookByIdAsync(int id, CancellationToken ct);
        Task<List<Book>> SearchBooksByTitleAsync(string title, CancellationToken ct);
        Task<Book> CreateBookAsync(Book book, CancellationToken ct);
        Task<Book?> UpdateBookAsync(Book book, CancellationToken ct);
        Task<bool> BookExistAsync(int id, CancellationToken ct);
        Task DeleteBookAsync(int id, CancellationToken ct);
    }
}