using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;
using HotChocolate;
using HotChocolate.Data;
using HotChocolate.Types;

namespace BookStore.GraphQL.Queries
{
    [ExtendObjectType(OperationTypeNames.Query)]
    public class BookQuery
    {
        [UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooks([ScopedService] AppDbContext context)
            => context.Books
                .Include(b => b.Authors)
                .Include(b => b.Reviews)
                .AsNoTracking();


        [UseDbContext(typeof(AppDbContext))]
        public async Task<Book?> GetBookById(int id, [ScopedService] AppDbContext context)
            => context.Books
                .Include(b => b.Authors)
                .Include(b => b.Reviews)
                .AsNoTracking()
                .FirstOrDefaultAsync(b => b.Id == id);

        [UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> SearchBooksByTitle(string title, [ScopedService] AppDbContext context)
            => context.Books
                    .Include(b => b.Authors)
                    .Where(base => EF.Functions.Like(base.Title, $"%{title}%"))
                    .AsNoTracking();

        [UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooksByGenre(string genre, [ScopedService] AppDbContext context) 
            => context.Books
                .Include(b => b.Authors)
                .Where(b => b.Genre == genre)
                .AsNoTracking();


    }
}