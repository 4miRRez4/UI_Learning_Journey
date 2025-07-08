using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IBookRepository
    {
        Task<List<Book>> GetAllBooksAsync();
        Task<Book> CreateBookAsync(Book book);
    }
}