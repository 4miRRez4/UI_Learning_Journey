using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace BookStore.Data
{
    /// <inheritdoc />
    public partial class InitialCreateWithEcommerceEntities : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Authors",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: false),
                    BirthDate = table.Column<DateTime>(type: "datetime2", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Authors", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Books",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Title = table.Column<string>(type: "nvarchar(200)", maxLength: 200, nullable: false),
                    Description = table.Column<string>(type: "nvarchar(max)", maxLength: 500, nullable: true),
                    PublishDate = table.Column<DateTime>(type: "datetime2", nullable: true),
                    Genre = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: true),
                    Price = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    StockQuantity = table.Column<int>(type: "int", nullable: false),
                    Publisher = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: true),
                    Language = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: true),
                    CreatedAt = table.Column<DateTime>(type: "datetime2", nullable: false),
                    UpdatedAt = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Books", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Users",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Username = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    PasswordHash = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Users", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "BookAuthors",
                columns: table => new
                {
                    BookId = table.Column<int>(type: "int", nullable: false),
                    AuthorId = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BookAuthors", x => new { x.BookId, x.AuthorId });
                    table.ForeignKey(
                        name: "FK_BookAuthors_Authors_AuthorId",
                        column: x => x.AuthorId,
                        principalTable: "Authors",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_BookAuthors_Books_BookId",
                        column: x => x.BookId,
                        principalTable: "Books",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Customers",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    UserId = table.Column<int>(type: "int", nullable: true),
                    Email = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: false),
                    FirstName = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    LastName = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    PhoneNumber = table.Column<string>(type: "nvarchar(20)", maxLength: 20, nullable: true),
                    Address = table.Column<string>(type: "nvarchar(200)", maxLength: 200, nullable: true),
                    DateOfBirth = table.Column<DateTime>(type: "datetime2", nullable: true),
                    CreatedAt = table.Column<DateTime>(type: "datetime2", nullable: false),
                    UpdatedAt = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Customers", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Customers_Users_UserId",
                        column: x => x.UserId,
                        principalTable: "Users",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "Reviews",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Rating = table.Column<int>(type: "int", nullable: false),
                    Comment = table.Column<string>(type: "nvarchar(1000)", maxLength: 1000, nullable: true),
                    CreatedAt = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BookId = table.Column<int>(type: "int", nullable: false),
                    UserId = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Reviews", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Reviews_Books_BookId",
                        column: x => x.BookId,
                        principalTable: "Books",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_Reviews_Users_UserId",
                        column: x => x.UserId,
                        principalTable: "Users",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Orders",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    CustomerId = table.Column<int>(type: "int", nullable: false),
                    OrderDate = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Status = table.Column<int>(type: "int", nullable: false),
                    TotalAmount = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    Subtotal = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    TaxAmount = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    ShippingAmount = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    DiscountAmount = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    PaymentStatus = table.Column<int>(type: "int", nullable: false),
                    PaymentMethod = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: true),
                    TransactionId = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: true),
                    ShippingAddress = table.Column<string>(type: "nvarchar(200)", maxLength: 200, nullable: false),
                    ShippingMethod = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: true),
                    Notes = table.Column<string>(type: "nvarchar(500)", maxLength: 500, nullable: true),
                    CreatedAt = table.Column<DateTime>(type: "datetime2", nullable: false),
                    UpdatedAt = table.Column<DateTime>(type: "datetime2", nullable: false),
                    UserId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Orders", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Orders_Customers_CustomerId",
                        column: x => x.CustomerId,
                        principalTable: "Customers",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_Orders_Users_UserId",
                        column: x => x.UserId,
                        principalTable: "Users",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "OrderItems",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    OrderId = table.Column<int>(type: "int", nullable: false),
                    BookId = table.Column<int>(type: "int", nullable: false),
                    Quantity = table.Column<int>(type: "int", nullable: false),
                    UnitPrice = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    Subtotal = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    DiscountAmount = table.Column<decimal>(type: "decimal(18,2)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_OrderItems", x => x.Id);
                    table.ForeignKey(
                        name: "FK_OrderItems_Books_BookId",
                        column: x => x.BookId,
                        principalTable: "Books",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_OrderItems_Orders_OrderId",
                        column: x => x.OrderId,
                        principalTable: "Orders",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "Authors",
                columns: new[] { "Id", "BirthDate", "Name" },
                values: new object[,]
                {
                    { 1, new DateTime(1965, 7, 31, 0, 0, 0, 0, DateTimeKind.Unspecified), "J.K. Rowling" },
                    { 2, new DateTime(1948, 9, 20, 0, 0, 0, 0, DateTimeKind.Unspecified), "George R.R. Martin" },
                    { 3, new DateTime(1947, 9, 21, 0, 0, 0, 0, DateTimeKind.Unspecified), "Stephen King" },
                    { 4, new DateTime(1890, 9, 15, 0, 0, 0, 0, DateTimeKind.Unspecified), "Agatha Christie" },
                    { 5, new DateTime(1899, 7, 21, 0, 0, 0, 0, DateTimeKind.Unspecified), "Ernest Hemingway" }
                });

            migrationBuilder.InsertData(
                table: "Books",
                columns: new[] { "Id", "CreatedAt", "Description", "Genre", "Language", "Price", "PublishDate", "Publisher", "StockQuantity", "Title", "UpdatedAt" },
                values: new object[,]
                {
                    { 1, new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), "The first book in the Harry Potter series", "Fantasy", "Persian", 24.99m, new DateTime(1997, 6, 26, 0, 0, 0, 0, DateTimeKind.Unspecified), "Cheshmeh", 50, "Harry Potter and the Philosopher's Stone", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc) },
                    { 2, new DateTime(2023, 3, 1, 10, 0, 0, 0, DateTimeKind.Utc), "The first book in A Song of Ice and Fire", "Fantasy", "Persian", 29.99m, new DateTime(1996, 8, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), "Ava", 35, "A Game of Thrones", new DateTime(2023, 3, 1, 10, 0, 0, 0, DateTimeKind.Utc) },
                    { 3, new DateTime(2023, 2, 1, 10, 0, 0, 0, DateTimeKind.Utc), "A horror novel about a haunted hotel", "Horror", "English", 19.99m, new DateTime(1977, 1, 28, 0, 0, 0, 0, DateTimeKind.Unspecified), "Doubleday", 25, "The Shining", new DateTime(2023, 2, 1, 10, 0, 0, 0, DateTimeKind.Utc) },
                    { 4, new DateTime(2023, 4, 1, 10, 0, 0, 0, DateTimeKind.Utc), "Classic murder mystery by Agatha Christie.", "Mystery", "English", 12.99m, new DateTime(1939, 11, 6, 0, 0, 0, 0, DateTimeKind.Unspecified), "Collins Crime Club", 40, "And Then There Were None", new DateTime(2023, 4, 1, 10, 0, 0, 0, DateTimeKind.Utc) },
                    { 5, new DateTime(2023, 5, 1, 10, 0, 0, 0, DateTimeKind.Utc), "A novella by Ernest Hemingway about an aging Cuban fisherman.", "Fiction", "English", 12.99m, new DateTime(1952, 9, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), "Scribner", 30, "The Old Man and the Sea", new DateTime(2023, 5, 1, 10, 0, 0, 0, DateTimeKind.Utc) }
                });

            migrationBuilder.InsertData(
                table: "Customers",
                columns: new[] { "Id", "Address", "CreatedAt", "DateOfBirth", "Email", "FirstName", "LastName", "PhoneNumber", "UpdatedAt", "UserId" },
                values: new object[] { 4, "999 Guest St, Guest City, GC 99999", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), null, "guest@email.com", "Guest", "Customer", "+1234567893", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), null });

            migrationBuilder.InsertData(
                table: "Users",
                columns: new[] { "Id", "PasswordHash", "Username" },
                values: new object[,]
                {
                    { 1, "hashed_admin_password_123", "admin" },
                    { 2, "hashed_john_password_123", "john_doe" },
                    { 3, "hashed_jane_password_123", "jane_smith" },
                    { 4, "hashed_bob_password_123", "bob_wilson" }
                });

            migrationBuilder.InsertData(
                table: "BookAuthors",
                columns: new[] { "AuthorId", "BookId" },
                values: new object[,]
                {
                    { 1, 1 },
                    { 2, 2 },
                    { 3, 3 },
                    { 4, 4 },
                    { 5, 5 }
                });

            migrationBuilder.InsertData(
                table: "Customers",
                columns: new[] { "Id", "Address", "CreatedAt", "DateOfBirth", "Email", "FirstName", "LastName", "PhoneNumber", "UpdatedAt", "UserId" },
                values: new object[,]
                {
                    { 1, "123 Admin St, Admin City, AC 12345", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), new DateTime(1990, 1, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), "admin@bookstore.com", "Admin", "User", "+1234567890", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), 1 },
                    { 2, "456 Main St, Anytown, AT 54321", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), new DateTime(1985, 5, 15, 0, 0, 0, 0, DateTimeKind.Unspecified), "john.doe@email.com", "John", "Doe", "+1234567891", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), 2 },
                    { 3, "789 Oak Ave, Somewhere, SW 67890", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), new DateTime(1992, 8, 22, 0, 0, 0, 0, DateTimeKind.Unspecified), "jane.smith@email.com", "Jane", "Smith", "+1234567892", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), 3 },
                    { 5, "101 Pine Ln, Forest Town, FT 11111", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), new DateTime(1988, 3, 10, 0, 0, 0, 0, DateTimeKind.Unspecified), "bob.wilson@email.com", "Bob", "Wilson", "+1234567894", new DateTime(2023, 1, 1, 10, 0, 0, 0, DateTimeKind.Utc), 4 }
                });

            migrationBuilder.InsertData(
                table: "Orders",
                columns: new[] { "Id", "CreatedAt", "CustomerId", "DiscountAmount", "Notes", "OrderDate", "PaymentMethod", "PaymentStatus", "ShippingAddress", "ShippingAmount", "ShippingMethod", "Status", "Subtotal", "TaxAmount", "TotalAmount", "TransactionId", "UpdatedAt", "UserId" },
                values: new object[] { 3, new DateTime(2024, 7, 12, 9, 0, 0, 0, DateTimeKind.Utc), 4, 0m, "Guest order", new DateTime(2024, 7, 12, 9, 0, 0, 0, DateTimeKind.Utc), "Credit Card", 0, "999 Guest St, Guest City, GC 99999", 5.99m, "Standard", 0, 19.99m, 2.00m, 27.98m, null, new DateTime(2024, 7, 12, 9, 0, 0, 0, DateTimeKind.Utc), null });

            migrationBuilder.InsertData(
                table: "Reviews",
                columns: new[] { "Id", "BookId", "Comment", "CreatedAt", "Rating", "UserId" },
                values: new object[,]
                {
                    { 1, 1, "Fantastic book! A perfect introduction to the magical world.", new DateTime(2024, 6, 10, 15, 30, 0, 0, DateTimeKind.Utc), 5, 2 },
                    { 2, 2, "Great but too violent for my taste. Excellent world-building though.", new DateTime(2024, 6, 15, 11, 0, 0, 0, DateTimeKind.Utc), 4, 3 },
                    { 3, 3, "Scared me to death! Masterpiece of horror literature.", new DateTime(2024, 6, 20, 9, 45, 0, 0, DateTimeKind.Utc), 5, 2 },
                    { 4, 4, "Classic mystery novel. Poirot is brilliant as always.", new DateTime(2024, 6, 25, 14, 0, 0, 0, DateTimeKind.Utc), 4, 4 },
                    { 5, 5, "Good story but a bit slow-paced for my liking.", new DateTime(2024, 7, 1, 10, 20, 0, 0, DateTimeKind.Utc), 3, 3 }
                });

            migrationBuilder.InsertData(
                table: "OrderItems",
                columns: new[] { "Id", "BookId", "DiscountAmount", "OrderId", "Quantity", "Subtotal", "UnitPrice" },
                values: new object[] { 5, 3, 0m, 3, 1, 19.99m, 19.99m });

            migrationBuilder.InsertData(
                table: "Orders",
                columns: new[] { "Id", "CreatedAt", "CustomerId", "DiscountAmount", "Notes", "OrderDate", "PaymentMethod", "PaymentStatus", "ShippingAddress", "ShippingAmount", "ShippingMethod", "Status", "Subtotal", "TaxAmount", "TotalAmount", "TransactionId", "UpdatedAt", "UserId" },
                values: new object[,]
                {
                    { 1, new DateTime(2024, 7, 8, 10, 0, 0, 0, DateTimeKind.Utc), 2, 0m, "First order from John Doe", new DateTime(2024, 7, 8, 10, 0, 0, 0, DateTimeKind.Utc), "Credit Card", 1, "456 Main St, Anytown, AT 54321", 5.99m, "Standard", 3, 44.98m, 4.50m, 55.47m, "TXN_001_2024", new DateTime(2024, 7, 12, 10, 0, 0, 0, DateTimeKind.Utc), null },
                    { 2, new DateTime(2024, 7, 10, 14, 30, 0, 0, DateTimeKind.Utc), 3, 0m, "Express shipping requested", new DateTime(2024, 7, 10, 14, 30, 0, 0, DateTimeKind.Utc), "PayPal", 1, "789 Oak Ave, Somewhere, SW 67890", 5.99m, "Express", 2, 32.98m, 3.30m, 42.27m, "TXN_002_2024", new DateTime(2024, 7, 12, 14, 30, 0, 0, DateTimeKind.Utc), null }
                });

            migrationBuilder.InsertData(
                table: "OrderItems",
                columns: new[] { "Id", "BookId", "DiscountAmount", "OrderId", "Quantity", "Subtotal", "UnitPrice" },
                values: new object[,]
                {
                    { 1, 1, 0m, 1, 1, 24.99m, 24.99m },
                    { 2, 3, 0m, 1, 1, 19.99m, 19.99m },
                    { 3, 2, 0m, 2, 1, 29.99m, 29.99m },
                    { 4, 5, 0m, 2, 1, 12.99m, 12.99m }
                });

            migrationBuilder.CreateIndex(
                name: "IX_BookAuthors_AuthorId",
                table: "BookAuthors",
                column: "AuthorId");

            migrationBuilder.CreateIndex(
                name: "IX_Customers_UserId",
                table: "Customers",
                column: "UserId",
                unique: true,
                filter: "[UserId] IS NOT NULL");

            migrationBuilder.CreateIndex(
                name: "IX_OrderItems_BookId",
                table: "OrderItems",
                column: "BookId");

            migrationBuilder.CreateIndex(
                name: "IX_OrderItems_OrderId",
                table: "OrderItems",
                column: "OrderId");

            migrationBuilder.CreateIndex(
                name: "IX_Orders_CustomerId",
                table: "Orders",
                column: "CustomerId");

            migrationBuilder.CreateIndex(
                name: "IX_Orders_UserId",
                table: "Orders",
                column: "UserId");

            migrationBuilder.CreateIndex(
                name: "IX_Reviews_BookId",
                table: "Reviews",
                column: "BookId");

            migrationBuilder.CreateIndex(
                name: "IX_Reviews_UserId",
                table: "Reviews",
                column: "UserId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "BookAuthors");

            migrationBuilder.DropTable(
                name: "OrderItems");

            migrationBuilder.DropTable(
                name: "Reviews");

            migrationBuilder.DropTable(
                name: "Authors");

            migrationBuilder.DropTable(
                name: "Orders");

            migrationBuilder.DropTable(
                name: "Books");

            migrationBuilder.DropTable(
                name: "Customers");

            migrationBuilder.DropTable(
                name: "Users");
        }
    }
}
