using BookStore.Models;
using BookStore.Data;
using HotChocolate;
using HotChocolate.Types;
using HotChocolate.Data;
using Microsoft.EntityFrameworkCore;

namespace BookStore.GraphQL.Types
{
    public class BookType : ObjectType<Book>
    {
        protected override void Configure(IObjectTypeDescriptor<Book> descriptor)
        {
            descriptor.Description("Represents a book in the bookstore.");

            descriptor.Field(b => b.Id).Description("The unique identifier for the book.");
            descriptor.Field(b => b.Title).Description("The title of the book.");
            descriptor.Field(b => b.Description).Description("A summary of the book's content.");
            descriptor.Field(b => b.PublishDate).Description("The date the book was published.");
            descriptor.Field(b => b.Genre).Description("The genre of the book.");
            descriptor.Field(b => b.Price).Description("The price of the book.");

            descriptor
                .Field(b => b.Reviews)
                .Description("Reviews for this book")
                .UseFiltering()
                .UseSorting();

            descriptor
                .Field("averageRating")
                .Description("The average rating of the book")
                .ResolveWith<BookResolvers>(r => r.GetAverageRating(default!, default!))
                .Type<FloatType>();

        }
    }

    public class BookResolvers
    {
        public double? GetAverageRating([Parent] Book book, [Service] AppDbContext context)
        {
            return context.Books
                .Where(r => r.Id == book.Id)
                .SelectMany(b => b.Reviews)
                .Average(r => (double?)r.Rating);
        }

    }
}
