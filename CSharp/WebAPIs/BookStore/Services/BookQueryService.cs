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


        public IQueryable<Book> GetAllBooksAsQueryable()
        {
            return _bookRepository.GetAllBooksAsQueryable()
                .AsNoTracking();
        }

        public IQueryable<Book> SearchBooksByTitleAsQueryable(string title)
        {
            return GetAllBooksAsQueryable().Where(b => b.Title.Contains(title));
        }

        public IQueryable<Book> GetBooksByGenreAsQueryable(string genre)
        {
            return GetAllBooksAsQueryable().Where(b => b.Genre == genre);
        }

        public IQueryable<Book> GetFilteredBooks(BookSearchFilter filter)
        {
            var query = _bookRepository.GetAllBooksAsQueryable();

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