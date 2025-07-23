using BookStore.Models;
using BookStore.Services;
using BookStore.Application.Books.Commands;
using BookStore.GraphQL.Types;
using HotChocolate;
using HotChocolate.Types;
using MediatR;


namespace BookStore.GraphQL.Mutations
{
	public class BookMutations
	{
        [GraphQLDescription("Adds a new book.")]
        public async Task<BookPayload> AddBookAsync(
			AddBookCommand input,
			[Service] IMediator mediator,
			CancellationToken ct)
		{
            try
            {
                var book = await mediator.Send(input, ct);
                return new BookPayload(book, null);
            }
            catch (Exception ex)
            {
                return new BookPayload(
                    null,
                    new List<UserError> { new("ADD_FAILED", ex.Message) });
            }
        }

        [GraphQLDescription("Updates an existing book.")]
        public async Task<BookPayload> UpdateBookAsync(
            UpdateBookCommand input,
            [Service] IMediator mediator,
            CancellationToken ct)
        {
            try
            {
                var book = await mediator.Send(input, ct);
                return book is null
                    ? new BookPayload(null, new List<UserError> { new("NOT_FOUND", "Book not found") })
                    : new BookPayload(book, null);
            }
            catch (Exception ex)
            {
                return new BookPayload(
                    null,
                    new List<UserError> { new("UPDATE_FAILED", ex.Message) });
            }
        }

        [GraphQLDescription("Deletes a book.")]
        public async Task<PayloadBase> DeleteBookAsync(
            DeleteBookCommand input,
            [Service] IMediator mediator,
            CancellationToken ct)
        {
            try
            {
                bool success = await mediator.Send(input, ct);
                return success
                    ? new PayloadBase(null)
                    : new PayloadBase(new List<UserError> { new("NOT_FOUND", "Book not found") });
            }
            catch (Exception ex)
            {
                return new PayloadBase(new List<UserError> { new("DELETE_FAILED", ex.Message) });
            }
        }
    }
}