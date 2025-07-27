using AutoMapper;
using BookStore.Dtos.Book;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using BookStore.Services;
using BookStore.Services.Interfaces;
using Moq;
using Xunit;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;

namespace BookStore.Tests.Unit.Services
{
    public class BookServiceTests
    {
        private readonly Mock<IBookRepository> _mockBookRepository;
        private readonly Mock<IAuthorRepository> _mockAuthorRepository;
        private readonly Mock<IMapper> _mockMapper;
        private readonly Mock<ILogger<BookService>> _mockLogger;
        private readonly BookService _bookService;

        public BookServiceTests()
        {
            _mockBookRepository = new Mock<IBookRepository>();
            _mockAuthorRepository = new Mock<IAuthorRepository>();
            _mockMapper = new Mock<IMapper>();
            _mockLogger = new Mock<ILogger<BookService>>();

            _bookService = new BookService(
                _mockBookRepository.Object,
                _mockAuthorRepository.Object,
                _mockMapper.Object,
                _mockLogger.Object);
        }

        #region GetAllBooksAsync Tests
        [Fact]
        public async Task GetAllBooksAsync_ReturnsMappedBooks()
        {
            // Arrange
            var books = new List<Book> { new Book { Id = 1 }, new Book { Id = 2 } };
            var bookDtos = new List<BookDto> { new BookDto { Id = 1 }, new BookDto { Id = 2 } };

            _mockBookRepository.Setup(x => x.GetAllBooksAsync(It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync(books);

            _mockMapper.Setup(x => x.Map<IEnumerable<BookDto>>(books))
                .Returns(bookDtos);

            // Act
            var result = await _bookService.GetAllBooksAsync();

            // Assert
            Assert.Equal(2, result.Count());
            _mockBookRepository.Verify(x => x.GetAllBooksAsync(false, false, It.IsAny<CancellationToken>()), Times.Once);
        }
        #endregion

        #region GetBookByIdAsync Tests
        [Fact]
        public async Task GetBookByIdAsync_BookExists_ReturnsMappedBook()
        {
            // Arrange
            var book = new Book { Id = 1 };
            var bookDto = new BookDto { Id = 1 };

            _mockBookRepository.Setup(x => x.GetBookByIdAsync(1, It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync(book);

            _mockMapper.Setup(x => x.Map<BookDto>(book))
                .Returns(bookDto);

            // Act
            var result = await _bookService.GetBookByIdAsync(1);

            // Assert
            Assert.NotNull(result);
            Assert.Equal(1, result.Id);
        }

        [Fact]
        public async Task GetBookByIdAsync_BookDoesNotExist_ReturnsNull()
        {
            // Arrange
            _mockBookRepository.Setup(x => x.GetBookByIdAsync(1, It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync((Book)null);

            // Act
            var result = await _bookService.GetBookByIdAsync(1);

            // Assert
            Assert.Null(result);
        }
        #endregion

        #region CreateBookAsync Tests
        [Fact]
        public async Task CreateBookAsync_ValidData_CreatesAndReturnsBook()
        {
            // Arrange
            var createDto = new CreateBookDto
            {
                Title = "Test Book",
                Price = 9.99m,
                StockQuantity = 10,
                AuthorIds = new List<int> { 1, 2 }
            };

            var bookEntity = new Book { Id = 1 };
            var authors = new List<Author> { new Author { Id = 1 }, new Author { Id = 2 } };
            var bookDto = new BookDto { Id = 1 };

            _mockMapper.Setup(x => x.Map<Book>(createDto))
                .Returns(bookEntity);

            _mockAuthorRepository.Setup(x => x.GetAuthorsByIdsAsync(createDto.AuthorIds, It.IsAny<CancellationToken>()))
                .ReturnsAsync(authors);

            _mockBookRepository.Setup(x => x.CreateBookAsync(bookEntity, It.IsAny<CancellationToken>()))
                .ReturnsAsync(bookEntity);

            _mockMapper.Setup(x => x.Map<BookDto>(bookEntity))
                .Returns(bookDto);

            // Act
            var result = await _bookService.CreateBookAsync(createDto, CancellationToken.None);

            // Assert
            Assert.NotNull(result);
            Assert.Equal(1, result.Id);
            Assert.Equal(2, bookEntity.Authors.Count);
        }

        [Fact]
        public async Task CreateBookAsync_NoAuthors_CreatesBookWithoutAuthors()
        {
            // Arrange
            var createDto = new CreateBookDto
            {
                Title = "Test Book",
                Price = 9.99m,
                StockQuantity = 10
            };

            var bookEntity = new Book { Id = 1 };
            var bookDto = new BookDto { Id = 1 };

            _mockMapper.Setup(x => x.Map<Book>(createDto))
                .Returns(bookEntity);

            _mockBookRepository.Setup(x => x.CreateBookAsync(bookEntity, It.IsAny<CancellationToken>()))
                .ReturnsAsync(bookEntity);

            _mockMapper.Setup(x => x.Map<BookDto>(bookEntity))
                .Returns(bookDto);

            // Act
            var result = await _bookService.CreateBookAsync(createDto, CancellationToken.None);

            // Assert
            Assert.NotNull(result);
            Assert.Empty(bookEntity.Authors);
        }
        #endregion

        #region UpdateBookAsync Tests
        [Fact]
        public async Task UpdateBookAsync_BookExists_UpdatesAndReturnsBook()
        {
            // Arrange
            var updateDto = new UpdateBookDto
            {
                Title = "Updated Title",
                AuthorIds = new List<int> { 1, 2 }
            };

            var existingBook = new Book
            {
                Id = 1,
                Authors = new List<Author>()
            };

            var updatedBook = new Book { Id = 1 };
            var authors = new List<Author> { new Author { Id = 1 }, new Author { Id = 2 } };
            var bookDto = new BookDto { Id = 1 };

            _mockBookRepository.Setup(x => x.GetBookByIdAsync(1, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync(existingBook);

            _mockAuthorRepository.Setup(x => x.GetAuthorsByIdsAsync(updateDto.AuthorIds, It.IsAny<CancellationToken>()))
                .ReturnsAsync(authors);

            _mockBookRepository.Setup(x => x.UpdateBookAsync(existingBook, It.IsAny<CancellationToken>()))
                .ReturnsAsync(updatedBook);

            _mockMapper.Setup(x => x.Map<BookDto>(updatedBook))
                .Returns(bookDto);

            // Act
            var result = await _bookService.UpdateBookAsync(1, updateDto, CancellationToken.None);

            // Assert
            Assert.NotNull(result);
            Assert.Equal(1, result.Id);
            Assert.Equal(2, existingBook.Authors.Count);
        }

        [Fact]
        public async Task UpdateBookAsync_BookDoesNotExist_ReturnsNull()
        {
            // Arrange
            var updateDto = new UpdateBookDto { Title = "Updated Title" };

            _mockBookRepository.Setup(x => x.GetBookByIdAsync(1, true, true, It.IsAny<CancellationToken>()))
                .ReturnsAsync((Book)null);

            // Act
            var result = await _bookService.UpdateBookAsync(1, updateDto, CancellationToken.None);

            // Assert
            Assert.Null(result);
        }
        #endregion

        #region DeleteBookAsync Tests
        [Fact]
        public async Task DeleteBookAsync_BookExists_DeletesAndReturnsTrue()
        {
            // Arrange
            _mockBookRepository.Setup(x => x.BookExistAsync(1, It.IsAny<CancellationToken>()))
                .ReturnsAsync(true);

            // Act
            var result = await _bookService.DeleteBookAsync(1, CancellationToken.None);

            // Assert
            Assert.True(result);
            _mockBookRepository.Verify(x => x.DeleteBookAsync(1, It.IsAny<CancellationToken>()), Times.Once);
        }

        [Fact]
        public async Task DeleteBookAsync_BookDoesNotExist_ReturnsFalse()
        {
            // Arrange
            _mockBookRepository.Setup(x => x.BookExistAsync(1, It.IsAny<CancellationToken>()))
                .ReturnsAsync(false);

            // Act
            var result = await _bookService.DeleteBookAsync(1, CancellationToken.None);

            // Assert
            Assert.False(result);
            _mockBookRepository.Verify(x => x.DeleteBookAsync(1, It.IsAny<CancellationToken>()), Times.Never);
        }
        #endregion

        #region SearchBooksByTitleAsync Tests
        [Fact]
        public async Task SearchBooksByTitleAsync_ReturnsMatchingBooks()
        {
            // Arrange
            var books = new List<Book> { new Book { Id = 1, Title = "Test Book" } };
            var bookDtos = new List<BookDto> { new BookDto { Id = 1, Title = "Test Book" } };

            _mockBookRepository.Setup(x => x.SearchBooksByTitleAsync("Test", It.IsAny<bool>(), It.IsAny<bool>(), It.IsAny<CancellationToken>()))
                .ReturnsAsync(books);

            _mockMapper.Setup(x => x.Map<List<BookDto>>(books))
                .Returns(bookDtos);

            // Act
            var result = await _bookService.SearchBooksByTitleAsync("Test");

            // Assert
            Assert.Single(result);
            Assert.Equal("Test Book", result.First().Title);
        }
        #endregion
    }
}