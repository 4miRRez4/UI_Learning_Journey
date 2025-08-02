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

        #region PatchBookAsync Tests

        [Fact]
        public async Task PatchBookAsync_WithTitleUpdate_UpdatesOnlyTitleAndTimestamps()
        {
            // Arrange
            const int bookId = 1;
            var originalBook = BookTestDataFactory.CreateBook(
                id: bookId,
                title: "Original Title",
                price: 19.99m,
                stockQuantity: 10);

            var patchDoc = new JsonPatchDocument<UpdateBookDto>();
            patchDoc.Replace(x => x.Title, "Updated Title");

            var expectedDto = new BookDtoBuilder()
                .WithId(bookId)
                .WithTitle("Updated Title")
                .WithPrice(19.99m)
                .WithStockQuantity(10)
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<UpdateBookDto>(originalBook))
                .Returns(new UpdateBookDto
                {
                    Title = originalBook.Title,
                    Price = originalBook.Price,
                    StockQuantity = originalBook.StockQuantity
                });


            _fixture.MapperMock
                .Setup(x => x.Map(It.IsAny<UpdateBookDto>(), originalBook))
                .Callback<UpdateBookDto, Book>((dto, book) =>
                {
                    if (dto.Title != null) book.Title = dto.Title;
                    book.UpdatedAt = DateTime.UtcNow;
                });

            _fixture.BookRepositoryMock
                .Setup(x => x.UpdateBookAsync(originalBook, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<BookDto>(originalBook))
                .Returns(expectedDto);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.PatchBookAsync(bookId, patchDoc, CancellationToken.None);

            // Assert
            result.Should().BeEquivalentTo(expectedDto);
            originalBook.Title.Should().Be("Updated Title");
            originalBook.UpdatedAt.Should().BeCloseTo(DateTime.UtcNow, TimeSpan.FromSeconds(1));

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Information,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((state, type) =>
                        state.ToString().Contains($"Book with ID {bookId} patched successfully")),
                    null,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        [Fact]
        public async Task PatchBookAsync_WithMultipleUpdates_AppliesAllChanges()
        {
            // Arrange
            const int bookId = 1;
            var originalBook = BookTestDataFactory.CreateBook(
                id: bookId,
                price: 19.99m,
                stockQuantity: 10);

            var patchDoc = new JsonPatchDocument<UpdateBookDto>();
            patchDoc.Replace(x => x.Price, 29.99m);
            patchDoc.Replace(x => x.StockQuantity, 5);
            patchDoc.Replace(x => x.Genre, "Updated Genre");

            var expectedDto = new BookDtoBuilder()
                .WithId(bookId)
                .WithPrice(29.99m)
                .WithStockQuantity(5)
                .WithGenre("Updated Genre")
                .Build();

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<UpdateBookDto>(originalBook))
                .Returns(new UpdateBookDto
                {
                    Price = originalBook.Price,
                    StockQuantity = originalBook.StockQuantity,
                    Genre = originalBook.Genre
                });

            _fixture.MapperMock
                .Setup(x => x.Map(It.IsAny<UpdateBookDto>(), originalBook))
                .Callback<UpdateBookDto, Book>((dto, book) =>
                {
                    if (dto.Price.HasValue) book.Price = dto.Price.Value;
                    if (dto.StockQuantity.HasValue) book.StockQuantity = dto.StockQuantity.Value;
                    if (dto.Genre != null) book.Genre = dto.Genre;
                    book.UpdatedAt = DateTime.UtcNow;
                });

            _fixture.BookRepositoryMock
                .Setup(x => x.UpdateBookAsync(originalBook, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<BookDto>(originalBook))
                .Returns(expectedDto);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.PatchBookAsync(bookId, patchDoc, CancellationToken.None);

            // Assert
            result.Should().BeEquivalentTo(expectedDto);
            originalBook.Price.Should().Be(29.99m);
            originalBook.StockQuantity.Should().Be(5);
            originalBook.Genre.Should().Be("Updated Genre");
            originalBook.UpdatedAt.Should().BeCloseTo(DateTime.UtcNow, TimeSpan.FromSeconds(1));
        }

        [Fact]
        public async Task PatchBookAsync_WithAuthorIdsUpdate_ReplacesAuthorsList()
        {
            // Arrange
            const int bookId = 1;
            var originalBook = BookTestDataFactory.CreateBook(
                id: bookId,
                includeAuthors: true);

            var patchDoc = new JsonPatchDocument<UpdateBookDto>();
            patchDoc.Replace(x => x.AuthorIds, new List<int> { 1, 2 });

            var updatedAuthors = new List<Author>
            {
                BookTestDataFactory.CreateAuthorDto(1).ToAuthor(),
                BookTestDataFactory.CreateAuthorDto(2).ToAuthor()
            };

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.AuthorRepositoryMock
                .Setup(x => x.GetAuthorsByIdsAsync(new List<int> { 1, 2 }, It.IsAny<CancellationToken>()))
                .ReturnsAsync(updatedAuthors);

            _fixture.BookRepositoryMock
                .Setup(x => x.UpdateBookAsync(originalBook, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<UpdateBookDto>(originalBook))
                .Returns(new UpdateBookDto { AuthorIds = new List<int> { originalBook.Authors.First().Id } });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.PatchBookAsync(bookId, patchDoc, CancellationToken.None);

            // Assert
            originalBook.Authors.Should().HaveCount(2)
                .And.Contain(a => a.Id == 1)
                .And.Contain(a => a.Id == 2);
        }

        [Fact]
        public async Task PatchBookAsync_WithInvalidData_ThrowsAndLogsWarning()
        {
            // Arrange
            const int bookId = 1;
            var originalBook = BookTestDataFactory.CreateBook(id: bookId);
            var patchDoc = new JsonPatchDocument<UpdateBookDto>();
            patchDoc.Replace(x => x.Title, new string('a', 201)); // Exceeds max length

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<UpdateBookDto>(originalBook))
                .Returns(new UpdateBookDto { Title = originalBook.Title });

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act & Assert
            await Assert.ThrowsAsync<ArgumentException>(() =>
                service.PatchBookAsync(bookId, patchDoc, CancellationToken.None));

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Warning,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((state, type) =>
                        state.ToString() == $"Invalid patch data for book with ID {bookId}"),
                    null, 
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        [Fact]
        public async Task PatchBookAsync_WithInvalidProperty_ThrowsJsonPatchException()
        {
            // Arrange
            const int bookId = 1;
            var originalBook = BookTestDataFactory.CreateBook(id: bookId);
            var patchDoc = new JsonPatchDocument<UpdateBookDto>();

            // Create an invalid operation directly
            patchDoc.Operations.Add(new Operation<UpdateBookDto>(
                "replace",
                "/nonexistent property", 
                null,
                "invalid value"));

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(originalBook);

            _fixture.MapperMock
                .Setup(x => x.Map<UpdateBookDto>(originalBook))
                .Returns(new UpdateBookDto());

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act & Assert
            var ex = await Assert.ThrowsAsync<ArgumentException>(() =>
                service.PatchBookAsync(bookId, patchDoc, CancellationToken.None));

            ex.Message.Should().Contain("invalid patch operation");

            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Error,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((o, t) => o.ToString().Contains("JSON patch error for book with ID")),
                    It.IsAny<JsonPatchException>(),
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        [Fact]
        public async Task PatchBookAsync_WithNonExistingBook_ReturnsNull()
        {
            // Arrange
            const int bookId = 999;
            var patchDoc = new JsonPatchDocument<UpdateBookDto>();
            patchDoc.Replace(x => x.Title, "New Title");

            _fixture.BookRepositoryMock
                .Setup(x => x.GetBookByIdAsync(bookId, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync((Book)null);

            var service = new BookService(
                _fixture.BookRepositoryMock.Object,
                _fixture.AuthorRepositoryMock.Object,
                _fixture.MapperMock.Object,
                _fixture.LoggerMock.Object);

            // Act
            var result = await service.PatchBookAsync(bookId, patchDoc, CancellationToken.None);

            // Assert
            result.Should().BeNull();
            _fixture.LoggerMock.Verify(
                x => x.Log(
                    LogLevel.Warning,
                    It.IsAny<EventId>(),
                    It.Is<It.IsAnyType>((state, type) =>
                        state.ToString() == $"There is no book with ID {bookId}"),
                    null,
                    It.IsAny<Func<It.IsAnyType, Exception, string>>()),
                Times.Once);
        }

        #endregion
    }
}