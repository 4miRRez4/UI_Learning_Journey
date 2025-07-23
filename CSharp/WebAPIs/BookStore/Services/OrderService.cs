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
using BookStore.Models.Enums;

namespace BookStore.Services
{
    public class OrderService : IOrderService 
    {
        public readonly IOrderRepository _orderRepository;
        public readonly ICustomerRepository _customerRepository;
        public readonly IBookRepository _bookRepository;
        public readonly IMapper _mapper;
        public readonly ILogger<OrderService> _logger;

        public OrderService(IOrderRepository orderRepository, ICustomerRepository customerRepository, IBookRepository bookRepository, IMapper mapper, ILogger<OrderService> logger)
        {
            _orderRepository = orderRepository;
            _bookRepository = bookRepository;
            _customerRepository = customerRepository;
            _mapper = mapper;
            _logger = logger;
        }

        public async Task<IEnumerable<OrderDto>> GetAllOrdersAsync(CancellationToken ct)
        {
            var orders = await _orderRepository.GetAllOrdersAsync(ct);

            if (orders == null || !orders.Any())
            {
                _logger.LogWarning("No orders found.");
                return Enumerable.Empty<OrderDto>();
            }

            foreach (var order in orders)
            {
                order.UpdateOrderTotals();
            }

            return _mapper.Map<IEnumerable<Order>, IEnumerable<OrderDto>>(orders);
        }

        public async Task<OrderDto?> GetOrderByIdAsync(int id, CancellationToken ct)
        {
            var order = await _orderRepository.GetOrderByIdAsync(id, ct);
            if (order == null)
            {
                _logger.LogWarning($"Order with ID {id} not found.");
                return null;
            }
            return _mapper.Map<OrderDto>(order);
        }

        public async Task<OrderDto> CreateOrderAsync(CreateOrderDto createOrderDto, CancellationToken ct)
        {
            var order = _mapper.Map<Order>(createOrderDto);

            var orderCustomer = await _customerRepository.GetCustomerByIdAsync(createOrderDto.CustomerId, ct);
            if (orderCustomer == null)
            {
                _logger.LogWarning($"Customer with ID {createOrderDto.CustomerId} not found");
                throw new System.Collections.Generic.KeyNotFoundException($"Customer with ID {createOrderDto.CustomerId} not found");
            }

            order.Customer = orderCustomer;

            foreach(var item in order.OrderItems)
            {
                var book = await _bookRepository.GetBookByIdAsync(item.BookId, ct);

                if(book == null || book.StockQuantity < item.Quantity)
                {
                    _logger.LogError($"Book with ID {item.BookId} not found or insufficient stock.");
                    throw new System.Collections.Generic.KeyNotFoundException($"Book with ID {item.BookId} not found or insufficient stock.");
                }

                item.Book = book;
                item.UnitPrice = book.Price;
                item.DiscountAmount = 0;
                item.UpdateOrderItemSubtotal();
            }
            order.UpdateOrderTotals();

            order.Status = OrderStatus.Pending;
            order.PaymentStatus = PaymentStatus.Pending;

            var createdOrder = await _orderRepository.CreateOrderAsync(order, ct);
            return _mapper.Map<OrderDto>(createdOrder);
        }


        public async Task<OrderDto> AddItemToOrderUsingIdsAsync(int orderId, int bookId, int quantity, CancellationToken ct)
        {
            var order = await _orderRepository.GetOrderByIdAsync(orderId, ct);
            if (order == null)
            {
                _logger.LogError($"Order with ID {orderId} not found.");
                throw new System.Collections.Generic.KeyNotFoundException($"Order with ID {orderId} not found.");
            }

            var book = await _bookRepository.GetBookByIdAsync(bookId, ct);
            if (book == null) 
            {
                _logger.LogError($"Book with ID {bookId} not found.");
                throw new System.Collections.Generic.KeyNotFoundException($"Book with ID {bookId} not found.");
            }

            order.AddOrderItem(book, quantity);

            await _orderRepository.UpdateOrderAsync(order, ct);

            return _mapper.Map<OrderDto>(order);
        }
    } 
}                  
