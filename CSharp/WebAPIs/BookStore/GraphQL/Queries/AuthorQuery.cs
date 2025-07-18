using BookStore.Models;
using BookStore.Data;
using HotChocolate;
using HotChocolate.Data;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;

namespace BookStore.GraphQL.Queries
{
    [ExtendObjectType(OperationTypeNames.Query)]
    public class AuthorQuery
    {
        [UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Author> GetAuthors([ScopedService] AppDbContext context) =>
            context.Authors
                .Include(a => a.Books)
                .AsNoTracking();

        [UseDbContext(typeof(AppDbContext))]
        public async Task<Author?> GetAuthorById(
            [ScopedService] AppDbContext context,
            int id) =>
            await context.Authors
                .Include(a => a.Books)
                .FirstOrDefaultAsync(a => a.Id == id);
    }
}