using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Options;
using HotChocolate;

namespace BookStore.GraphQL.Authors.DataLoaders
{
    public class AuthorStatsDataLoader : BatchDataLoader<int, AuthorStatistics>
    {
        private readonly AppDbContext _context;

        public AuthorStatsDataLoader(
            IBatchScheduler batchScheduler,
            AppDbContext context)
            : base(batchScheduler, new DataLoaderOptions())
        {
            _context = context;
        }

        protected override async Task<IReadOnlyDictionary<int, AuthorStatistics>> LoadBatchAsync(
            IReadOnlyList<int> authorIds,
            CancellationToken ct)
        {
            return await _context.Authors
                .Where(a => authorIds.Contains(a.Id))
                .Select(a => new AuthorStatistics
                {
                    AuthorId = a.Id,
                    AuthorName = a.Name,
                    TotalBooks = a.Books.Count(),
                    //TotalReviews = a.Books.SelectMany(b => b.Reviews).Count(),
                    //AverageRating = a.Books.SelectMany(b => b.Reviews)
                    //    .Average(r => (double?)r.Rating) ?? 0.0
                })
                .ToDictionaryAsync(s => s.AuthorId, ct);
        }
    }
}