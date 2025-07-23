using BookStore.Models;

namespace BookStore.GraphQL.Types
{

    public record PayloadBase(IReadOnlyList<UserError>? Errors);

    public record BookPayload(
        Book? Book,
        IReadOnlyList<UserError>? Errors);

    public record UserError(
        string Code,
        string Message
        );

}