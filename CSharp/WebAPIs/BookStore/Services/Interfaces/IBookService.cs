using BookStore.Dtos.Book;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{

	public interface IBookService
	{
		// REST
		Task<IEnumerable<BookDto>> GetAllBooksAsync();

		Task<BookDto?> GetBookByIdAsync(int id);

        Task<List<BookDto>> SearchBooksByTitleAsync(string title);

		Task<BookDto> CreateBookAsync(CreateBookDto dto);

		Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto bookDto);

		Task<bool> DeleteBookAsync(int id);

		Task<BookDto?> PatchBookAsync(int id, JsonPatchDocument<UpdateBookDto> patchDocument);
    }
}