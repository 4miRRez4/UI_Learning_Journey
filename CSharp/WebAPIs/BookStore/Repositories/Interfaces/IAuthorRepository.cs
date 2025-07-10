using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IAuthorRepository
    {
        Task<List<Author>> GetAllAuthorsAsync();
        Task<Author?> GetAuthorByIdAsync(int id);
        Task<List<Author>> GetAuthorsByIdsAsync(List<int> authorIds);
    }
}
