using BookStore.Models;
using BookStore.Data;
using BookStore.Repositories.Interfaces;
using Microsoft.EntityFrameworkCore;


namespace BookStore.Repositories
{
    public class AuthorRepository : IAuthorRepository
    {
        private readonly AppDbContext _context;

        public AuthorRepository (AppDbContext context)
        {
            _context = context;
        }

        public async Task<List<Author>> GetAllAuthorsAsync(CancellationToken ct)
        {
            return await _context.Authors
                                .Include(b => b.Books)
                                .AsNoTracking()
                                .ToListAsync(ct);
        }

        public async Task<Author?> GetAuthorByIdAsync(int id, CancellationToken ct)
        {
            return await _context.Authors.FindAsync(new object[] { id }, ct);
        }

        public async Task<List<Author>> GetAuthorsByIdsAsync(List<int> authorIds, CancellationToken ct)
        {
            return await _context.Authors
                                 .Where(a => authorIds.Distinct().Contains(a.Id))
                                 .ToListAsync(ct);
        }

    }
}