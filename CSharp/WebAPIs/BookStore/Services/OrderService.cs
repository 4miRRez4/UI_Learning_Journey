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

        public async Task<IEnumerable<OrderDto>> GetAllOrdersAsync()
        {
            var orders = await _orderRepository.GetAllOrdersAsync();
            return _mapper.Map<IEnumerable<OrderDto>>(orders);
        }

        public async Task<OrderDto?> GetOrderByIdAsync(int id)
        {
            var order = await _orderRepository.GetOrderByIdAsync(id);
            if (order == null)
            {
                _logger.LogWarning($"Order with ID {id} not found.");
                return null;
            }
            return _mapper.Map<OrderDto>(order);
        }

        public async Task<OrderDto> CreateOrderAsync(CreateOrderDto createOrderDto)
        {
            var order = _mapper.Map<Order>(createOrderDto);
            var createdOrder = await _orderRepository.CreateOrderAsync(order);
            return _mapper.Map<OrderDto>(createdOrder);
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
