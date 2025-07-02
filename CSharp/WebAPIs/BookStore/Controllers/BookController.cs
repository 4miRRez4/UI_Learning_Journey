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

        public BookController(IBookService bookService)
        {
            _bookService = bookService;
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

    }
}