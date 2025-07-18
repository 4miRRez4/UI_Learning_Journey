using BookStore.Models;
using HotChocolate;
using HotChocolate.Types;

namespace BookStore.GraphQL.Types
{
    public class ReviewType : ObjectType<Review>
    {
        protected override void Configure(IObjectTypeDescriptor<Review> descriptor)
        {
            descriptor.Description("Represents a review for a book");

            descriptor
                .Field(r => r.User)
                .Description("The user who wrote this review")
                .UseProjection();
        }
    }
}