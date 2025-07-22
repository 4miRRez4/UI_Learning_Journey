using BookStore.Models;
using BookStore.Data;
using HotChocolate;
using HotChocolate.Types;
using HotChocolate.Data;
using Microsoft.EntityFrameworkCore;

namespace BookStore.GraphQL.Types
{
    public class AuthorType : ObjectType<Author>
    {
        protected override void Configure(IObjectTypeDescriptor<Author> descriptor)
        {
            descriptor.Description("Represents an author of books");

            //TODO: delete or only use this manual configuration instead of [UseProjection]
            //descriptor
            //    .Field(a => a.Books)
            //    .Description("Books written by this author")
            //    .UsePaging()
            //    .UseProjection()
            //    .UseFiltering()
            //    .UseSorting();

        }
    }

    public class AuthorResolvers
    {
        // TODO: change this to return IQueryable. add more customre resolvers
        public async Task<IEnumerable<Book>> GetBooks([Parent] Author author, [Service] AppDbContext context, [Service] ILogger<AuthorResolvers> logger)
        {
            logger.LogInformation("Fetching books for author {AuthorId}", author.Id);

            var query = context.Authors
                .Where(a => a.Id == author.Id)
                .SelectMany(a => a.Books);


            var books = await query.AsNoTracking().ToListAsync();
            logger.LogInformation("Found {Count} books", books.Count);

            return books;
        }
    }
}