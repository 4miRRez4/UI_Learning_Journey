using BookStore.Dtos.Book;
using BookStore.Models;
using BookStore.Services;
using BookStore.Tests.Builders;
using BookStore.Tests.Factories;
using Moq;
using FluentAssertions;
using static BookStore.Tests.Fixtures.BookServiceTests;
using Microsoft.Extensions.Logging;
using BookStore.Dtos.Author;
using Microsoft.AspNetCore.JsonPatch.Exceptions;
using Microsoft.AspNetCore.JsonPatch;
using Microsoft.AspNetCore.JsonPatch.Operations;

namespace BookStore.Tests.Unit.Services
{
    public class BookServiceTests : IClassFixture<BookServiceFixture>
    {
        private readonly BookServiceFixture _fixture;

        public BookServiceTests(BookServiceFixture fixture)
        {
            _fixture = fixture;
            _fixture.BookRepositoryMock.Reset();
            _fixture.AuthorRepositoryMock.Reset();
            _fixture.MapperMock.Reset();
        }

        #region GetAllBooksAsync Tests

        [Fact]
        public async Task GetAllBooksAsync_WithNoIncludes_ReturnsMappedBooks()
        {
            // Arrange
            var testBook = BookTestDataFactory.CreateBook(
                id: 1,
                title: "Clean Code",
                price: 39.99m,
                stockQuantity: 25);

            var expectedDto = new BookDtoBuilder()
                .WithId(1)
                .WithTitle("Clean Code")
                .WithPrice(39.99m)
                .WithStockQuantity(25)
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetAllBooksAsync(false, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book> { testBook });

            _fixture.MapperMock
                .Setup(x => x.Map<IEnumerable<BookDto>>(It.IsAny<IEnumerable<Book>>()))
                .Returns(new List<BookDto> { expectedDto });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.GetAllBooksAsync();

            // Assert
            result.Should().ContainSingle()
                .Which.Should().BeEquivalentTo(expectedDto);
            _fixture.BookRepositoryMock.Verify(
                x => x.GetAllBooksAsync(false, false, It.IsAny<CancellationToken>()),
                Times.Once);
        }

        [Fact]
        public async Task GetAllBooksAsync_WithAuthorsAndReviews_ReturnsBooksWithFullDetails()
        {
            // Arrange
            var testBook = BookTestDataFactory.CreateBook(
                includeAuthors: true,
                includeReviews: true);

            var expectedDto = new BookDtoBuilder()
                .WithDefaultValues()
                .WithAuthors(
                    BookTestDataFactory.CreateAuthorDto(),
                    BookTestDataFactory.CreateAuthorDto(2))
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetAllBooksAsync(true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book> { testBook });

            _fixture.MapperMock
                .Setup(x => x.Map<IEnumerable<BookDto>>(It.IsAny<IEnumerable<Book>>()))
                .Returns(new List<BookDto> { expectedDto });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.GetAllBooksAsync(includeAuthors: true, includeReviews: true);

            // Assert
            result.First().Authors.Should().HaveCount(2);
            _fixture.BookRepositoryMock.Verify(
                x => x.GetAllBooksAsync(true, true, It.IsAny<CancellationToken>()),
                Times.Once);
        }

        [Fact]
        public async Task GetAllBooksAsync_WhenRepositoryThrows_LogsAndRethrows()
        {
            // Arrange
            var expectedException = new Exception("Database connection failed");

            _fixture.BookRepositoryMock
                .Setup(x => x.GetAllBooksAsync(It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ThrowsAsync(expectedException);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act & Assert
            await Assert.ThrowsAsync<Exception>(() => service.GetAllBooksAsync());

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Error,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) => o.ToString() == "Error getting all books"),
                    expectedException,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        #endregion

        #region GetBookByIdAsync Tests

        [Fact]
        public async Task GetBookByIdAsync_WithFullDetails_ReturnsCompleteBookDto()
        {
            // Arrange
            var testBook = BookTestDataFactory.CreateBook(
                id: 5,
                title: "Domain-Driven Design",
                description: "About DDD principles",
                includeAuthors: true);

            var expectedDto = new BookDtoBuilder()
                .WithId(5)
                .WithTitle("Domain-Driven Design")
                .WithDescription("About DDD principles")
                .WithAuthors(BookTestDataFactory.CreateAuthorDto())
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(5, true, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(testBook);

            _fixture.MapperMock
                .Setup(x => x.Map<BookDto>(testBook))
                .Returns(expectedDto);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.GetBookByIdAsync(5, includeAuthor: true);

            // Assert
            result.Should().BeEquivalentTo(expectedDto);
            result.Authors.Should().ContainSingle();
        }

        [Fact]
        public async Task GetBookByIdAsync_WithNonExistingId_ReturnsNullAndLogsWarning()
        {
            // Arrange
            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(999, It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync((Book)null);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.GetBookByIdAsync(999);

            // Assert
            result.Should().BeNull();
            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Warning,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) => o.ToString() == "Book with ID {BookId} not found"),
                    It.IsAny<Exception>(),
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Never);
        }

