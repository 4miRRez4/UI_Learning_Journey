
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
            return _bookRepository.GetAllBooks()
                .AsNoTracking();
        }

        public IQueryable<Book> SearchBooksByTitle(string title)
        {
            return GetAllBooksAsQueryable().Where(b => b.Title.Contains(title));
        }

        public IQueryable<Book> GetBooksByGenre(string genre)
        {
            return GetAllBooksAsQueryable().Where(b => b.Genre == genre);
        }
    }
}