using MediatR;
using AutoMapper;
using BookStore.Dtos.Book;
using BookStore.Services.Interfaces;
using BookStore.Models;

namespace BookStore.Application.Books.Commands
{
    public class UpdateBookCommandHandler : IRequestHandler<UpdateBookCommand, Book?>
    {
        private readonly IBookService _bookService;
        private readonly IMapper _mapper;

        public UpdateBookCommandHandler(IBookService bookService, IMapper mapper)
        {
            _bookService = bookService;
            _mapper = mapper;
        }

        public async Task<Book?> Handle(UpdateBookCommand request, CancellationToken ct)
        {
            var updateDto = _mapper.Map<UpdateBookDto>(request);
            var resBookDto = await _bookService.UpdateBookAsync(request.Id, updateDto, ct);
            return resBookDto == null ? null : _mapper.Map<Book>(resBookDto);
        }
    }
}