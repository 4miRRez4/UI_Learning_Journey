

namespace BookStore.GraphQL.Types.Inputs
{
    public record AddBookInput
    {
        public string Title { get; set; } = null!;
        public string? Description { get; set; }
        public DateTime? PublishDate { get; set; }
        public string? Genre { get; set; }
        public decimal Price { get; set; }
        public int StockQuantity { get; set; }
        public string? Publisher { get; set; }
        public string? Language { get; set; }
        public List<int>? AuthorIds { get; set; }
    }


    public class AddBookInputType : InputObjectType<AddBookInput>
    {
        protected override void Configure(IInputObjectTypeDescriptor<AddBookInput> descriptor)
        {
            descriptor.Description("Input for adding a new book");

            descriptor.Field(f => f.Title)
                .Description("Title of the book (required)")
                .Type<NonNullType<StringType>>();

            descriptor.Field(f => f.Price)
                .Description("Price of the book (must be positive)")
                .Type<NonNullType<DecimalType>>();

            descriptor.Field(f => f.StockQuantity)
                .Description("Initial stock quantity (must be non-negative)")
                .Type<NonNullType<IntType>>();

            descriptor.Field(f => f.AuthorIds)
                .Description("Optional list of author IDs to associate with the book");
        }
    }
}