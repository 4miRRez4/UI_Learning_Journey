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

        public async Task<List<Author>> GetAllAuthorsAsync()
        {
            return await _context.Authors
                                .Include(b => b.Books)
                                .AsNoTracking()
                                .ToListAsync();
        }

        public async Task<Author?> GetAuthorByIdAsync(int id)
        {
            return await _context.Authors.FindAsync(id);
        }

        public async Task<List<Author>> GetAuthorsByIdsAsync(List<int> authorIds)
        {
            return await _context.Authors
                                 .Where(a => authorIds.Distinct().Contains(a.Id))
                                 .ToListAsync();
        }

    }
}