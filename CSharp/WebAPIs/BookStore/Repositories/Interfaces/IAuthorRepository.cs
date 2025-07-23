using BookStore.Models;

namespace BookStore.Repositories.Interfaces
{
    public interface IAuthorRepository
    {
        Task<List<Author>> GetAllAuthorsAsync(CancellationToken ct);
        Task<Author?> GetAuthorByIdAsync(int id, CancellationToken ct);
        Task<List<Author>> GetAuthorsByIdsAsync(List<int> authorIds, CancellationToken ct);
    }
}
