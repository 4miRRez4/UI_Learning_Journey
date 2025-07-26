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



        public async Task<IEnumerable<BookDto>> GetAllBooksAsync(
            bool includeAuthors = false, 
            bool includeReviews = false,
            CancellationToken ct = default)
        {
            try
            {
                var books = await _bookRepository.GetAllBooksAsync(includeAuthors, includeReviews, ct);
                return _mapper.Map<IEnumerable<BookDto>>(books);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error getting all books");
                throw;
            }
        }

        public async Task<BookDto?> GetBookByIdAsync(int id, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default)
        {
            try
            {
                var bookEntity = await _bookRepository.GetBookByIdAsync(id, includeAuthor, includeReview, ct);
                return bookEntity == null ? null : _mapper.Map<BookDto>(bookEntity);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error getting book by id {BookId}", id);
                throw;
            }
        }

        public async Task<IEnumerable<BookDto>> SearchBooksByTitleAsync(string title, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default)
        {
            try
            {
                var books = await _bookRepository.SearchBooksByTitleAsync(title, includeAuthor, includeReview, ct);
                return _mapper.Map<List<BookDto>>(books);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error searching books by title '{Title}'", title);
                throw;
            }
        }

        public async Task<BookDto> CreateBookAsync(CreateBookDto bookDto, CancellationToken ct)
        {
            try
            {
                var bookEntity = _mapper.Map<Book>(bookDto);

                if (bookDto.AuthorIds?.Count > 0)
                {
                    var authors = await _authorRepository.GetAuthorsByIdsAsync(bookDto.AuthorIds, ct);
                    bookEntity.Authors = authors ?? new List<Author>();
                }

                var createdBook = await _bookRepository.CreateBookAsync(bookEntity, ct);
                return _mapper.Map<BookDto>(createdBook);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error creating book");
                throw;
            }
        }

        public async Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto updateDto, CancellationToken ct)
        {
            try
            {
                var existingBook = await _bookRepository.GetBookByIdAsync(id, includeAuthor: true, includeReview: true, ct);
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
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error updating book with ID {BookId}", id);
                throw;
            }
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
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error deleting book with ID {BookId}", id);
                throw;
            }
        }

        public async Task<BookDto?> PatchBookAsync(int id, JsonPatchDocument<UpdateBookDto> patchDocument, CancellationToken ct)
        {
            try
            {
                var existingBook = await _bookRepository.GetBookByIdAsync(id, includeAuthor: true, includeReview: true, ct);
                if (existingBook == null)
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
                if (bookToPatch.AuthorIds?.Count > 0)
                {
                    existingBook.Authors.Clear();
                    var authors = await _authorRepository.GetAuthorsByIdsAsync(bookToPatch.AuthorIds, ct);
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

        #region GraphQL Methods (IQueryable)
        public IQueryable<Book> GetAllBooksQueryable(CancellationToken ct)
        {
            try
            {
                return _bookRepository.GetAllBooksQueryable(includeAuthor: false, includeReview: false, ct)
                    .AsNoTracking();
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error getting all books as queryable");
                throw;
            }
        }

        public IQueryable<Book> SearchBooksByTitleQueryable(string title, CancellationToken ct)
        {
            try
            {
                return _bookRepository.SearchBooksByTitleQueryable(title, includeAuthor: false, includeReview: false, ct)
                    .AsNoTracking();
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error searching books by title as queryable");
                throw;
            }
        }

        public IQueryable<Book> GetBooksByGenreQueryable(string genre, CancellationToken ct)
        {
            try
            {
                return _bookRepository.GetBooksByGenreQueryable(genre, includeAuthor: false, includeReview: false, ct)
                    .AsNoTracking();
            }   
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error getting books by genre as queryable");
                throw;
            }
        }

        #endregion
    }
}