using System; 
using BookStore.Models;
using BookStore.Models.Enums; 
using Microsoft.EntityFrameworkCore;

namespace BookStore.Data
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options) { }

        public DbSet<Book> Books { get; set; }
        public DbSet<Author> Authors { get; set; }
        public DbSet<User> Users { get; set; }
        public DbSet<Customer> Customers { get; set; }
        public DbSet<Order> Orders { get; set; }
        public DbSet<OrderItem> OrderItems { get; set; }
        public DbSet<Review> Reviews { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configure User-Customer relationship (one-to-one)
            modelBuilder.Entity<ApplicationUser>()
                .HasOne(u => u.Customer)
                .WithOne(c => c.ApplicationUser)
                .HasForeignKey<Customer>(c => c.UserId)
                .IsRequired(false);
                .OnDelete(DeleteBehavior.Cascade)

            // Configure Order relationships
            modelBuilder.Entity<Order>()
                .HasOne(o => o.Customer)
                .WithMany(c => c.Orders)
                .HasForeignKey(o => o.CustomerId)
                .OnDelete(DeleteBehavior.Restrict);

            modelBuilder.Entity<OrderItem>()
                .HasOne(oi => oi.Order)
                .WithMany(o => o.OrderItems)
                .HasForeignKey(oi => oi.OrderId)
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<OrderItem>()
                .HasOne(oi => oi.Book)
                .WithMany(b => b.OrderItems)
                .HasForeignKey(oi => oi.BookId)
                .OnDelete(DeleteBehavior.Restrict);

            // Configure Book-Author many-to-many relationship
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
                    }
                );

            // Seed Authors
            modelBuilder.Entity<Author>().HasData(
                new Author
                {
                    Id = 1,
                    Name = "J.K. Rowling",
                    BirthDate = new DateTime(1965, 7, 31)
                },
                new Author
                {
                    Id = 2,
                    Name = "George R.R. Martin",
                    BirthDate = new DateTime(1948, 9, 20)
                },
                new Author
                {
                    Id = 3,
                    Name = "Stephen King",
                    BirthDate = new DateTime(1947, 9, 21)
                },
                new Author
                {
                    Id = 4,
                    Name = "Agatha Christie",
                    BirthDate = new DateTime(1890, 9, 15)
                },
                new Author
                {
                    Id = 5,
                    Name = "Ernest Hemingway",
                    BirthDate = new DateTime(1899, 7, 21)
                }
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
                Language = "Persian",
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc)  
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
                Language = "Persian",
                CreatedAt = new DateTime(2023, 3, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 3, 1, 10, 0, 0, DateTimeKind.Utc)  
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
                CreatedAt = new DateTime(2023, 2, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 2, 1, 10, 0, 0, DateTimeKind.Utc)  
            },

            new Book
            {
                Id = 4,
                Title = "And Then There Were None",
                Description = "Classic murder mystery by Agatha Christie.",
                PublishDate = new DateTime(1939, 11, 6),
                Genre = "Mystery",
                Price = 12.99m,
                StockQuantity = 40,
                Publisher = "Collins Crime Club",
                Language = "English",
                CreatedAt = new DateTime(2023, 4, 1, 10, 0, 0, DateTimeKind.Utc),
                UpdatedAt = new DateTime(2023, 4, 1, 10, 0, 0, DateTimeKind.Utc)
            },
            new Book
            {
                Id = 5,
                Title = "The Old Man and the Sea",
                Description = "A novella by Ernest Hemingway about an aging Cuban fisherman.",
                PublishDate = new DateTime(1952, 9, 1),
                Genre = "Fiction",
                Price = 12.99m,
                StockQuantity = 30,
                Publisher = "Scribner",
                Language = "English",
                CreatedAt = new DateTime(2023, 5, 1, 10, 0, 0, DateTimeKind.Utc),
                UpdatedAt = new DateTime(2023, 5, 1, 10, 0, 0, DateTimeKind.Utc)
            }
            );

            // Seed Users (for authentication)
            modelBuilder.Entity<User>().HasData(
                new User
                {
                    Id = 1,
                    Username = "admin",
                    PasswordHash = "hashed_admin_password_123"
                },
                new User
                {
                    Id = 2,
                    Username = "john_doe",
                    PasswordHash = "hashed_john_password_123"
                },
                new User
                {
                    Id = 3,
                    Username = "jane_smith",
                    PasswordHash = "hashed_jane_password_123"
                },
                new User
                {
                    Id = 4,
                    Username = "bob_wilson",
                    PasswordHash = "hashed_bob_password_123"
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
                PhoneNumber = "+1234567890",
                Address = "123 Admin St, Admin City, AC 12345",
                DateOfBirth = new DateTime(1990, 1, 1),
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc) 
            },
            new Customer
            {
                Id = 2,
                UserId = 2,
                Email = "john.doe@email.com",
                FirstName = "John",
                LastName = "Doe",
                PhoneNumber = "+1234567891",
                Address = "456 Main St, Anytown, AT 54321",
                DateOfBirth = new DateTime(1985, 5, 15),
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc) 
            },
            new Customer
            {
                Id = 3,
                UserId = 3,
                Email = "jane.smith@email.com",
                FirstName = "Jane",
                LastName = "Smith",
                PhoneNumber = "+1234567892",
                Address = "789 Oak Ave, Somewhere, SW 67890",
                DateOfBirth = new DateTime(1992, 8, 22),
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc)  
            },
            new Customer
            {
                Id = 4,
                UserId = null, // Guest customer 
                Email = "guest@email.com",
                FirstName = "Guest",
                LastName = "Customer",
                PhoneNumber = "+1234567893",
                Address = "999 Guest St, Guest City, GC 99999",
                DateOfBirth = null,
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc), 
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc) 
            },
            
            new Customer
            {
                Id = 5,
                UserId = 4, // Link to bob_wilson user
                Email = "bob.wilson@email.com",
                FirstName = "Bob",
                LastName = "Wilson",
                PhoneNumber = "+1234567894",
                Address = "101 Pine Ln, Forest Town, FT 11111",
                DateOfBirth = new DateTime(1988, 3, 10),
                CreatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc),
                UpdatedAt = new DateTime(2023, 1, 1, 10, 0, 0, DateTimeKind.Utc)
            }
            );

            // Seed Book-Author relationships
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
                            new { BookId = 3, AuthorId = 3 }, 
                            new { BookId = 4, AuthorId = 4 }, 
                            new { BookId = 5, AuthorId = 5 } 
                        );
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
                    Comment = "Fantastic book! A perfect introduction to the magical world.",
                    CreatedAt = new DateTime(2024, 6, 10, 15, 30, 0, DateTimeKind.Utc) 
                },
                new Review
                {
                    Id = 2,
                    BookId = 2,
                    UserId = 3,
                    Rating = 4,
                    Comment = "Great but too violent for my taste. Excellent world-building though.",
                    CreatedAt = new DateTime(2024, 6, 15, 11, 0, 0, DateTimeKind.Utc) 
                },
                new Review
                {
                    Id = 3,
                    BookId = 3,
                    UserId = 2,
                    Rating = 5,
                    Comment = "Scared me to death! Masterpiece of horror literature.",
                    CreatedAt = new DateTime(2024, 6, 20, 9, 45, 0, DateTimeKind.Utc)
                },
                new Review
                {
                    Id = 4,
                    BookId = 4,
                    UserId = 4,
                    Rating = 4,
                    Comment = "Classic mystery novel. Poirot is brilliant as always.",
                    CreatedAt = new DateTime(2024, 6, 25, 14, 0, 0, DateTimeKind.Utc)
                },
                new Review
                {
                    Id = 5,
                    BookId = 5,
                    UserId = 3,
                    Rating = 3,
                    Comment = "Good story but a bit slow-paced for my liking.",
                    CreatedAt = new DateTime(2024, 7, 1, 10, 20, 0, DateTimeKind.Utc)
                }
            );

            // Seed Orders
            modelBuilder.Entity<Order>().HasData(
                new Order
                {
                    Id = 1,
                    CustomerId = 2,
                    OrderDate = new DateTime(2024, 7, 8, 10, 0, 0, DateTimeKind.Utc), 
                    Status = OrderStatus.Delivered,
                    Subtotal = 44.98m,
                    TaxAmount = 4.50m,
                    ShippingAmount = 5.99m,
                    DiscountAmount = 0m,
                    TotalAmount = 55.47m,
                    PaymentStatus = PaymentStatus.Paid,
                    PaymentMethod = "Credit Card",
                    TransactionId = "TXN_001_2024",
                    ShippingAddress = "456 Main St, Anytown, AT 54321",
                    ShippingMethod = "Standard",
                    Notes = "First order from John Doe",
                    CreatedAt = new DateTime(2024, 7, 8, 10, 0, 0, DateTimeKind.Utc), 
                    UpdatedAt = new DateTime(2024, 7, 12, 10, 0, 0, DateTimeKind.Utc) 
                },
                new Order
                {
                    Id = 2,
                    CustomerId = 3,
                    OrderDate = new DateTime(2024, 7, 10, 14, 30, 0, DateTimeKind.Utc), 
                    Status = OrderStatus.Shipped,
                    Subtotal = 32.98m,
                    TaxAmount = 3.30m,
                    ShippingAmount = 5.99m,
                    DiscountAmount = 0m,
                    TotalAmount = 42.27m,
                    PaymentStatus = PaymentStatus.Paid,
                    PaymentMethod = "PayPal",
                    TransactionId = "TXN_002_2024",
                    ShippingAddress = "789 Oak Ave, Somewhere, SW 67890",
                    ShippingMethod = "Express",
                    Notes = "Express shipping requested",
                    CreatedAt = new DateTime(2024, 7, 10, 14, 30, 0, DateTimeKind.Utc), 
                    UpdatedAt = new DateTime(2024, 7, 12, 14, 30, 0, DateTimeKind.Utc) 
                },
                new Order
                {
                    Id = 3,
                    CustomerId = 4, // Guest customer
                    OrderDate = new DateTime(2024, 7, 12, 9, 0, 0, DateTimeKind.Utc),
                    Status = OrderStatus.Pending,
                    Subtotal = 19.99m,
                    TaxAmount = 2.00m,
                    ShippingAmount = 5.99m,
                    DiscountAmount = 0m,
                    TotalAmount = 27.98m,
                    PaymentStatus = PaymentStatus.Pending,
                    PaymentMethod = "Credit Card",
                    TransactionId = null,
                    ShippingAddress = "999 Guest St, Guest City, GC 99999",
                    ShippingMethod = "Standard",
                    Notes = "Guest order",
                    CreatedAt = new DateTime(2024, 7, 12, 9, 0, 0, DateTimeKind.Utc),
                    UpdatedAt = new DateTime(2024, 7, 12, 9, 0, 0, DateTimeKind.Utc) 
                }
            );

            // Seed OrderItems 
            modelBuilder.Entity<OrderItem>().HasData(
                new OrderItem
                {
                    Id = 1,
                    OrderId = 1,
                    BookId = 1,
                    Quantity = 1,
                    UnitPrice = 24.99m,
                    Subtotal = 24.99m,
                    DiscountAmount = 0m
                },
                new OrderItem
                {
                    Id = 2,
                    OrderId = 1,
                    BookId = 3,
                    Quantity = 1,
                    UnitPrice = 19.99m,
                    Subtotal = 19.99m,
                    DiscountAmount = 0m
                },
                new OrderItem
                {
                    Id = 3,
                    OrderId = 2,
                    BookId = 2,
                    Quantity = 1,
                    UnitPrice = 29.99m,
                    Subtotal = 29.99m,
                    DiscountAmount = 0m
                },
                new OrderItem
                {
                    Id = 4,
                    OrderId = 2,
                    BookId = 5, 
                    Quantity = 1,
                    UnitPrice = 12.99m,
                    Subtotal = 12.99m,
                    DiscountAmount = 0m
                },
                new OrderItem
                {
                    Id = 5,
                    OrderId = 3,
                    BookId = 3,
                    Quantity = 1,
                    UnitPrice = 19.99m,
                    Subtotal = 19.99m,
                    DiscountAmount = 0m
                }
            );
        }
    }
}