using BookStore.Data;
using BookStore.Models;
using BookStore.Repositories;
using BookStore.Tests.Fixtures;
using BookStore.Tests.Builders;
using BookStore.Tests.Factories;
using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using Testcontainers.MsSql;
using Xunit;

namespace BookStore.Tests.Integration.DatabaseTests
{
    [Collection("Database")]
    public class BookRepositoryTests : IAsyncLifetime
    {
        private readonly DatabaseFixture _fixture;
        private BookRepository _repository;

        public BookRepositoryTests(DatabaseFixture fixture)
        {
            _fixture = fixture;
        }

        public Task InitializeAsync()
        {
            _repository = new BookRepository(_fixture.DbContext);
            return Task.CompletedTask;
        }

        public Task DisposeAsync() => Task.CompletedTask;


        #region CRUD Tests

        [Fact]
        public async Task CreateBookAsync_ShouldAddBookToDatabase()
        {
            // Arrange
            var newBook = BookTestDataFactory.CreateBook();

            // Act
            var createdBook = await _repository.CreateBookAsync(newBook, CancellationToken.None);

            // Assert
            createdBook.Should().NotBeNull();
            createdBook.Id.Should().BeGreaterThan(0);

            var dbBook = await _fixture.DbContext.Books.FindAsync(createdBook.Id);
            dbBook.Should().NotBeNull();
            dbBook.Title.Should().Be(newBook.Title);
        }

        [Fact]
        public async Task GetBookByIdAsync_ShouldReturnNull_WhenNotExists()
        {
            // Act
            var result = await _repository.GetBookByIdAsync(9999);

            // Assert
            result.Should().BeNull();
        }

        [Fact]
        public async Task GetAllBooksAsync_ShouldReturnAllBooks()
        {
            // Arrange
            _fixture.DbContext.Books.AddRange(
                BookTestDataFactory.CreateBook(title: "first book"),
                BookTestDataFactory.CreateBook(title: "second book"),
                BookTestDataFactory.CreateBook(title: "third book")
                );
            _fixture.DbContext.SaveChanges();

            // Act
            var books = await _repository.GetAllBooksAsync();

            // Assert
            books.Should().NotBeNull();
            books.Should().HaveCount(3);
        }

        [Theory]
        [InlineData(true, false)]
        [InlineData(false, true)]
        [InlineData(true, true)]
        public async Task GetBookByIdAsync_ShouldReturnBook_WithRequestedIncludes(bool includeAuthors, bool includeReviews)
        {
            // Arrange
            var testBook = BookTestDataFactory.CreateBook(includeAuthors: includeAuthors, includeReviews: includeReviews);
            _fixture.DbContext.Books.Add(testBook);
            await _fixture.DbContext.SaveChangesAsync();

            // Act
            var result = await _repository.GetBookByIdAsync(testBook.Id, includeAuthors, includeReviews);

            // Assert
            result.Should().NotBeNull();
            result.Id.Should().Be(testBook.Id);

            if (includeAuthors)
                result.Authors.Should().NotBeEmpty();
            else
                result.Authors.Should().BeEmpty();

            if (includeReviews)
                result.Reviews.Should().NotBeEmpty();
            else
                result.Reviews.Should().BeEmpty();
        }

        [Fact]
        public async Task UpdateBookAsync_ShouldModifyExistingBook()
        {
            // Arrange
            var originalBook = BookTestDataFactory.CreateBook();
            _fixture.DbContext.Books.Add(originalBook);
            await _fixture.DbContext.SaveChangesAsync();

            var updatedBook = originalBook;
            updatedBook.Title = "Updated Title";

            // Act
            var result = await _repository.UpdateBookAsync(updatedBook, CancellationToken.None);

            // Assert
            result.Should().NotBeNull();
            result.Title.Should().Be("Updated Title");

            var dbBook = await _fixture.DbContext.Books.FindAsync(originalBook.Id);
            dbBook.Title.Should().Be("Updated Title");
        }

        [Fact]
        public async Task DeleteBookAsync_ShouldRemoveBookFromDatabase()
        {
            // Arrange
            var bookToDelete = BookTestDataFactory.CreateBook();
            _fixture.DbContext.Books.Add(bookToDelete);
            await _fixture.DbContext.SaveChangesAsync();

            // Act
            await _repository.DeleteBookAsync(bookToDelete.Id, CancellationToken.None);

            // Assert
            var dbBook = await _fixture.DbContext.Books.FindAsync(bookToDelete.Id);
            dbBook.Should().BeNull();
        }

        #endregion

    }

}