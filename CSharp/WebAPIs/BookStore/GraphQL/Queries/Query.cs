using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;
using HotChocolate;
using HotChocolate.Data;

namespace BookStore.GraphQL
{
    public class Query
    {

        [HotChocolate.Data.UseProjection]
        [HotChocolate.Data.UseFiltering]
        [HotChocolate.Data.UseSorting]    
        public IQueryable<Book> GetBooks([Service] AppDbContext context) =>
            context.Books.Include(b => b.Authors);
    }
}