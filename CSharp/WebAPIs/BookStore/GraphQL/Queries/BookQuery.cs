using BookStore.Models;
using BookStore.Dtos.Book;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Services;
using Microsoft.EntityFrameworkCore;
using HotChocolate;
using HotChocolate.Data;
using HotChocolate.Types;

namespace BookStore.GraphQL.Queries
{
    [ExtendObjectType(OperationTypeNames.Query)]
    public class BookQuery
    {
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooks([Service] IBookQueryService bookQueryService)
            => bookQueryService.GetAllBooksAsQueryable();



        public async Task<BookDto?> GetBookById(int id, [Service] IBookService bookService)
        {
            return await bookService.GetBookByIdAsync(id);
        }

        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> SearchBooksByTitle(string title, [Service] IBookQueryService bookQueryService)
            => bookQueryService.SearchBooksByTitleAsQueryable(title);


        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooksByGenre(string genre, [Service] IBookQueryService bookQueryService)
            => bookQueryService.GetBooksByGenreAsQueryable(genre);


    }
}