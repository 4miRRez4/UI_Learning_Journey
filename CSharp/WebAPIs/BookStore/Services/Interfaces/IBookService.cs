using BookStore.Dtos.Book;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{

	public interface IBookService
	{
		// REST
		Task<IEnumerable<BookDto>> GetAllBooksAsync(CancellationToken ct);

		Task<BookDto?> GetBookByIdAsync(int id, CancellationToken ct);

        Task<List<BookDto>> SearchBooksByTitleAsync(string title, CancellationToken ct);

		Task<BookDto> CreateBookAsync(CreateBookDto dto, CancellationToken ct);

		Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto bookDto, CancellationToken ct);

		Task<bool> DeleteBookAsync(int id);

		Task<BookDto?> PatchBookAsync(int id, JsonPatchDocument<UpdateBookDto> patchDocument, CancellationToken ct);
    }
}