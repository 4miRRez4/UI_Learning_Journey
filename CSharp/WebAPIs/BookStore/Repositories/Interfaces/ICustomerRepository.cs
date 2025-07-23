using BookStore.Models;


namespace BookStore.Repositories.Interfaces
{
    public interface ICustomerRepository
    {
        Task<Customer?> GetCustomerByIdAsync(int id, CancellationToken ct);
        Task<List<Customer>> GetAllCustomersAsync(CancellationToken ct);
        Task<Customer> CreateCustomerAsync(Customer customer, CancellationToken ct);
        Task<bool> CustomerExistsAsync(int id, CancellationToken ct);
        Task DeleteCustomerAsync(int id, CancellationToken ct);
        Task<Customer?> GetCustomerByEmailAsync(string email, CancellationToken ct);
        Task<Customer?> GetCustomerByUserIdAsync(string userId, CancellationToken ct);
           
    }
}