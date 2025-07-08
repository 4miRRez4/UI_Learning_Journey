using Microsoft.EntityFrameworkCore;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Dtos.Book;
using BookStore.Dtos.Author;
using BookStore.Repositories.Interfaces;
using System.Collections.Generic;
using System.Threading.Tasks;



namespace BookStore.Services
{
    public class BookService : IBookService
    {
        private readonly IBookRepository _repository;

        public BookService(IBookRepository repository)
        {
            _repository = repository;
        }

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync()
        {
            var books = await _repository.GetAllBooksAsync();

            var bookDtos = new List<BookDto>();
            foreach(var book in books)
            {
                bookDtos.Add(new BookDto
                {
                    Id = book.Id,
                    Title = book.Title,
                    Description = book.Description,
                    PublishDate = book.PublishDate,
                    Genre = book.Genre,
                    Authors = book.Authors.Select(a => new AuthorDto
                    {
                        Id = a.Id,
                        Name = a.Name,
                        BirthDate = a.BirthDate
                    }).ToList()
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

            if(bookDto.AuthorIds?.Count > 0)
            {
                bookEntity.Authors = _repository.GetAllAuthorsAsync()
                    .Where(a => bookDto.AuthorIds.Contains(a.Id))
                    .ToListAsync();
            }

            var createdBook = await _repository.CreateBookAsync(bookEntity);


            return new BookDto
            {
                Id = createdBook.Id,
                Title = createdBook.Title,
                Description = createdBook.Description,
                PublishDate = createdBook.PublishDate,
                Genre = createdBook.Genre,
                Authors = createdBook.Authors?.Select(a => new AuthorDto
                {
                    Id = a.Id,
                    Name = a.Name
                }).ToList() ?? new List<AuthorDto>()
            };
        }

    }
}