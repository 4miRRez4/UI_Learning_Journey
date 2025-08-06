using BookStore.Data;
using Microsoft.EntityFrameworkCore;
using Testcontainers.MsSql;

namespace BookStore.Tests.Fixtures
{
    public class DatabaseFixture : IAsyncLifetime
    {
        public MsSqlContainer DbContainer { get; }
        public TestAppDbContext DbContext { get; private set; }

        public DatabaseFixture()
        {
            DbContainer = new MsSqlBuilder()
                .WithImage("mcr.microsoft.com/mssql/server:2019-latest")
                .WithPassword("Strong(!)Password")
                .Build();
        }

        public async Task InitializeAsync()
        {
            await DbContainer.StartAsync();

            var options = new DbContextOptionsBuilder<TestAppDbContext>()
                .UseSqlServer(DbContainer.GetConnectionString(),
                 sqlServerOptions => sqlServerOptions.MigrationsAssembly(typeof(TestAppDbContext).Assembly.FullName))
                .Options;

            DbContext = new TestAppDbContext(options);

            await DbContext.Database.EnsureCreatedAsync();
            await DbContext.Database.MigrateAsync();
        }

        public async Task DisposeAsync()
        {
            await DbContainer.DisposeAsync();
            await DbContext.DisposeAsync();
        }
    }
}