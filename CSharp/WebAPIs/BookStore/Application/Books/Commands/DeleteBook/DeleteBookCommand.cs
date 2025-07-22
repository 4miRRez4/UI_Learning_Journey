using MediatR;

namespace BookStore.Application.Books.Commands
{
    public class DeleteBookCommand : IRequest<bool>
    {
        public int Id { get; set; }
    }
}