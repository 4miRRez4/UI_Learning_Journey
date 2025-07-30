using BookStore.Models;
using BookStore.Services;
using BookStore.Application.Books.Commands;
using BookStore.GraphQL.Types;
using BookStore.GraphQL.Books.Subscriptions;
using HotChocolate;
using HotChocolate.Types;
using HotChocolate.AspNetCore.Authorization;
using MediatR;
using HotChocolate.Authorization;


namespace BookStore.GraphQL.Mutations
{
    [Authorize(Policy = "ManageBooks")]
	public class BookMutations
	{
        [GraphQLDescription("Adds a new book.")]
        public async Task<BookPayload> AddBookAsync(
			AddBookCommand input,
			[Service] IMediator mediator,
            [Service] BookEvents bookEvents,
			CancellationToken ct)
		{
            try
            {
                var book = await mediator.Send(input, ct);

                bookEvents.NotifyBookAdded(book, ct);

                return new BookPayload(book, null);
            }
            catch (GraphQLException gqlEx)
            {
                var validationErrors = gqlEx.Errors[0].Extensions["errors"] as Dictionary<string, string[]>;

                var userErrors = validationErrors?
                    .SelectMany(error => error.Value.Select(msg => new UserError(error.Key, msg)))
                    .ToList() ?? new List<UserError>();

                return new BookPayload(null, userErrors);
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
            [Service] BookEvents bookEvents,
            CancellationToken ct)
        {
            try
            {
                var book = await mediator.Send(input, ct);

                if (book == null)
                    return new BookPayload(null, new List<UserError> { new("NOT_FOUND", "Book not found") });

                bookEvents.NotifyBookUpdated(book, ct);

                return new BookPayload(book, null);
            }
            catch (GraphQLException gqlEx)
            {
                var validationErrors = gqlEx.Errors[0].Extensions["errors"] as Dictionary<string, string[]>;
                var userErrors = validationErrors?
                    .SelectMany(error => error.Value.Select(msg => new UserError(error.Key, msg)))
                    .ToList() ?? new List<UserError>();

                return new BookPayload(null, userErrors);
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
            catch (GraphQLException gqlEx)
            {
                var validationErrors = gqlEx.Errors[0].Extensions["errors"] as Dictionary<string, string[]>;
                var userErrors = validationErrors?
                    .SelectMany(error => error.Value.Select(msg => new UserError(error.Key, msg)))
                    .ToList() ?? new List<UserError>();

                return new PayloadBase(userErrors);
            }
            catch (Exception ex)
            {
                return new PayloadBase(new List<UserError> { new("DELETE_FAILED", ex.Message) });
            }
        }
    }
}