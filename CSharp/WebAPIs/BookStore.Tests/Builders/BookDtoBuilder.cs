using BookStore.Dtos.Author;
using BookStore.Dtos.Book;
using BookStore.Tests.Factories;

namespace BookStore.Tests.Builders
{


    public class BookDtoBuilder
    {
        private readonly BookDto _dto = new();

        public BookDtoBuilder WithId(int id)
        {
            _dto.Id = id;
            return this;
        }

        public BookDtoBuilder WithTitle(string title)
        {
            _dto.Title = title;
            return this;
        }

        public BookDtoBuilder WithDescription(string description)
        {
            _dto.Description = description;
            return this;
        }

        public BookDtoBuilder WithPublishDate(DateTime publishDate)
        {
            _dto.PublishDate = publishDate;
            return this;
        }

        public BookDtoBuilder WithGenre(string genre)
        {
            _dto.Genre = genre;
            return this;
        }

        public BookDtoBuilder WithPrice(decimal price)
        {
            _dto.Price = price;
            return this;
        }

        public BookDtoBuilder WithStockQuantity(int quantity)
        {
            _dto.StockQuantity = quantity;
            return this;
        }

        public BookDtoBuilder WithPublisher(string publisher)
        {
            _dto.Publisher = publisher;
            return this;
        }

        public BookDtoBuilder WithLanguage(string language)
        {
            _dto.Language = language;
            return this;
        }

        public BookDtoBuilder WithAuthors(params AuthorDto[] authors)
        {
            _dto.Authors = authors.ToList();
            return this;
        }

        public BookDtoBuilder WithDefaultValues()
        {
            return this.WithId(1)
                .WithTitle("Default Book")
                .WithDescription("Default Description")
                .WithPublishDate(new DateTime(2020, 1, 1))
                .WithGenre("Fiction")
                .WithPrice(9.99m)
                .WithStockQuantity(10)
                .WithPublisher("Default Publisher")
                .WithLanguage("English")
                .WithAuthors(BookTestDataFactory.CreateAuthorDto());
        }

        public BookDto Build() => _dto;
    }
}
