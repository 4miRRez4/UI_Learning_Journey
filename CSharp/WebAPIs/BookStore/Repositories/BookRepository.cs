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

        private IQueryable<Book> ApplyIncludes(IQueryable<Book> query, bool includeAuthors = false, bool includeReviews = false)
        {
            if (includeAuthors)
                query = query.Include(b => b.Authors);
            
            if (includeReviews)
                query = query.Include(b => b.Reviews);
            
            return query;   
        }
        

        public async Task<List<Book>> GetAllBooksAsync(bool includeAuthors = false, bool includeReviews = false, CancellationToken ct = default)
        {
            try
            {
                var query = GetAllBooksQueryable(includeAuthors, includeReviews);
                return await query.ToListAsync(ct);
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        public async Task<Book?> GetBookByIdAsync(int id, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default)
        {
            try
            {
                var query = GetAllBooksQueryable(includeAuthor, includeReview);
                return await query.FirstOrDefaultAsync(b => b.Id == id, ct);
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        public async Task<List<Book>> SearchBooksByTitleAsync(string title, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default)
        {
            try
            {
                var query = GetAllBooksQueryable(includeAuthor, includeReview)
                    .Where(b => EF.Functions.Like(b.Title, $"%{title}%"))
                    .OrderBy(b => b.Title);
                return await query.ToListAsync(ct);
            }
            catch (Exception ex)
            {
                throw;
            }
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
            var bookEntity = await GetBookByIdAsync(id, false, false, ct);
            
            if (bookEntity != null)
            {
                _context.Books.Remove(bookEntity);
                await _context.SaveChangesAsync(ct);
            }
        }

        #region GraphQL Methods (IQueryable)
        public IQueryable<Book> GetAllBooksQueryable(bool includeAuthors = false, bool includeReviews = false, CancellationToken ct = default) 
            => ApplyIncludes(_context.Books.AsQueryable(), includeAuthors, includeReviews);

        public IQueryable<Book> SearchBooksByTitleQueryable(string title, bool includeAuthors = false, bool includeReviews = false, CancellationToken ct = default)
            => GetAllBooksQueryable(includeAuthors, includeReviews)
                .Where(b => EF.Functions.Like(b.Title, $"%{title}%"))
                .OrderBy(b => b.Title);

        public IQueryable<Book> GetBooksByGenreQueryable(string genre, bool includeAuthors = false, bool includeReviews = false, CancellationToken ct = default)
            => GetAllBooksQueryable(includeAuthors, includeReviews)
                .Where(b => b.Genre == genre)
                .OrderBy(b => b.Title);
        #endregion

    }
}