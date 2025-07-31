

using BookStore.Models;
using BookStore.Repositories.Interfaces;
using Microsoft.Extensions.Configuration;
using Microsoft.AspNetCore.Identity;
using Moq;

namespace BookStore.Tests.Fixtures
{
    public class AuthServiceFixture : IDisposable
    {
        public Mock<UserManager<ApplicationUser>> UserManagerMock { get; }
        public Mock<RoleManager<ApplicationRole>> RoleManagerMock { get; }
        public Mock<ICustomerRepository> CustomerRepositoryMock { get; }
        public Mock<IConfiguration> ConfigurationMock { get; }

        public AuthServiceFixture()
        {
            var userStoreMock = new Mock<IUserStore<ApplicationUser>>();
            UserManagerMock = new Mock<UserManager<ApplicationUser>>(userStoreMock.Object, null, null, null, null, null, null, null, null);
            
            var roleStoreMock = new Mock<IRoleStore<ApplicationRole>>();
            RoleManagerMock = new Mock<RoleManager<ApplicationRole>>(roleStoreMock.Object, null, null, null, null);
            
            CustomerRepositoryMock = new Mock<ICustomerRepository>();
            ConfigurationMock = new Mock<IConfiguration>();

            ConfigurationMock.Setup(x => x["Jwt:Key"]).Returns("6D5A7134743777217A25432A462D4A614E645267556B58703272357538666666");
            ConfigurationMock.Setup(x => x["Jwt:Issuer"]).Returns("TestIssuer");
            ConfigurationMock.Setup(x => x["Jwt:Audience"]).Returns("TestAudience");
            ConfigurationMock.Setup(x => x["Jwt:ExpireDays"]).Returns("7");
        }

        public void Dispose()
        {

        }
    }


}