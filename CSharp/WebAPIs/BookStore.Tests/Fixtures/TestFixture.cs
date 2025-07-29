//using BookStore.Data;
//using BookStore.Models;
//using Microsoft.EntityFrameworkCore;

//namespace BookStore.Tests.Fixtures;

//public class TestDbContextFactory
//{
//    private readonly DbContextOptions<AppDbContext> _options;

//    public TestDbContextFactory()
//    {
//        _options = new DbContextOptionsBuilder<AppDbContext>()
//            .UseInMemoryDatabase(databaseName: "BookStoreTestDB")
//            .Options;

//        using var context = CreateContext();
//        SeedTestData(context);
//    }

//    public AppDbContext CreateContext()
//    {
//        var context = new AppDbContext(_options);
//        return context;
//    }

//    private static void SeedTestData(AppDbContext context)
//    {
//        context.Database.EnsureDeleted();
//        context.Database.EnsureCreated();

//        context.Authors.AddRange(
//            new Author { Id = 1, Name = "Author 1", Books = new List<Book> { new() { Id = 1, Title = "Book 1" } } },
//            new Author { Id = 2, Name = "Author 2", Books = new List<Book> { new() { Id = 2, Title = "Book 2" }, new() { Id = 3, Title = "Book 3" } } },
//            new Author { Id = 3, Name = "Author 3" }
//        );

//        context.SaveChanges();
//    }
//}