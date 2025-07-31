using AutoMapper;
using BookStore.Repositories.Interfaces;
using BookStore.Services;
using Microsoft.Extensions.Logging;
using Moq;

namespace BookStore.Tests.Fixtures
{
    public class BookServiceTests
    {
        public class BookServiceFixture : IDisposable
        {
            public Mock<IBookRepository> BookRepositoryMock { get; }
            public Mock<IAuthorRepository> AuthorRepositoryMock { get; }
            public Mock<IMapper> MapperMock { get; }
            public Mock<ILogger<BookService>> LoggerMock { get; }

            public BookServiceFixture()
            {
                BookRepositoryMock = new Mock<IBookRepository>();
                AuthorRepositoryMock = new Mock<IAuthorRepository>();
                MapperMock = new Mock<IMapper>();
                LoggerMock = new Mock<ILogger<BookService>>();
            }

            public void Dispose()
            {

            }
        }
    }
}
