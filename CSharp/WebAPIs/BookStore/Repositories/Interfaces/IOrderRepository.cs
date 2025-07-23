using BookStore.Models;


namespace BookStore.Repositories.Interfaces
{
    public interface IOrderRepository
    {
        Task<Order?> GetOrderByIdAsync(int id, CancellationToken ct);
        Task<List<Order>> GetAllOrdersAsync(CancellationToken ct);
        Task<Order> CreateOrderAsync(Order order, CancellationToken ct);
        Task<Order?> UpdateOrderAsync(Order order, CancellationToken ct);
        Task<bool> OrderExistsAsync(int id, CancellationToken ct);
        Task DeleteOrderAsync(int id, CancellationToken ct);
        Task<List<Order>> GetOrdersByCustomerIdAsync(int customerId, CancellationToken ct);
    }
}