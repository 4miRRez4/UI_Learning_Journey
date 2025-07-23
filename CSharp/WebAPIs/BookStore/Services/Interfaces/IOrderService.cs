using BookStore.Dtos.Order;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{
    public interface IOrderService 
    {
        Task<IEnumerable<OrderDto>> GetAllOrdersAsync(CancellationToken ct);
        Task<OrderDto?> GetOrderByIdAsync(int id, CancellationToken ct);
        Task<OrderDto> CreateOrderAsync(CreateOrderDto createOrderDto, CancellationToken ct);

        Task<OrderDto> AddItemToOrderUsingIdsAsync(int orderId, int bookId, int quantity, CancellationToken ct);
    }
}