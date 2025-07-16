using BookStore.Models;


namespace BookStore.Repositories.Interfaces
{
    public interface ICustomerRepository
    {
        Task<Customer?> GetCustomerByIdAsync(int id);
        Task<List<Customer>> GetAllCustomersAsync();
        Task<Customer> CreateCustomerAsync(Customer customer);
        Task<bool> CustomerExistsAsync(int id);
        Task DeleteCustomerAsync(int id);
        Task<Customer?> GetCustomerByEmailAsync(string email);
        Task<Customer?> GetCustomerByUserIdAsync(string userId);
           
    }
}