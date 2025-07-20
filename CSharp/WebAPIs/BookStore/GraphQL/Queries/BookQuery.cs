using BookStore.Models;
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
        //[UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooks([Service] IBookQueryService bookQueryService)
            => bookQueryService.GetAllBooksAsQueryable();



        //[UseDbContext(typeof(AppDbContext))]
        public async Task<Book?> GetBookById(int id, [Service] IBookService bookService)
        {
            return await bookService.GetBookByIdAsync(id);
        }


        //[UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> SearchBooksByTitle(string title, [Service] IBookQueryService bookQueryService)
            => bookQueryService.SearchBooksByTitleAsQueryable(title);


        //[UseDbContext(typeof(AppDbContext))]
        [UsePaging]
        [UseProjection]
        [UseFiltering]
        [UseSorting]
        public IQueryable<Book> GetBooksByGenre(string genre, [Service] IBookQueryService bookQueryService)
            => bookQueryService.GetBooksByGenreAsQueryable(genre);


    }
}