
using BookStore.Services.Interfaces;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.VisualStudio.TestPlatform.TestHost;
using Moq;
using Xunit.Abstractions;

namespace BookStore.Tests.Integration
{
    public abstract class ControllerTestBase : IClassFixture<CustomWebApplicationFactory<Program>>
    {
        protected readonly HttpClient Client;
        protected readonly Mock<IAuthService> AuthServiceMock;
        protected readonly ITestOutputHelper Output;

        protected ControllerTestBase(
            CustomWebApplicationFactory<Program> factory,
            ITestOutputHelper output)
        {
            Client = factory.CreateClient(new WebApplicationFactoryClientOptions
            {
                AllowAutoRedirect = false,
                HandleCookies = true
            });
            AuthServiceMock = factory.AuthServiceMock;
            Output = output;

            AuthServiceMock.Invocations.Clear();
        }

        public void Dispose()
        {

        }

    }
}