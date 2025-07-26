using BookStore.Dtos.Book;
using BookStore.Models;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{

	public interface IBookService
	{
        Task<IEnumerable<BookDto>> GetAllBooksAsync(bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<BookDto?> GetBookByIdAsync(int id, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<IEnumerable<BookDto>> SearchBooksByTitleAsync(string title, bool includeAuthor = false, bool includeReview = false, CancellationToken ct = default);
        Task<BookDto> CreateBookAsync(CreateBookDto dto, CancellationToken ct = default);
        Task<BookDto?> UpdateBookAsync(int id, UpdateBookDto bookDto, CancellationToken ct = default);
        Task<bool> DeleteBookAsync(int id, CancellationToken ct = default);
        Task<BookDto?> PatchBookAsync(int id, JsonPatchDocument<UpdateBookDto> patchDocument, CancellationToken ct = default);


		// GraphQL
		IQueryable<Book> GetAllBooksQueryable(CancellationToken ct = default);
		IQueryable<Book> SearchBooksByTitleQueryable(string title, CancellationToken ct = default);
		IQueryable<Book> GetBooksByGenreQueryable(string genre, CancellationToken ct = default);
    }
}