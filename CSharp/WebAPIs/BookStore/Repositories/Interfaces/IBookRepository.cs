using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IBookRepository
    {
        Task<List<Book>> GetAllBooksAsync();
        Task<Book?> GetBookByIdAsync(int id);
        Task<Book> CreateBookAsync(Book book);
        Task<Book?> UpdateBookAsync(Book book);
        Task<bool> BookExistAsync(int id);
        Task DeleteBookAsync(int id);
    }
}