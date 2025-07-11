using BookStore.Dtos.Book;
using BookStore.Services;
using BookStore.Services.Interfaces;
using Microsoft.AspNetCore.Mvc;

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
        public async Task<ActionResult<IEnumerable<BookDto>>> GetAllBooks()
        {
            var books = await _bookService.GetAllBooksAsync();

            if(books == null || !books.Any())
            {
                return NotFound("No books found!");
            }

            return Ok(books);
        }

        [HttpGet("{id}")] // Get: api/book/{id}
        public async Task<IActionResult> GetBookById(int id)
        {
            try
            {
                var bookDto = await _bookService.GetBookByIdAsync(id);

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

        [HttpPost] // POST: api/book
        public async Task<ActionResult<BookDto>> CreateBook([FromBody] CreateBookDto createBookDto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            try
            {
                var createdBook = await _bookService.CreateBookAsync(createBookDto);

                if(createdBook == null)
                {
                    return BadRequest("Book creation failed!");
                }

                return CreatedAtAction(nameof(GetAllBooks), new { id = createdBook.Id }, createdBook);
            }
            catch(Exception ex)
            {
                return StatusCode(500, $"Internal error: {ex.Message}");
            }
        }


        [HttpPut("{id}")] // PUT: api/book/id
        public async Task<IActionResult> UpdateBook(int id, [FromBody] UpdateBookDto updateDto)
        {
            try 
            {
                var updatedBook = await _bookService.UpdateBookAsync(id, updateDto);

                return updatedBook == null ? NotFound() : Ok(updatedBook);
            }
            catch (Exception ex)
            {
                //return StatusCode(500, $"An error occurred while updating the book with ID {id} : {ex.Message}");
                string errorDetails = ex.Message;
                while (ex.InnerException != null)
                {
                    ex = ex.InnerException;
                    errorDetails += $"\nInner Exception: {ex.Message}";
                }
                return StatusCode(500, $"Error updating book {id}: {errorDetails}");

            }
        }

    }
}