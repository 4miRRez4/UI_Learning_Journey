using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using BookStore.Repositories;
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
    }
}