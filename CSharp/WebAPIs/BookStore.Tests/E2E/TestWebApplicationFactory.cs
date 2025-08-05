using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using BookStore.Data;
using Testcontainers.MsSql;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection.Extensions;

namespace BookStore.Tests.E2E
{
    public class TestWebApplicationFactory : WebApplicationFactory<Program>, IAsyncLifetime
    {
        private readonly MsSqlContainer _dbContainer = new MsSqlBuilder()
            .WithImage("mcr.microsoft.com/mssql/server:2019-latest")
            .WithPassword("Strong(!)Password")
            .Build();

        protected override void ConfigureWebHost(IWebHostBuilder builder)
        {
            builder.ConfigureServices(services =>
            {
                var descriptor = services.SingleOrDefault(
                    d => d.ServiceType == typeof(DbContextOptions<AppDbContext>));
                if (descriptor != null) services.Remove(descriptor);

                services.AddDbContext<TestAppDbContext>(options =>
                {
                    options.UseSqlServer(_dbContainer.GetConnectionString(),
                        sqlOpt => sqlOpt.MigrationsAssembly(typeof(AppDbContext).Assembly.FullName));
                });

                services.AddScoped<AppDbContext>(sp => sp.GetRequiredService<TestAppDbContext>());

                var sp = services.BuildServiceProvider();
                using var scope = sp.CreateScope();
                var db = scope.ServiceProvider.GetRequiredService<TestAppDbContext>();
                db.Database.EnsureCreated();
                db.Database.Migrate();
            });
        }

        public async Task InitializeAsync() => await _dbContainer.StartAsync();
        public new async Task DisposeAsync() => await _dbContainer.DisposeAsync();
    }
}