using BookStore.Models;
using BookStore.Data;
using BookStore.GraphQL.Authors.DataLoaders;
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

            descriptor
                .Field("statistics")
                .Description("Statistics about the author's books")
                .ResolveWith<AuthorResolvers>(r => r.GetStatistics(default!, default!, default!))
                .Authorize();

        }
    }

    public class AuthorResolvers
    {
        public async Task<AuthorStatistics> GetStatistics(
            [Parent] Author author,
            [Service] AuthorStatsDataLoader dataLoader,
            CancellationToken ct)
        {
            return await dataLoader.LoadAsync(author.Id, ct);
        }
    }
}