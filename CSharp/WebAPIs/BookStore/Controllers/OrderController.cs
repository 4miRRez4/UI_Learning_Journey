using BookStore.Dtos.Order;
using BookStore.Services.Interfaces;
using BookStore.Services;
using BookStore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.JsonPatch;
using Microsoft.IdentityModel.Tokens;
using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;
using Microsoft.IdentityModel.Tokens;
using Microsoft.AspNetCore.Identity;

namespace BookStore.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize]
    public class OrderController : ControllerBase
    {
        private readonly IOrderService _orderService;
        private readonly ILogger<OrderController> _logger;

        public OrderController(IOrderService orderService, ILogger<OrderController> logger)
        {
            _orderService = orderService;
            _logger = logger;
        }

        [HttpGet] // GET: api/order
        [Authorize(Roles = UserRoles.Admin + "," + UserRoles.Seller)]
        public async Task<ActionResult<IEnumerable<OrderDto>>> GetAllOrders()
        {
            try
            {
                var orders = await _orderService.GetAllOrdersAsync();
                if (orders == null || !orders.Any())
                {
                    return NotFound("No orders found!");
                }
                return Ok(orders);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error retrieving all orders");
                return StatusCode(500, "Internal server error");
            }
        }

        [HttpGet("{id}")]
        [Authorize(UserRoles.Admin + "," + UserRoles.Customer)]
        public async Task<IActionResult> GetOrderById(int id)
        {
            try
            {
                var order = await _orderService.GetOrderByIdAsync(id);
                if (order == null)
                {
                    _logger.LogWarning("Order with ID {OrderId} not found", id);
                    return NotFound();
                }
                return Ok(order);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error fetching order with ID {OrderId}", id);
                return StatusCode(500, "Internal server error");
            }
        }

        [HttpPost]
        [Authorize(Roles = UserRoles.Customer)]
        public async Task<ActionResult<OrderDto>> CreateOrder([FromBody] CreateOrderDto createOrderDto)
        {
            if (createOrderDto == null)
            {
                return BadRequest("Order data is null");
            }
            try
            {
                if (!ModelState.IsValid)
                {
                    _logger.LogWarning("Invalid model state for order creation");
                    return BadRequest(ModelState);
                }

                var createdOrder = await _orderService.CreateOrderAsync(createOrderDto);
                return CreatedAtAction(nameof(GetOrderById), new { id = createdOrder.Id }, createdOrder);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error creating order");
                return StatusCode(500, "Internal server error");
            }
        }

        [HttpPost("{orderId}/items")] // POST: api/order/{orderId}/items
        [Authorize(UserRoles.Customer)]
        public async Task<ActionResult<OrderDto>> AddItemToOrder(int orderId, [FromBody] CreateOrderItemDto createOrderItemDto)
        {
            if (createOrderItemDto == null)
            {
                return BadRequest("Order item data is null");
            }

            try
            {
                if (!ModelState.IsValid)
                {
                    _logger.LogWarning("Invalid model state for adding item to order");
                    return BadRequest(ModelState);
                }

                var updatedOrder = await _orderService.AddItemToOrderUsingIdsAsync(orderId, createOrderItemDto.BookId, createOrderItemDto.Quantity);

                if (updatedOrder == null)
                {
                    _logger.LogWarning("Order with ID {OrderId} not found", orderId);
                    return NotFound($"Order with ID {orderId} not found");
                }
                return Ok(updatedOrder);
            }
            catch (KeyNotFoundException ex)
            {
                _logger.LogWarning(ex.Message);
                return NotFound(ex.Message);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error adding item to order with ID {OrderId}", orderId);
                return StatusCode(500, "Internal server error");
            }
        }

    }
}