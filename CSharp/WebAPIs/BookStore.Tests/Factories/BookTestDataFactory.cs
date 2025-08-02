using BookStore.Dtos.Author;
using BookStore.Dtos.Book;
using BookStore.Models;

namespace BookStore.Tests.Factories
{
    public static class BookTestDataFactory
    {
        public static Book CreateBook(
            int id = 1,
            string title = "Test Book",
            string? description = "Test Description",
            DateTime? publishDate = null,
            string? genre = "Fiction",
            decimal price = 9.99m,
            int stockQuantity = 10,
            string? publisher = "Test Publisher",
            string? language = "English",
            bool includeAuthors = false,
            bool includeReviews = false)
        {
            var book = new Book
            {
                Id = id,
                Title = title,
                Description = description,
                PublishDate = publishDate ?? new DateTime(2020, 1, 1),
                Genre = genre,
                Price = price,
                StockQuantity = stockQuantity,
                Publisher = publisher,
                Language = language,
                CreatedAt = DateTime.UtcNow.AddDays(-1),
                UpdatedAt = DateTime.UtcNow
            };

            if (includeAuthors)
            {
                book.Authors = new List<Author>
                {
                    new Author
                    {
                        Id = 1,
                        Name = "Test Author",
                        BirthDate = new DateTime(1980, 1, 1)
                    }
                };
            }

            if (includeReviews)
            {
                book.Reviews = new List<Review>
                {
                    new Review
                    {
                        Id = 1,
                        Rating = 5,
                        Comment = "Great book!",
                        CreatedAt = DateTime.UtcNow
                    }
                };
            }

            return book;
        }

        public static CreateBookDto CreateValidCreateBookDto() => new()
        {
            Title = "New Book",
            Description = "New Description",
            PublishDate = new DateTime(2023, 1, 1),
            Genre = "Non-Fiction",
            Price = 19.99m,
            StockQuantity = 5,
            Publisher = "New Publisher",
            Language = "English",
            AuthorIds = new List<int> { 1 }
        };

        public static UpdateBookDto CreateValidUpdateBookDto() => new()
        {
            Title = "Updated Book",
            Description = "Updated Description",
            PublishDate = new DateTime(2023, 6, 1),
            Genre = "Updated Genre",
            Price = 29.99m,
            StockQuantity = 15,
            Publisher = "Updated Publisher",
            Language = "Spanish",
            AuthorIds = new List<int> { 1, 2 }
        };

        public static AuthorDto CreateAuthorDto(int id = 1) => new()
        {
            Id = id,
            Name = $"Author {id}",
            BirthDate = new DateTime(1970 + id, 1, 1)
        };
    }
}
