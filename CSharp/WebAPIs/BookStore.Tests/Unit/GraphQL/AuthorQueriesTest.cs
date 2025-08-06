using BookStore.Data;
using BookStore.GraphQL.Queries;
using BookStore.Tests.Fixtures;
using BookStore.Models;
using Microsoft.EntityFrameworkCore;
using Xunit;

namespace BookStore.Tests.Unit.GraphQL;

public class AuthorQueriesTests : IDisposable
{
    private readonly TestDbContextFactory _fixture;
    private readonly TestAppDbContext _context;
    private readonly AuthorQueries _authorQueries;

    public AuthorQueriesTests()
    {
        _fixture = new TestDbContextFactory();
        _context = _fixture.CreateContext();
        _authorQueries = new AuthorQueries();
    }

    public void Dispose() => _context.Dispose();

    #region GetAuthors
    [Fact]
    public void GetAuthors_ReturnsAllAuthors()
    {
        // Act
        var result = _authorQueries.GetAuthors(_context);

        // Assert
        Assert.Equal(3, result.Count());
    }

    [Fact]
    public void GetAuthors_WithPaging_ReturnsCorrectPage()
    {
        // Act
        var result = _authorQueries.GetAuthors(_context).Skip(1).Take(1).ToList();

        // Assert
        Assert.Single(result);
        Assert.Equal(2, result[0].Id);
    }

    [Fact]
    public void GetAuthors_WithProjection_ReturnsOnlyRequestedFields()
    {
        // Act
        var result = _authorQueries.GetAuthors(_context)
            .Select(a => new { a.Id, a.Name })
            .First();

        // Assert
        Assert.Equal(1, result.Id);
        Assert.NotNull(result.Name);
    }

    [Fact]
    public async Task GetAuthors_WithBooks_IncludesBooks()
    {

        // Act
        var authorWithBooks = await _authorQueries.GetAuthors(_context)
            .Include(a => a.Books)
            .FirstAsync(a => a.Id == 2);

        // Assert
        Assert.Equal(2, authorWithBooks.Books.Count);
    }

    #endregion
}