        #endregion

        #region CreateBookAsync Tests

        [Fact]
        public async Task CreateBookAsync_WithValidData_CreatesBookWithAuthors()
        {
            // Arrange
            var createDto = BookTestDataFactory.CreateValidCreateBookDto();
            var testAuthors = new List<Author>
            {
                BookTestDataFactory.CreateBook(includeAuthors: true).Authors.First()
            };

            var expectedBook = BookTestDataFactory.CreateBook(
                title: createDto.Title,
                description: createDto.Description,
                price: createDto.Price);

            var expectedDto = new BookDtoBuilder()
                .WithTitle(createDto.Title)
                .WithDescription(createDto.Description)
                .WithPrice(createDto.Price)
                .Build();

            _fixture.AuthorRepositoryMock
                .Setup(x => x.GetAuthorsByIdsAsync(createDto.AuthorIds, It.IsAny<CancellationToken>()))
                .ReturnsAsync(testAuthors);

            _fixture.MapperMock
                .Setup(x => x.Map<Book>(createDto))
                .Returns(expectedBook);

            _fixture.BookRepositoryMock
                .Setup(x => x.CreateBookAsync(expectedBook, It.IsAny<CancellationToken>()))
                .ReturnsAsync(expectedBook);

            _fixture.MapperMock
                .Setup(x => x.Map<BookDto>(expectedBook))
                .Returns(expectedDto);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.CreateBookAsync(createDto, CancellationToken.None);

            // Assert
            result.Should().BeEquivalentTo(expectedDto);
            expectedBook.Authors.Should().BeEquivalentTo(testAuthors);
            _fixture.BookRepositoryMock.Verify(
                x => x.CreateBookAsync(It.IsAny<Book>(), It.IsAny<CancellationToken>()),
                Times.Once);
        }

        [Fact]
        public async Task CreateBookAsync_WithInvalidAuthorIds_ThrowsAndLogsError()
        {
            // Arrange
            var createDto = BookTestDataFactory.CreateValidCreateBookDto();
            createDto.AuthorIds = new List<int> { 999 };

            var expectedBook = BookTestDataFactory.CreateBook(
                title: createDto.Title,
                description: createDto.Description,
                price: createDto.Price);

            _fixture.MapperMock
                .Setup(x => x.Map<Book>(createDto))
                .Returns(expectedBook);

            _fixture.AuthorRepositoryMock
                .Setup(x => x.GetAuthorsByIdsAsync(createDto.AuthorIds, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Author>()); 

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act & Assert
            var ex = await Assert.ThrowsAsync<Exception>(() =>
                service.CreateBookAsync(createDto, CancellationToken.None));

            ex.Message.Should().Be("No authors found with the provided IDs");

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Error,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) => o.ToString() == "Error creating book"),
                    ex,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        #endregion

        #region UpdateBookAsync Tests

