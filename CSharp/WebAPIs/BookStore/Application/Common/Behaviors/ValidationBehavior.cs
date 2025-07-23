using FluentValidation;
using MediatR;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;


namespace BookStore.Application.Common.Behaviors
{
    public class ValidationBehavior<TRequest, TResponse> : IPipelineBehavior<TRequest, TResponse>
        where TRequest : IRequest<TResponse>
    {

        public async Task<TResponse> Handle(
            TRequest request,
            RequestHandlerDelegate<TResponse> next,
            CancellationToken ct)
        {
            var validationContext = new ValidationContext(request);
            var validationResults = new List<ValidationResult>();

            if(!Validator.TryValidateObject(request, validationContext, validationResults, true))
            {
                var errors = validationResults
                    .SelectMany(r => r.MemberNames
                        .Select(m => new { Member = m, Error = r.ErrorMessage }))
                    .GroupBy(x => x.Member)
                    .ToDictionary(
                        g => g.Key,
                        g => g.Select(x => x.Error).ToArray());

                throw new GraphQLException(
                    ErrorBuilder.New()
                        .SetMessage("Validation errors occurred.")
                        .SetCode("VALIDATION_ERROR")
                        .SetExtension("errors", errors)
                        .Build());
            }

            return await next();
        }
    }
}