using BookStore.Dtos.Order;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{
    public interface IOrderService 
    {
        Task<IEnumerable<OrderDto>> GetAllOrdersAsync();
        Task<OrderDto?> GetOrderByIdAsync(int id);
        Task<OrderDto> CreateOrderAsync(CreateOrderDto createOrderDto);

        Task<OrderDto> AddItemToOrderUsingIdsAsync(int orderId, int bookId, int quantity);
    }
}