        [Fact]
        public async Task UpdateBookAsync_WithValidChanges_UpdatesAllProperties()
        {
            // Arrange
            var originalBook = BookTestDataFactory.CreateBook(
                id: 1,
                title: "Original Title",
                price: 10.00m);

            var updateDto = BookTestDataFactory.CreateValidUpdateBookDto();
            updateDto.Title = "Updated Title";
            updateDto.Price = 20.00m;
            updateDto.AuthorIds = new List<int> { 1, 2 };

            var updatedAuthors = new List<Author>
            {
                new Author { Id = 1, Name = "Author One" },
                new Author { Id = 2, Name = "Author Two" }
            };

            var updatedBook = BookTestDataFactory.CreateBook(
                id: 1,
                title: "Updated Title",
                price: 20.00m);
            updatedBook.Authors = updatedAuthors;

            var expectedDto = new BookDtoBuilder()
                .WithId(1)
                .WithTitle("Updated Title")
                .WithPrice(20.00m)
                .WithAuthors(
                    new AuthorDto { Id = 1, Name = "Author One" },
                    new AuthorDto { Id = 2, Name = "Author Two" })
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(1, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.AuthorRepositoryMock
                .Setup(x => x.GetAuthorsByIdsAsync(updateDto.AuthorIds, It.IsAny<CancellationToken>()))
                .ReturnsAsync(updatedAuthors);

            _fixture.BookRepositoryMock
                .Setup(x => x.UpdateBookAsync(It.IsAny<Book>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync(updatedBook);

            _fixture.MapperMock
                .Setup(x => x.Map(updateDto, originalBook))
                .Callback<UpdateBookDto, Book>((dto, book) =>
                {
                    book.Title = dto.Title;
                    book.Price = dto.Price.Value;
                });

            _fixture.MapperMock
                .Setup(x => x.Map<BookDto>(updatedBook))
                .Returns(expectedDto);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.UpdateBookAsync(1, updateDto, CancellationToken.None);

            // Assert
            result.Should().BeEquivalentTo(expectedDto);
            _fixture.MapperMock.Verify(x => x.Map(updateDto, originalBook), Times.Once);
            _fixture.MapperMock.Verify(x => x.Map<BookDto>(updatedBook), Times.Once);
        }


        [Fact]
        public async Task UpdateBookAsync_WithNonExistingId_ReturnsNullAndLogsWarning()
        {
            // Arrange
            const int nonExistingId = 999;
            var updateDto = BookTestDataFactory.CreateValidUpdateBookDto();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(nonExistingId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync((Book)null);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.UpdateBookAsync(nonExistingId, updateDto, CancellationToken.None);

            // Assert
            result.Should().BeNull();

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Warning,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) =>
                        o.ToString().Contains($"There is no book with ID {nonExistingId} to update")),
                    null,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }
        #endregion

        #region DeleteBookAsync Tests

        [Fact]
        public async Task DeleteBookAsync_WithExistingId_ReturnsTrueAndDeletes()
        {
            // Arrange
            _fixture.BookRepositoryMock
                .Setup(x => x.BookExistAsync(1, It.IsAny<CancellationToken>()))
                .ReturnsAsync(true);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.DeleteBookAsync(1, CancellationToken.None);

            // Assert
            result.Should().BeTrue();
            _fixture.BookRepositoryMock.Verify(
                x => x.DeleteBookAsync(1, It.IsAny<CancellationToken>()),
                Times.Once);
        }

        [Fact]
        public async Task DeleteBookAsync_WithNonExistingId_ReturnsFalseAndLogsWarning()
        {
            // Arrange
            _fixture.BookRepositoryMock
                .Setup(x => x.BookExistAsync(999, It.IsAny<CancellationToken>()))
                .ReturnsAsync(false);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.DeleteBookAsync(999, CancellationToken.None);

            // Assert
            result.Should().BeFalse();
            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Warning,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) => o.ToString().Contains("There is no book with ID 999 to delete")),
                    null,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        #endregion

        #region SearchBooksByTitleAsync Tests

        [Fact]
        public async Task SearchBooksByTitleAsync_WithPartialMatch_ReturnsMatchingBooks()
        {
            // Arrange
            const string searchTerm = "code";
            var matchingBooks = new List<Book>
            {
                BookTestDataFactory.CreateBook(id: 1, title: "Clean Code", genre: "Programming"),
                BookTestDataFactory.CreateBook(id: 2, title: "Code Complete", genre: "Programming")
            };

            var expectedDtos = new List<BookDto>
            {
                new BookDtoBuilder().WithId(1).WithTitle("Clean Code").WithGenre("Programming").Build(),
                new BookDtoBuilder().WithId(2).WithTitle("Code Complete").WithGenre("Programming").Build()
            };

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, false, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(matchingBooks);

            _fixture.MapperMock
                .Setup(x => x.Map<List<BookDto>>(matchingBooks))
                .Returns(expectedDtos);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.SearchBooksByTitleAsync(searchTerm);

            // Assert
            result.Should().HaveCount(2)
                .And.Contain(b => b.Title.Contains(searchTerm, StringComparison.OrdinalIgnoreCase))
                .And.OnlyContain(b => b.Genre == "Programming");
        }

        [Fact]
        public async Task SearchBooksByTitleAsync_WithCaseInsensitiveMatch_ReturnsBooks()
        {
            // Arrange
            const string searchTerm = "deSiGn";
            var testBook = BookTestDataFactory.CreateBook(title: "Domain-Driven Design");
            var expectedDto = new BookDtoBuilder().WithTitle("Domain-Driven Design").Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, false, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book> { testBook });

            _fixture.MapperMock
                .Setup(x => x.Map<List<BookDto>>(It.IsAny<List<Book>>()))
                .Returns(new List<BookDto> { expectedDto });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.SearchBooksByTitleAsync(searchTerm);

            // Assert
            result.Should().ContainSingle()
                .Which.Title.Should().Be("Domain-Driven Design");
        }

