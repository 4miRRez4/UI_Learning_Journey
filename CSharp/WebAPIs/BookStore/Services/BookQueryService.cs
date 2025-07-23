using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using BookStore.Repositories;
using BookStore.GraphQL.Types.Inputs;
using Microsoft.EntityFrameworkCore;

namespace BookStore.Services
{
    public class BookQueryService : IBookQueryService
    {
        private readonly IBookRepository _bookRepository;
        public BookQueryService(IBookRepository bookRepository)
        {
            _bookRepository = bookRepository;
        }


        public async Task<IQueryable<Book>> GetAllBooksAsQueryable(CancellationToken ct)
        {
            var books = await _bookRepository.GetAllBooksAsQueryable(ct);
            return books.AsNoTracking();
        }

        public async Task<IQueryable<Book>> SearchBooksByTitleAsQueryable(string title, CancellationToken ct)
        {
            var books = await GetAllBooksAsQueryable(ct);
            return books.Where(b => b.Title.Contains(title));
        }

        public async Task<IQueryable<Book>> GetBooksByGenreAsQueryable(string genre, CancellationToken ct)
        {
            var books = await GetAllBooksAsQueryable(ct);
            return books.Where(b => b.Genre == genre);
        }

        public async Task<IQueryable<Book>> GetFilteredBooks(BookSearchFilter filter, CancellationToken ct)
        {
            var query = _bookRepository.GetAllBooksAsQueryable(ct);

            if (!string.IsNullOrEmpty(filter.Title))
            {
                query = query.Where(b => b.Title.Contains(filter.Title));
            }

            if (!string.IsNullOrEmpty(filter.Genre))
            {
                query = query.Where(b => b.Genre == filter.Genre);
            }

            if (filter.AuthorId.HasValue)
            {
                query = query.Where(b => b.Authors.Any(a => a.Id == filter.AuthorId));
            }

            return query;
        }
    }
}