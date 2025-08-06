
using BookStore.Dtos.Auth;
using Org.BouncyCastle.Asn1.Mozilla;

namespace BookStore.Tests.Builders
{
    public class UserRegisterDtoBuilder
    {
        private readonly RegisterDto _user = new();
        
        public UserRegisterDtoBuilder WithUserName(string username)
        {
            _user.UserName = username;
            return this;
        }

        public UserRegisterDtoBuilder WithEmail(string email)
        {
            _user.Email = email;
            return this;
        }

        public UserRegisterDtoBuilder WithPassword(string password)
        {
            _user.Password = password;
            _user.ConfirmPassword = password;
            return this;
        }

        public RegisterDto Build() => _user;
    }
}
