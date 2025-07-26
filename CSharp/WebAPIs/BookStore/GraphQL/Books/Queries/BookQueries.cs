using BookStore.Models;
using BookStore.Dtos.Book;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Services;
using BookStore.GraphQL.Types.Inputs;
using Microsoft.EntityFrameworkCore;
using HotChocolate;
using HotChocolate.Data;
using HotChocolate.Types;

namespace BookStore.GraphQL.Queries
{
    [ExtendObjectType(OperationTypeNames.Query)]
    public class BookQueries
    {
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooks([Service] IBookService bookService, CancellationToken ct)
            => bookService.GetAllBooksQueryable(ct);



        public async Task<BookDto?> GetBookById(int id, [Service] IBookService bookService, CancellationToken ct)
        {
            return await bookService.GetBookByIdAsync(id, false, false);
        }

        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> SearchBooksByTitle(string title, [Service] IBookService bookService, CancellationToken ct)
            => bookService.SearchBooksByTitleQueryable(title, ct);


        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooksByGenre(string genre, [Service] IBookService bookService, CancellationToken ct)
            => bookService.GetBooksByGenreQueryable(genre, ct);

        [UsePaging]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetFilteredBooks(BookSearchFilter filter, [Service] IBookService bookService, CancellationToken ct)
        {
            var query = bookService.GetAllBooksQueryable();

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