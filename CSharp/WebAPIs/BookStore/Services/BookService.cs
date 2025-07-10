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
        private readonly IBookRepository _bookRepository;
        private readonly IAuthorRepository _authorRepository;

        public BookService(IBookRepository bookRepository, IAuthorRepository authorRepository)
        {
            _bookRepository = bookRepository;
            _authorRepository = authorRepository;
        }

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync()
        {
            var books = await _bookRepository.GetAllBooksAsync();

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
                var authors = await _authorRepository.GetAuthorsByIdsAsync(bookDto.AuthorIds);
                bookEntity.Authors = authors ?? new List<Author>();
            }

            var createdBook = await _bookRepository.CreateBookAsync(bookEntity);


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