using HotChocolate;
using HotChocolate.Types;
using BookStore.Models;

namespace BookStore.GraphQL
{
    public partial class Subscription
    {
        [Subscribe]
        [Topic("OnBookAdded")]
        public Book OnBookAdded([EventMessage] Book book)
        {
            return book;
        }

        [Subscribe]
        [Topic("OnBookUpdated")]
        public Book OnBookUpdated([EventMessage] Book book)
        {
            return book;
        }
    }
}