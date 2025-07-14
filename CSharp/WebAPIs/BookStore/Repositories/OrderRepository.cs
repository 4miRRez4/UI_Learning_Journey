using BookStore.Repositories.Interfaces;
using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;

namespace BookStore.Repositories
{
    public class OrderRepository : IOrderRepository
    {
        private readonly AppDbContext _context;

        public OrderRepository(AppDbContext context)
        {
            _context = context;
        }

        public async Task<Order> CreateOrderAsync(Order order)
        {
            await _context.Orders.AddAsync(order);
            await _context.SaveChangesAsync();
            return order;
        }

        public async Task<bool> OrderExistsAsync(int id)
        {
            return await _context.Orders.AnyAsync(o => o.Id == id);
        }

        public async Task DeleteOrderAsync(int id)
        {
            var order = await _context.Orders.FindAsync(id);
            if (order != null)
            {
                _context.Orders.Remove(order);
                await _context.SaveChangesAsync();
            }
        }

        public async Task<List<Order>> GetOrdersByCustomerIdAsync(int customerId)
        {
            return await _context.Orders
                .Where(o => o.CustomerId == customerId)
                .Include(o => o.OrderItems)
                .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .ToListAsync();
        }

        public async Task<Order?> GetOrderByIdAsync(int id)
        {
            return await _context.Orders
                .Include(o => o.OrderItems)
                .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .FirstOrDefaultAsync(o => o.Id == id);
        }

        public async Task<List<Order>> GetAllOrdersAsync()
        {
            return await _context.Orders
                .Include(o => o.OrderItems)
                .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .ToListAsync();
        }

        public async Task<Order?> UpdateOrderAsync(Order order)
        {
            _context.Orders.Update(order);
            await _context.SaveChangesAsync();
            return order;
        }
    }
}