using BookStore.Authorization;

namespace BookStore.Dtos.Auth
{
    public class AuthResult
    {
        public bool Success { get; set; }
        public string? Token { get; set; }
        public DateTime? TokenExpiry {  get; set; }
        public string? UserId { get; set; }
        public int? CustomerId { get; set; }
        public IEnumerable<string>? Errors { get; set; }
        public List<string>? Roles { get; set; }
    }

}