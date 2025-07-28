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
using Swashbuckle.AspNetCore.Annotations;

namespace BookStore.Controllers
{
    /// <summary>
    /// Controller for managing orders and order items
    /// </summary>
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

        /// <summary>
        /// Retrieves all orders (Admin/Seller only)
        /// </summary>
        /// <returns>List of all orders</returns>
        /// <response code="200">Returns the list of orders</response>
        /// <response code="404">If no orders are found</response>
        /// <response code="401">If user is not authenticated</response>
        /// <response code="403">If user lacks required role</response>
        [HttpGet] // GET: api/order
        [Authorize(Policy = "ManageBooks")]
        public async Task<ActionResult<IEnumerable<OrderDto>>> GetAllOrders(CancellationToken ct)
        {
            try
            {
                var orders = await _orderService.GetAllOrdersAsync(ct);
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

        /// <summary>
        /// Retrieves a specific order by ID (Admin/Customer only)
        /// </summary>
        /// <param name="id">The ID of the order to retrieve</param>
        /// <returns>The requested order</returns>
        /// <response code="200">Returns the requested order</response>
        /// <response code="404">If order is not found</response>
        /// <response code="401">If user is not authenticated</response>
        /// <response code="403">If user lacks required role</response>
        [HttpGet("{id}")]
        [Authorize(Policy = "AdminOrCustomer")]
        public async Task<IActionResult> GetOrderById(int id, CancellationToken ct)
        {
            try
            {
                var order = await _orderService.GetOrderByIdAsync(id, ct);
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

        /// <summary>
        /// Creates a new order (Customer only)
        /// </summary>
        /// <remarks>
        /// Sample request:
        ///
        ///     POST /api/order
        ///     {
        ///        "customerId": 1,
        ///        "shippingAddress": "123 Main St",
        ///        "orderItems": [
        ///          {
        ///            "bookId": 1,
        ///            "quantity": 2
        ///          }
        ///        ]
        ///     }
        ///
        /// </remarks>
        /// <param name="createOrderDto">The order data</param>
        /// <returns>The newly created order</returns>
        /// <response code="201">Returns the newly created order</response>
        /// <response code="400">If the order data is invalid</response>
        /// <response code="401">If user is not authenticated</response>
        /// <response code="403">If user lacks required role</response>
        [HttpPost]
        [Authorize(Policy = "RequireCustomer")]
        public async Task<ActionResult<OrderDto>> CreateOrder([FromBody] CreateOrderDto createOrderDto, CancellationToken ct)
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

                var createdOrder = await _orderService.CreateOrderAsync(createOrderDto, ct);
                return CreatedAtAction(nameof(GetOrderById), new { id = createdOrder.Id }, createdOrder);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error creating order");
                return StatusCode(500, "Internal server error");
            }
        }

        /// <summary>
        /// Adds an item to an existing order (Customer only)
        /// </summary>
        /// <remarks>
        /// Sample request:
        ///
        ///     POST /api/order/1/items
        ///     {
        ///        "bookId": 2,
        ///        "quantity": 1
        ///     }
        ///
        /// </remarks>
        /// <param name="orderId">The ID of the order to modify</param>
        /// <param name="createOrderItemDto">The order item data</param>
        /// <returns>The updated order</returns>
        /// <response code="200">Returns the updated order</response>
        /// <response code="400">If the order item data is invalid</response>
        /// <response code="404">If order is not found</response>
        /// <response code="401">If user is not authenticated</response>
        /// <response code="403">If user lacks required role</response>
        [HttpPost("{orderId}/items")] // POST: api/order/{orderId}/items
        [Authorize(Policy = "RequireCustomer")]
        public async Task<ActionResult<OrderDto>> AddItemToOrder(int orderId, [FromBody] CreateOrderItemDto createOrderItemDto, CancellationToken ct)
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

                var updatedOrder = await _orderService.AddItemToOrderUsingIdsAsync(orderId, createOrderItemDto.BookId, createOrderItemDto.Quantity, ct);

                if (updatedOrder == null)
                {
                    _logger.LogWarning("Order with ID {OrderId} not found", orderId);
                    return NotFound($"Order with ID {orderId} not found");
                }
                return Ok(updatedOrder);
            }
            catch (System.Collections.Generic.KeyNotFoundException ex)
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