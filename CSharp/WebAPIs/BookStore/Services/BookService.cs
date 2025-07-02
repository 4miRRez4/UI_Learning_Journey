using Microsoft.EntityFrameworkCore;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Dtos.Book;
using System.Collections.Generic;
using System.Threading.Tasks;


namespace BookStore.Services
{
    public class BookService : IBookService
    {
        private readonly AppDbContext _context;

        public BookService(AppDbContext context)
        {
            _context = context;
        }

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync()
        {
            var books = await _context.Books
                .AsNoTracking()
                .ToListAsync();

            var bookDtos = new List<BookDto>();
            foreach(var book in books)
            {
                bookDtos.Add(new BookDto
                {
                    Id = book.Id,
                    Title = book.Title,
                    Description = book.Description,
                    PublishDate = book.PublishDate,
                    Genre = book.Genre
                });
            }

            return bookDtos;
        }

        public async Task<BookDto> CreateBookAsync(CreateBookDto bookDto)
        {
            var bookEntity = new Book
            {
                Title = bookDto.Title,
                Description = bookDto.Description,
                PublishDate = bookDto.PublishDate,
                Genre = bookDto.Genre
            };

            await _context.Books.AddAsync(bookEntity);
            await _context.SaveChangesAsync();


            return new BookDto
            {
                Id = bookEntity.Id,
                Title = bookEntity.Title,
                Description = bookEntity.Description,
                PublishDate = bookEntity.PublishDate,
                Genre = bookEntity.Genre
            };
        }

    }
}