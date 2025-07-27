using BookStore.Models;
using BookStore.Data;
using HotChocolate;
using HotChocolate.Data;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;

namespace BookStore.GraphQL.Queries
{
    [ExtendObjectType(OperationTypeNames.Query)]
    public class AuthorQueries
    {
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Author> GetAuthors(
            [Service] AppDbContext context,
            CancellationToken ct)
        {
            //TODO: write Service for Author and use here.
            return context.Authors;
        }
    }

}