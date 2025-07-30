using HotChocolate.Subscriptions;
using BookStore.Models;

namespace BookStore.GraphQL.Books.Subscriptions
{
    public class BookEvents
    {
        private readonly ITopicEventSender _eventSender;

        public BookEvents(ITopicEventSender eventSender)
        {
            _eventSender = eventSender;
        }

        public async void NotifyBookAdded(Book book, CancellationToken ct)
        {
            await _eventSender.SendAsync("OnBookAdded", book, ct);
        }

        public async void NotifyBookUpdated(Book book, CancellationToken ct)
        {
            await _eventSender.SendAsync("OnBookUpdated", book, ct);
        }
    }
}