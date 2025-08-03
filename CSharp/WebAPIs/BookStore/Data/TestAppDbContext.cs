using Microsoft.EntityFrameworkCore;

namespace BookStore.Data
{
    public class TestAppDbContext : AppDbContext
    {
        public TestAppDbContext(DbContextOptions<AppDbContext> options) : base(options) { }

        public override void SeedData(ModelBuilder modelBuilder)
        {
            // intentionally empty. to prevent seeding in tests.
        }
    }
}
