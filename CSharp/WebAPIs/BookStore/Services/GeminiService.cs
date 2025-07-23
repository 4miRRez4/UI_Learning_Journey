//using Google.Api.Gax.Grpc;
//using Google.Cloud.AIPlatform.V1;
//using Microsoft.Extensions.Options;
//using System.Threading.Tasks;

//namespace BookStore.Services
//{
//    public class GeminiService
//    {
//        private readonly IConfiguration _configuration;
//        private readonly string _model = "gemini-2.5-pro";

//        public GeminiService(IConfiguration configuration)
//        {
//            _configuration = configuration;
//        }

//        public async Task<string> GenerateBookDescriptionAsync(string bookTitle, string? bookGenre, string? bookAuthor)
//        {
//            var client = new GenerativeServiceClientBuilder()
//            {
//                ApiKey = _configuration["Gemini:ApiKey"]
//            }.Build();

//            var prompt = @$"
//            You are a creative copywriter for a bookstore.
//            Write a compelling book description for a book with the following details:
//            - Title: {bookTitle}
//            - Author(s): {bookAuthor ?? "Not specified"}
//            - Genre: {bookGenre ?? "Not specified"}

//            The description should be engaging, around 50-80 words, and must not exceed 500 characters.
//            It should entice customers to buy the book.
//            ";

//            var request = new GenerateContentRequest
//            {
//                Model = $"models/{_model}",
//                Contents = { Content.FromText(prompt) }
//            };

//            try
//            {
//                GenerateContentResponse response = await client.GenerateContentAsync(request);
//                string generatedText = response.Candidates.First().Content.Parts.First().Text;
//                return generatedText.Trim();
//            }
//            catch (RpcException ex)
//            {
//                return $"Error: Could not generate description. API returned: {ex.Status.Detail}";
//            }
//        }
//    }
//}