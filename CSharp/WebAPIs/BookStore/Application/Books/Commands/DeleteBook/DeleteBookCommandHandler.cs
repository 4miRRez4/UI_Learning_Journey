using MediatR;
using BookStore.Services.Interfaces;

namespace BookStore.Application.Books.Commands
{
    public class DeleteBookCommandHandler : IRequestHandler<DeleteBookCommand, bool>
    {
        private readonly IBookService _bookService;

        public DeleteBookCommandHandler(IBookService bookService)
        {
            _bookService = bookService;
        }

        public async Task<bool> Handle(DeleteBookCommand request, CancellationToken cancellationToken)
        {
            return await _bookService.DeleteBookAsync(request.Id);
        }
    }
}