        [Fact]
        public async Task SearchBooksByTitleAsync_WithSpecialCharacters_ReturnsBooks()
        {
            // Arrange
            const string searchTerm = "C#";
            var testBook = BookTestDataFactory.CreateBook(title: "Mastering C#");
            var expectedDto = new BookDtoBuilder().WithTitle("Mastering C#").Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, false, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book> { testBook });

            _fixture.MapperMock
                .Setup(x => x.Map<List<BookDto>>(It.IsAny<List<Book>>()))
                .Returns(new List<BookDto> { expectedDto });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.SearchBooksByTitleAsync(searchTerm);

            // Assert
            result.Should().ContainSingle()
                .Which.Title.Should().Be("Mastering C#");
        }

        [Fact]
        public async Task SearchBooksByTitleAsync_WithNoMatches_ReturnsEmptyList()
        {
            // Arrange
            const string searchTerm = "nonexistent";

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, false, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book>());

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.SearchBooksByTitleAsync(searchTerm);

            // Assert
            result.Should().BeNull();
            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Error,
                    It.IsAny<EventId>(),
                    It.IsAny<It.IsAnyType>(),
                    It.IsAny<Exception>(),
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Never);
        }

        [Fact]
        public async Task SearchBooksByTitleAsync_WithAuthors_ReturnsBooksWithAuthorDetails()
        {
            // Arrange
            const string searchTerm = "design";
            var testBook = BookTestDataFactory.CreateBook(
                title: "Design Patterns",
                includeAuthors: true);

            var expectedDto = new BookDtoBuilder()
                .WithTitle("Design Patterns")
                .WithAuthors(BookTestDataFactory.CreateAuthorDto())
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, true, false, It.IsAny<CancellationToken>()))
                .ReturnsAsync(new List<Book> { testBook });

            _fixture.MapperMock
                .Setup(x => x.Map<List<BookDto>>(It.IsAny<List<Book>>()))
                .Returns(new List<BookDto> { expectedDto });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.SearchBooksByTitleAsync(searchTerm, includeAuthor: true);

            // Assert
            result.Should().ContainSingle()
                .Which.Should().BeEquivalentTo(expectedDto);
            result.First().Authors.Should().ContainSingle();
        }

        [Fact]
        public async Task SearchBooksByTitleAsync_WhenRepositoryFails_LogsAndRethrows()
        {
            // Arrange
            const string searchTerm = "error";
            var expectedException = new Exception("Database error");

            _fixture.BookRepositoryMock
                .Setup(x => x.SearchBooksByTitleAsync(searchTerm, It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ThrowsAsync(expectedException);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act & Assert
            await Assert.ThrowsAsync<Exception>(() =>
                service.SearchBooksByTitleAsync(searchTerm));

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Error,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((state, type) =>
                        state.ToString() == $"Error searching books by title '{searchTerm}'"),
                    expectedException,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        #endregion
    }
}