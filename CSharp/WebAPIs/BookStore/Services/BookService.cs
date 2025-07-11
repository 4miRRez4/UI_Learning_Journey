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

        private readonly IMapper  _mapper;

        public BookService(IBookRepository bookRepository, IAuthorRepository authorRepository, IMapper mapper)
        {
            _bookRepository = bookRepository;
            _authorRepository = authorRepository;
            _mapper = mapper;
        }

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync()
        {
            var books = await _bookRepository.GetAllBooksAsync();

            return _mapper.Map<IEnumerable<BookDto>>(books);
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

    }
}