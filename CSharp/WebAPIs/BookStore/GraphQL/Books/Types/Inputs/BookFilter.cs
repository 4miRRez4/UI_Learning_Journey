
namespace BookStore.GraphQL.Types.Inputs
{
    public record BookSearchFilter(
        string? Title,
        string? Genre,
        int? AuthorId);

}