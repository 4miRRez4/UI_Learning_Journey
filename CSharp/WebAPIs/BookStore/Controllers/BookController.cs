using BookStore.Dtos.Book;
using BookStore.Services;
using BookStore.Services.Interfaces;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.JsonPatch;
using Microsoft.IdentityModel.Tokens;
using Microsoft.AspNetCore.Authorization; 

namespace BookStore.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class BookController : ControllerBase
    {
        private readonly IBookService _bookService;
        private readonly ILogger<BookController> _logger;

        public BookController(IBookService bookService, ILogger<BookController> logger)
        {
            _bookService = bookService;
            _logger = logger;
        }

        [HttpGet] // GET: api/book
        [AllowAnonymous] 
        public async Task<ActionResult<IEnumerable<BookDto>>> GetAllBooks(CancellationToken ct)
        {
            var books = await _bookService.GetAllBooksAsync(includeAuthor: true, includeReview: true, ct);

            if (books == null || !books.Any())
            {
                return NotFound("No books found!");
            }

            return Ok(books);
        }

        [HttpGet("{id}")] // Get: api/book/{id}
        [AllowAnonymous]
        public async Task<IActionResult> GetBookById(int id, CancellationToken ct)
        {
            try
            {
                var bookDto = await _bookService.GetBookByIdAsync(id, includeAuthor: true, includeReview: true, ct);

                if (bookDto == null)
                {
                    _logger.LogWarning("Book with ID {BookId} not found", id);
                    return NotFound();
                }

                return Ok(bookDto);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error fetching book with ID {BookId}", id);
                return StatusCode(500, "Internal server error!");
            }
        }

        [HttpGet("search")] // GET: api/book/search
        [AllowAnonymous]
        public async Task<IActionResult> SearchBooksByTitle([FromQuery] string title, CancellationToken ct)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(title))
                {
                    _logger.LogWarning("search title can not be empty.");
                    return BadRequest("Search title cant be empty.");
                }

                var books = await _bookService.SearchBooksByTitleAsync(title, includeAuthor: true, includeReview: true, ct);
                return Ok(books);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error searching books by title {title}");
                return StatusCode(500, "An error occurred while searching books");
            }
        }

        [HttpPost] // POST: api/book
        [Authorize(Policy = "ManageBooks")]
        public async Task<ActionResult<BookDto>> CreateBook([FromBody] CreateBookDto createBookDto, CancellationToken ct)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            try
            {
                var createdBook = await _bookService.CreateBookAsync(createBookDto, ct);

                if (createdBook == null)
                {
                    _logger.LogError("Failed to create book.");
                    return BadRequest("Book creation failed!");
                }

                return CreatedAtAction(nameof(GetAllBooks), new { id = createdBook.Id }, createdBook);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error creating book.");
                return StatusCode(500, $"Internal error: {ex.Message}");
            }
        }


        [HttpPut("{id}")] // PUT: api/book/id
        [Authorize(Policy = "ManageBooks")]
        public async Task<IActionResult> UpdateBook(int id, [FromBody] UpdateBookDto updateDto, CancellationToken ct)
        {
            try
            {
                var updatedBook = await _bookService.UpdateBookAsync(id, updateDto, ct);

                return updatedBook == null ? NotFound() : Ok(updatedBook);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error updating book with ID {BookId}", id);
                return StatusCode(500, $"An error occurred while updating the book: {ex.Message}");
            }
        }

        [HttpPatch("{id}")] // PATCH: api/book/id
        [Authorize(Policy = "ManageBooks")]
        public async Task<IActionResult> PatchBook(int id, [FromBody] JsonPatchDocument<UpdateBookDto> patchDocument, CancellationToken ct)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            if (patchDocument == null)
            {
                return BadRequest("Patch document can not be empty.");
            }

            try
            {
                var patchedBook = await _bookService.PatchBookAsync(id, patchDocument, ct);

                if (patchedBook == null)
                {
                    return NotFound($"Book with Id {id} didn't found.");
                }

                return Ok(patchedBook);
            }
            catch (ArgumentException ex)
            {
                _logger.LogWarning(ex, "Validation error patching book with ID {BookId}", id);
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                _logger.LogWarning(ex, "Error patching book with ID {BookId}", id);
                return StatusCode(500, $"An error occurred while patching the book: {ex.Message}");
            }
        }


        [HttpDelete("{id}")] // DELETE: api/book/id
        [Authorize(Policy = "RequireAdmin")]
        public async Task<IActionResult> DeleteBook(int id, CancellationToken ct)
        {
            try
            {
                var result = await _bookService.DeleteBookAsync(id, ct);

                return result ? NoContent() : NotFound();
            }
            catch (Exception ex)
            {
                return StatusCode(500, "An error occurred while deleting the book");
            }
        }
    }
}