using BookStore.Data;
using BookStore.GraphQL.Queries;
using BookStore.Tests.Fixtures;
using BookStore.Models;
using Microsoft.EntityFrameworkCore;
using Xunit;

namespace BookStore.Tests.Unit.GraphQL;

public class AuthorQueriesTests
{
    private TestFixture _fixture;

    public AuthorQueriesTests()
    {
        _fixture = new TestFixture();
    }

    #region GetAuthors
    [Fact]
    public void GetAuthors_ReturnsAllAuthors()
    {
        // Arrange
        using var context = _fixture.CreateContext();
        var queries = new AuthorQueries();

        // Act
        var result = queries.GetAuthors(context);
    

        // Assert
        Assert.Equal(3, result.Count());
    }

    [Fact]
    public void GetAuthors_WithPaging_ReturnsCorrectPage()
    {
        // Arrange
        using var context = _fixture.CreateContext(); 
        var queries = new AuthorQueries();

        // Act
        var result = queries.GetAuthors(context).Skip(1).Take(1).ToList();

        // Assert
        Assert.Single(result);
        Assert.Equal(2, result[0].Id);
    }

    [Fact]
    public void GetAuthors_WithProjection_ReturnsOnlyRequestedFields()
    {
        // Arrange
        using var context = _fixture.CreateContext();
        var queries = new AuthorQueries();

        // Act
        var result = queries.GetAuthors(context)
            .Select(a => new { a.Id, a.Name })
            .First();

        // Assert
        Assert.Equal(1, result.Id);
        Assert.NotNull(result.Name);
    }

    [Fact]
    public async Task GetAuthors_WithBooks_IncludesBooks()
    {
        // Arrange
        using var context = _fixture.CreateContext();
        var queries = new AuthorQueries();

        // Act
        var authorWithBooks = await queries.GetAuthors(context)
            .Include(a => a.Books)
            .FirstAsync(a => a.Id == 2);

        // Assert
        Assert.Equal(2, authorWithBooks.Books.Count);
    }
    #endregion
}