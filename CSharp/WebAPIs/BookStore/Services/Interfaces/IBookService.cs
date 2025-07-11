using BookStore.Dtos.Book;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace BookStore.Services.Interfaces
{

	public interface IBookService
	{
		Task<IEnumerable<BookDto>> GetAllBooksAsync();

		Task<BookDto> GetBookByIdAsync(int id);

		Task<BookDto> CreateBookAsync(CreateBookDto dto);
	}
}