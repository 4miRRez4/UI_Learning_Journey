using BookStore.Models;


namespace BookStore.Repositories.Interfaces
{
    public interface IOrderRepository
    {
        Task<Order?> GetOrderByIdAsync(int id);
        Task<List<Order>> GetAllOrdersAsync();
        Task<Order> CreateOrderAsync(Order order);
        Task<Order?> UpdateOrderAsync(Order order);
        Task<bool> OrderExistsAsync(int id);
        Task DeleteOrderAsync(int id);
        Task<List<Order>> GetOrdersByCustomerIdAsync(int customerId);
    }
}