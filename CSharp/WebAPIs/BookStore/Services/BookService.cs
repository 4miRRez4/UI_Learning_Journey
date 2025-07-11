using Microsoft.EntityFrameworkCore;
using AutoMapper;
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

        private readonly IMapper _mapper;

        private readonly ILogger<BookService> _logger;

        public BookService(IBookRepository bookRepository, IAuthorRepository authorRepository, IMapper mapper, ILogger<BookService> logger)
        {
            _bookRepository = bookRepository;
            _authorRepository = authorRepository;
            _mapper = mapper;
            _logger = logger;
        }

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync()
        {
            var books = await _bookRepository.GetAllBooksAsync();

            return _mapper.Map<IEnumerable<BookDto>>(books);
        }

        public async Task<BookDto?> GetBookByIdAsync(int id)
        {
            var bookEntity = await _bookRepository.GetBookByIdAsync(id);

            return bookEntity == null ? null : _mapper.Map<BookDto>(bookEntity);
        }

        public async Task<BookDto> CreateBookAsync(CreateBookDto bookDto)
        {
            var bookEntity = _mapper.Map<Book>(bookDto);

            if(bookDto.AuthorIds?.Count > 0)
            {
                var authors = await _authorRepository.GetAuthorsByIdsAsync(bookDto.AuthorIds);
                bookEntity.Authors = authors ?? new List<Author>();
            }

            var createdBook = await _bookRepository.CreateBookAsync(bookEntity);

            return _mapper.Map<BookDto>(createdBook);
        }
            
        public async Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto updateDto)
        {
            var existingBook = await _bookRepository.GetBookByIdAsync(id);
            if (existingBook == null)
            {
                _logger.LogWarning("There is no book with ID {BookId} to update.", id);
                return null;
            }

            _mapper.Map(updateDto, existingBook);

            if (updateDto.AuthorIds?.Count > 0)
            {
                existingBook.Authors.Clear();

                var authors = await _authorRepository.GetAuthorsByIdsAsync(updateDto.AuthorIds);
                existingBook.Authors = authors;
            }

            var updatedBook = await _bookRepository.UpdateBookAsync(existingBook);

            return _mapper.Map<BookDto>(updatedBook);
        }

    }
}