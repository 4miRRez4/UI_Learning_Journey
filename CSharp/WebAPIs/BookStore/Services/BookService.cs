using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.JsonPatch;
using Microsoft.AspNetCore.JsonPatch.Exceptions;
using AutoMapper;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using System.Collections.Generic;
using System.Threading.Tasks;
using BookStore.Dtos.Book;
using BookStore.Dtos.Author;

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

        public async Task<IEnumerable<BookDto>> GetAllBooksAsync(CancellationToken ct)
        {
            var books = await _bookRepository.GetAllBooksAsync(ct);
            return _mapper.Map<IEnumerable<BookDto>>(books);
        }

        public async Task<BookDto?> GetBookByIdAsync(int id, CancellationToken ct)
        {
            var bookEntity = await _bookRepository.GetBookByIdAsync(id, ct);
            return bookEntity == null ? null : _mapper.Map<BookDto>(bookEntity);
        }

        public async Task<List<BookDto>> SearchBooksByTitleAsync(string title, CancellationToken ct)
        {
            var books = await _bookRepository.SearchBooksByTitleAsync(title, ct);
            return _mapper.Map<List<BookDto>>(books);
        }

        public async Task<BookDto> CreateBookAsync(CreateBookDto bookDto, CancellationToken ct)
        {
            var bookEntity = _mapper.Map<Book>(bookDto);

            if(bookDto.AuthorIds?.Count > 0)
            {
                var authors = await _authorRepository.GetAuthorsByIdsAsync(bookDto.AuthorIds, ct);
                bookEntity.Authors = authors ?? new List<Author>();
            }

            var createdBook = await _bookRepository.CreateBookAsync(bookEntity, ct);
            return _mapper.Map<BookDto>(createdBook);
        }
            
        public async Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto updateDto, CancellationToken ct)
        {
            var existingBook = await _bookRepository.GetBookByIdAsync(id, ct);
            if (existingBook == null)
            {
                _logger.LogWarning("There is no book with ID {BookId} to update.", id);
                return null;
            }

            _mapper.Map(updateDto, existingBook);

            if (updateDto.AuthorIds?.Count > 0)
            {
                existingBook.Authors.Clear();
                var authors = await _authorRepository.GetAuthorsByIdsAsync(updateDto.AuthorIds, ct);
                existingBook.Authors = authors;
            }

            var updatedBook = await _bookRepository.UpdateBookAsync(existingBook, ct);
            return _mapper.Map<BookDto>(updatedBook);
        }

        public async Task<bool> DeleteBookAsync(int id, CancellationToken ct)
        {
            try
            {
                var bookExist = await _bookRepository.BookExistAsync(id, ct);
                if (!bookExist)
                {
                    _logger.LogWarning($"There is no book with ID {id} to delete.");
                    return false;
                }

                await _bookRepository.DeleteBookAsync(id, ct);
                return true;
            }
            catch(Exception ex)
            {
                _logger.LogError(ex, "Error deleting book with ID {BookId}", id);
                throw;
            }
        }

        public async Task<BookDto?> PatchBookAsync(int id, JsonPatchDocument<UpdateBookDto> patchDocument, CancellationToken ct)
        {
            try
            {
                var existingBook = await _bookRepository.GetBookByIdAsync(id, ct);
                if(existingBook == null)
                {
                    _logger.LogWarning($"There is no book with ID {id}");
                    return null;
                }

                var bookToPatch = _mapper.Map<UpdateBookDto>(existingBook);

                patchDocument.ApplyTo(bookToPatch);

                if (!ValidateBookDto(bookToPatch))
                {
                    _logger.LogWarning("Invalid patch data for book with ID {id}", id);
                    throw new ArgumentException("Invalid patch data");
                }

                _mapper.Map(bookToPatch, existingBook);

                existingBook.UpdatedAt = DateTime.UtcNow;

                // Handle authors if they were patched
                if(bookToPatch.AuthorIds?.Count > 0)
                {
                    existingBook.Authors.Clear();
                    var authors = await _authorRepository.GetAuthorsByIdsAsync(bookToPatch.AuthorIds, CancellationToken ct);
                    existingBook.Authors = authors;
                }

                var patchedBook = await _bookRepository.UpdateBookAsync(existingBook, ct);
                _logger.LogInformation("Book with ID {id} patched successfully. ", id);

                return _mapper.Map<BookDto>(patchedBook);
            }
            catch (JsonPatchException ex)
            {
                _logger.LogError(ex, "JSON patch error for book with ID {BookId}: {Message}", id, ex.Message);
                throw new ArgumentException($"invalid patch operation: {ex.Message}");
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error patching book with ID {BookId}", id);
                throw;
            }
        }

        private bool ValidateBookDto(UpdateBookDto dto)
        {
            if (!string.IsNullOrEmpty(dto.Title) && dto.Title.Length > 200)
                return false;

            if (!string.IsNullOrEmpty(dto.Description) && dto.Description.Length > 500)
                return false;

            if (!string.IsNullOrEmpty(dto.Genre) && dto.Genre.Length > 50)
                return false;

            if (dto.Price.HasValue && dto.Price.Value < 0)
                return false;

            if (dto.StockQuantity.HasValue && dto.StockQuantity.Value < 0)
                return false;

            if (!string.IsNullOrEmpty(dto.Publisher) && dto.Publisher.Length > 100)
                return false;

            if (!string.IsNullOrEmpty(dto.Language) && dto.Language.Length > 50)
                return false;

            return true;
        }

        public IQueryable<Book> GetAllBooksAsQueryable(CancellationToken ct)
        {
            return _bookRepository.GetAllBooksAsQueryable(ct)
                .Include(b => b.Authors)
                .Include(b => b.Reviews)
                .AsNoTracking();
        }
    }
}