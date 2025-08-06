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
using Microsoft.EntityFrameworkCore.Storage;

namespace BookStore.Tests.Integration.DatabaseTests
{
    [Collection("Database")]
    public class BookRepositoryTests : IAsyncLifetime
    {
        private DatabaseFixture _fixture;
        private BookRepository _repository;

        public BookRepositoryTests()
        {
        }

        public async Task InitializeAsync()
        {
            _fixture = new DatabaseFixture(); //Todo: use Respown or Transaction instead of creating fresh db 
            await _fixture.InitializeAsync();

            _repository = new BookRepository(_fixture.DbContext);
        }

        public async Task DisposeAsync()
        {
            await _fixture.DisposeAsync();
        }


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

        #region Relationship Tests

        [Fact]
        public async Task CreateBookAsync_WithAuthors_ShouldCreateBookAuthorRelationships()
        {
            // Arrange
            var author = new Author { Name = "Existing Author" };
            _fixture.DbContext.Authors.Add(author);
            await _fixture.DbContext.SaveChangesAsync();

            var newBook = BookTestDataFactory.CreateBook();
            newBook.Authors = new List<Author> { author };

            // Act
            var createdBook = await _repository.CreateBookAsync(newBook, CancellationToken.None);

            // Assert
            var dbBook = await _fixture.DbContext.Books
                .Include(b => b.Authors)
                .FirstOrDefaultAsync(b => b.Id == createdBook.Id);

            dbBook.Authors.Should().HaveCount(1);
            dbBook.Authors.First().Name.Should().Be("Existing Author");
        }

        [Fact]
        public async Task GetAllBooksQueryable_WithIncludes_ShouldReturnProperlyLoadedEntities()
        {
            // Arrange
            var bookWithAuthor = BookTestDataFactory.CreateBook(includeAuthors: true);
            var bookWithReview = BookTestDataFactory.CreateBook(includeReviews: true);
            _fixture.DbContext.Books.AddRange(bookWithAuthor, bookWithReview);
            await _fixture.DbContext.SaveChangesAsync();

            // Act
            var booksWithAuthors = await _repository.GetAllBooksQueryable(includeAuthors: true).ToListAsync();
            var booksWithReviews = await _repository.GetAllBooksQueryable(includeReviews: true).ToListAsync();

            // Assert
            booksWithAuthors.Should().Contain(b => b.Authors != null && b.Authors.Any());
            booksWithReviews.Should().Contain(b => b.Reviews != null && b.Reviews.Any());
        }

        #endregion

        #region Query Tests

        [Theory]
        [InlineData("C#", 2)]
        [InlineData("Java", 1)]
        [InlineData("", 3)]
        public async Task SearchBooksByTitleAsync_ShouldReturnCorrectResults(string searchTerm, int expectedCount)
        {
            // Arrange
            _fixture.DbContext.Books.AddRange(
                BookTestDataFactory.CreateBook(title: "C# Programming"),
                BookTestDataFactory.CreateBook(title: "Advanced C#"),
                BookTestDataFactory.CreateBook(title: "JavaScript Basics")
            );
            await _fixture.DbContext.SaveChangesAsync();

            // Act
            var results = await _repository.SearchBooksByTitleAsync(searchTerm);

            // Assert
            results.Should().HaveCount(expectedCount);
            if (!string.IsNullOrEmpty(searchTerm))
            {
                results.Should().OnlyContain(b => b.Title.Contains(searchTerm));
            }
        }

        [Theory]
        [InlineData("Fantasy", 2)]
        [InlineData("Sci-Fi", 1)]
        [InlineData("Non-Existing", 0)]
        public async Task GetBooksByGenreQueryable_ShouldFilterCorrectly(string genre, int expectedCount)
        {
            // Arrange
            _fixture.DbContext.Books.AddRange(
                BookTestDataFactory.CreateBook(title: "Fantasy Book 1", genre: "Fantasy"),
                BookTestDataFactory.CreateBook(title: "Fantasy Book 2", genre: "Fantasy"),
                BookTestDataFactory.CreateBook(title: "Sci-Fi Book", genre: "Sci-Fi")
            );
            await _fixture.DbContext.SaveChangesAsync();

            // Act
            var query = _repository.GetBooksByGenreQueryable(genre);
            var results = await query.ToListAsync();

            // Assert
            results.Should().HaveCount(expectedCount);
            if (expectedCount > 0)
            {
                results.Should().OnlyContain(b => b.Genre == genre);
            }
        }

        #endregion

        #region Edge Cases

        [Theory]
        [InlineData(0)]
        [InlineData(-1)]
        public async Task GetBookByIdAsync_WithInvalidId_ShouldReturnNull(int invalidId)
        {
            // Act
            var result = await _repository.GetBookByIdAsync(invalidId);

            // Assert
            result.Should().BeNull();
        }

        [Fact]
        public async Task BookExistAsync_ShouldReturnCorrectResult()
        {
            // Arrange
            var existingBook = BookTestDataFactory.CreateBook();
            _fixture.DbContext.Books.Add(existingBook);
            await _fixture.DbContext.SaveChangesAsync();

            // Act & Assert
            (await _repository.BookExistAsync(existingBook.Id, CancellationToken.None)).Should().BeTrue();
            (await _repository.BookExistAsync(9999, CancellationToken.None)).Should().BeFalse();
        }

        #endregion

    }

}