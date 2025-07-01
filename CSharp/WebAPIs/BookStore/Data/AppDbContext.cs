using BookStore.Models;
using Microsoft.EntityFrameworkCore;

namespace BookStore.Data
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options) { }

        public DbSet<Book> Books { get; set; }
        public DbSet<User> Users { get; set; }
        public DbSet<Author> Authors { get; set; }
        public DbSet<Review> Reviews { get; set; }

        //Seed Authors
        ModelBuilder.Entity<Author>.HasData(
            new Author { Id = 1, Name = "Abbas Maroufi", BirthDate = new DateTime(1940, 1, 1)}
            new Author { Id = 2, Name = "George R.R. Martin", BirthDate = new DateTime(1950, 2, 2) 
            new Author { Id = 1, Name = "J.K. Rowling", BirthDate = new DateTime(1960, 3, 3) }
        )

    }
}