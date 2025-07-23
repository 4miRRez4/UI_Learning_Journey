using BookStore.Repositories.Interfaces;
using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;

namespace BookStore.Repositories
{
    public class BookRepository : IBookRepository
    {
        private readonly AppDbContext _context;

        public BookRepository(AppDbContext context)
        {
            _context = context;
        }

        public IQueryable<Book> GetAllBooksAsQueryable()
            => _context.Books
                .Include(b => b.Authors);

        public async Task<List<Book>> GetAllBooksAsync(CancellationToken ct)
        {
            return await GetAllBooksAsQueryable()
                .ToListAsync(ct);
        }

        public async Task<Book?> GetBookByIdAsync(int id, CancellationToken ct)
        {
            return await GetAllBooksAsQueryable()
                .FirstOrDefaultAsync(b => b.Id == id, ct);
        }

        public async Task<List<Book>> SearchBooksByTitleAsync(string title, CancellationToken ct)
        {
            return await _context.Books
                .Include(b => b.Authors)
                .Where(b => EF.Functions.Like(b.Title, $"%{title}%"))
                .OrderBy(b => b.Title)
                .ToListAsync(ct);
        }

        public async Task<Book> CreateBookAsync(Book book, CancellationToken ct)
        {
            await _context.Books.AddAsync(book, ct);
            await _context.SaveChangesAsync(ct);
            return book;
        }

        public async Task<Book?> UpdateBookAsync(Book book, CancellationToken ct)
        {
            await _context.SaveChangesAsync(ct);
            return book;
        }

        public async Task<bool> BookExistAsync(int id, CancellationToken ct)
        {
            return await _context.Books.AnyAsync(b => b.Id == id, ct);
        }

        public async Task DeleteBookAsync(int id, CancellationToken ct)
        {
            var bookEntity = await _context.Books
                .Include(b => b.Authors)
                .FirstOrDefaultAsync(b => b.Id == id, ct);
            
            if (bookEntity != null)
            {
                _context.Books.Remove(bookEntity);
                await _context.SaveChangesAsync(ct);
            }
        }



    }
}