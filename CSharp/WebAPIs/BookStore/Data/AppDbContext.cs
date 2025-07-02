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
        

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Seed Authors
            modelBuilder.Entity<Author>().HasData(
                new Author { Id = 1, Name = "Abbas Maroufi", BirthDate = new DateTime(1940, 1, 1) },
                new Author { Id = 2, Name = "George R.R. Martin", BirthDate = new DateTime(1950, 2, 2) },
                new Author { Id = 3, Name = "J.K. Rowling", BirthDate = new DateTime(1960, 3, 3) }
            );


            // Seed Books   
            modelBuilder.Entity<Book>().HasData(
            new Book
            {
                Id = 1,
                Title = "Harry Potter and the Philosopher's Stone",
                Description = "The first book in the Harry Potter series",
                PublishDate = new DateTime(1997, 6, 26),
                Genre = "Fantasy"
            },
            new Book
            {
                Id = 2,
                Title = "A Game of Thrones",
                Description = "The first book in A Song of Ice and Fire",
                PublishDate = new DateTime(1996, 8, 1),
                Genre = "Fantasy"
            },
            new Book
            {
                Id = 3,
                Title = "The Shining",
                Description = "A horror novel about a haunted hotel",
                PublishDate = new DateTime(1977, 1, 28),
                Genre = "Horror"
            }
            );

            // many-to-many relationships
            modelBuilder.Entity("BookAuthor").HasData(
            new { BooksId = 1, AuthorsId = 1 },
            new { BooksId = 2, AuthorsId = 2 },
            new { BooksId = 3, AuthorsId = 3 }
            );

            // Seed Users
            modelBuilder.Entity<User>().HasData(
            new User
            {
                Id = 1,
                Username = "admin",
                PasswordHash = "hashed_password_here",
            },
            new User
            {
                Id = 2,
                Username = "john_doe",
                PasswordHash = "hashed_password_here",
            },
            new User
            {
                Id = 3,
                Username = "jane_smith",
                PasswordHash = "hashed_password_here",
            }
            );

            // Seed Reviews
            modelBuilder.Entity<Review>().HasData(
            new Review
            {
                Id = 1,
                BookId = 1,
                UserId = 2,
                Rating = 5,
                Comment = "Fantastic book!",
                CreatedAt = new DateTime(2023, 1, 15)
            },
            new Review
            {
                Id = 2,
                BookId = 2,
                UserId = 3,
                Rating = 4,
                Comment = "Great but too violent",
                CreatedAt = new DateTime(2023, 2, 20)
            },
            new Review
            {
                Id = 3,
                BookId = 3,
                UserId = 2,
                Rating = 5,
                Comment = "Scared me to death!",
                CreatedAt = new DateTime(2023, 3, 10)
            }
            );
        }
    }
}