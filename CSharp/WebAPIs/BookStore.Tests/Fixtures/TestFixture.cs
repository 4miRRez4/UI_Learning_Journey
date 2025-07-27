using BookStore.Data;
using BookStore.Models;
using Microsoft.EntityFrameworkCore;

namespace BookStore.Tests.Fixtures;

public class TestFixture
{
    public AppDbContext CreateContext()
    {
        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseInMemoryDatabase(databaseName: Guid.NewGuid().ToString())
            .Options;

        var context = new AppDbContext(options);
        SeedTestData(context);
        return context;
    }

    private void SeedTestData(AppDbContext context)
    {
        context.Authors.AddRange(
            new Author { Id = 1, Name = "Author 1", Books = new List<Book> { new Book { Id = 1, Title = "test book" } } },
            new Author { Id = 2, Name = "Author 2", Books = new List<Book> { new Book { Id = 2, Title = "test book" }, new Book { Id = 3, Title = "test book" } } },
            new Author { Id = 3, Name = "Author 3" }
        );
        context.SaveChanges();
    }
}