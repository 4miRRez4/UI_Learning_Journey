using BookStore.Models;
using HotChocolate;
using HotChocolate.Types;

namespace BookStore.GraphQL.Types
{
    public class AuthorType : ObjectType<Author>
    {
        protected override void Configure(IObjectTypeDescriptor<Author> descriptor)
        {
            descriptor.Description("Represents an author of books");

            descriptor
                .Field(a => a.Books)
                .Description("Books written by this author")
                .UsePaging()
                .UseProjection()
                .UseFiltering()
                .UseSorting();
        }
    }
}