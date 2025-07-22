using MediatR;
using BookStore.Models;
using BookStore.Services.Interfaces;
using AutoMapper;
using BookStore.Dtos.Book;

namespace BookStore.Application.Books.Commands
{
    public class AddBookCommandHandler : IRequestHandler<AddBookCommand, Book>
    {
        private readonly IBookService _bookService;
        private readonly IMapper _mapper;

        public AddBookCommandHandler(IBookService bookService, IMapper mapper)
        {
            _bookService = bookService;
            _mapper = mapper;
        }

        public async Task<Book> Handle(AddBookCommand request, CancellationToken cancellationToken)
        {
            var createDto = _mapper.Map<CreateBookDto>(request);
            var resBookDto = await _bookService.CreateBookAsync(createDto);
            return _mapper.Map<Book>(resBookDto);
        }
    }
}