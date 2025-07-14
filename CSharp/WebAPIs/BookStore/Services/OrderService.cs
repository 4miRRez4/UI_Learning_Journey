using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.JsonPatch;
using Microsoft.AspNetCore.JsonPatch.Exceptions;
using AutoMapper;
using BookStore.Data;
using BookStore.Services.Interfaces;
using BookStore.Models;
using BookStore.Repositories.Interfaces;
using System.Collections.Generic;
using System.Threading.Tasks;
using BookStore.Dtos.Order;

namespace BookStore.Services
{
    public class OrderService : IOrderService 
    {
        public readonly IOrderRepository _orderRepository;
        public readonly IBookRepository _bookRepository;
        public readonly IMapper _mapper;
        public readonly ILogger _logger;

        public OrderService(IOrderRepository orderRepository, IBookRepository bookRepository, IMapper mapper, ILogger logger)
        {
            _orderRepository = orderRepository;
            _mapper = mapper;
            _logger = logger;
        }

        public async Task<OrderDto> AddItemToOrderUsingIdsAsync(int orderId, int bookId, int quantity)
        {
            var order = await _orderRepository.GetOrderByIdAsync(orderId);
            if (order == null)
            {
                _logger.LogError($"Order with ID {orderId} not found.");
                throw new KeyNotFoundException($"Order with ID {orderId} not found.");
            }

            var book = await _bookRepository.GetBookByIdAsync(bookId);
            if (book == null) 
            {
                _logger.LogError($"Book with ID {bookId} not found.");
                throw new KeyNotFoundException($"Book with ID {bookId} not found.");
            }

            order.AddOrderItem(book, quantity);

            await _orderRepository.UpdateOrderAsync(order);

            return _mapper.Map<OrderDto>(order);
        }
}                   
