using BookStore.Dtos.Auth;

namespace BookStore.Tests.Builders
{
    class AuthResultBuilder
    {
        private AuthResult _authResult = new AuthResult();

        public AuthResultBuilder WithSuccess(bool success)
        {
            _authResult.Success = success;
            return this;
        }

        public AuthResultBuilder withUserId(string userId)
        {
            _authResult.UserId = userId;
            return this;
        }

        public AuthResultBuilder WithError(string error)
        {
            _authResult.Errors = new[] { error };
            return this;
        }

        public AuthResult Build() => _authResult;
    }
}
