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
        public DbSet<Customer> Customers { get; set; }
        public DbSet<Author> Authors { get; set; }
        public DbSet<Review> Reviews { get; set; }
        

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>()
                .HasOne(u => u.Customer)
                .WithOne(c => c.User)
                .HasForeignKey<Customer>(c => c.UserId)
                .IsRequired(false);

            modelBuilder.Entity<Book>()
                .HasMany(b => b.Authors)
                .WithMany(a => a.Books)
                .UsingEntity<Dictionary<string, object>>(
                    "BookAuthors",
                    j => j.HasOne<Author>().WithMany().HasForeignKey("AuthorId"),
                    j => j.HasOne<Book>().WithMany().HasForeignKey("BookId"),
                    j =>
                    {
                        j.HasKey("BookId", "AuthorId");
                        j.HasData(
                            new { BookId = 1, AuthorId = 1 },
                            new { BookId = 2, AuthorId = 2 },
                            new { BookId = 3, AuthorId = 3 }
                        );
                    }
                );


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
                Genre = "Fantasy",
                Price = 24.99m,
                StockQuantity = 50,
                Publisher = "Cheshmeh",
                Language = "Persian"
            },
            new Book
            {
                Id = 2,
                Title = "A Game of Thrones",
                Description = "The first book in A Song of Ice and Fire",
                PublishDate = new DateTime(1996, 8, 1),
                Genre = "Fantasy",
                Price = 29.99m,
                StockQuantity = 35,
                Publisher = "Ava",
                Language = "Persian"
            },
            new Book
            {
                Id = 3,
                Title = "The Shining",
                Description = "A horror novel about a haunted hotel",
                PublishDate = new DateTime(1977, 1, 28),
                Genre = "Horror",
                Price = 19.99m,
                StockQuantity = 25,
                Publisher = "Doubleday",
                Language = "English",
            }
            );

            // Seed Users (for authentication)
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

            // Seed Customers (business domain)
            modelBuilder.Entity<Customer>().HasData(
            new Customer
            {
                Id = 1,
                UserId = 1, 
                Email = "admin@bookstore.com",
                FirstName = "Admin",
                LastName = "User",
                Phone = "+1234567890",
                Address = "123 Admin St, Admin City, AC 12345",
                DateOfBirth = new DateTime(1990, 1, 1),
            },
            new Customer
            {
                Id = 2,
                UserId = 2, 
                Email = "john.doe@email.com",
                FirstName = "John",
                LastName = "Doe",
                Phone = "+1234567891",
                Address = "456 Main St, Anytown, AT 54321",
                DateOfBirth = new DateTime(1985, 5, 15),
            },
            new Customer
            {
                Id = 3,
                UserId = 3, 
                Email = "jane.smith@email.com",
                FirstName = "Jane",
                LastName = "Smith",
                Phone = "+1234567892",
                Address = "789 Oak Ave, Somewhere, SW 67890",
                DateOfBirth = new DateTime(1992, 8, 22),
            },
            new Customer
            {
                Id = 4,
                UserId = null, // Guest customer
                Email = "guest@email.com",
                FirstName = "Guest",
                LastName = "Customer",
                Phone = "+1234567893",
                Address = "999 Guest St, Guest City, GC 99999",
                DateOfBirth = null,
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