using BookStore.Dtos.Order;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;

namespace BookStore.Services.Interfaces
{
    public interface IOrderService 
    {
        Task<OrderDto> AddItemToOrderUsingIdsAsync(int orderId, int bookId, int quantity);
    }
}