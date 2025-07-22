using BookStore.Models;
using BookStore.Services;
using BookStore.Application.Books.Commands;
using HotChocolate;
using HotChocolate.Types;
using MediatR;


namespace BookStore.GraphQL.Mutations
{
	public class BookMutations
	{
		public async Task<Book> AddBookAsync(
			AddBookCommand input,
			[Service] IMediator mediator,
			CancellationToken ct)
		{
			return await mediator.Send(input, ct);
		}

		public async Task<Book?> UpdateBookAsync(
			UpdateBookCommand input,
			[Service] IMediator mediator,
			CancellationToken ct)
		{
			return await mediator.Send(input, ct);
		}

		public async Task<bool> DeleteBookAsync(
			DeleteBookCommand input,
			[Service] IMediator mediator,
			CancellationToken ct)
		{
			return await mediator.Send(input, ct);
		}
	}
}