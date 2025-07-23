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

        public async Task<Order> CreateOrderAsync(Order order, CancellationToken ct)
        {
            await _context.Orders.AddAsync(order, ct);
            await _context.SaveChangesAsync(ct);
            return order;
        }

        public async Task<bool> OrderExistsAsync(int id, CancellationToken ct)
        {
            return await _context.Orders.AnyAsync(o => o.Id == id, ct);
        }

        public async Task DeleteOrderAsync(int id, CancellationToken ct)
        {
            var order = await _context.Orders.FindAsync(new object[] { id }, ct);
            if (order != null)
            {
                _context.Orders.Remove(order);
                await _context.SaveChangesAsync(ct);
            }
        }



        public async Task<List<Order>> GetOrdersByCustomerIdAsync(int customerId, CancellationToken ct)
        {
            return await _context.Orders
                .Where(o => o.CustomerId == customerId)
                .Include(o => o.OrderItems)
                .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .ToListAsync(ct);
        }

        public async Task<Order?> GetOrderByIdAsync(int id, CancellationToken ct)
        {
            return await _context.Orders
                .Include(o => o.OrderItems)
                    .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .FirstOrDefaultAsync(o => o.Id == id, ct);
        }

        public async Task<List<Order>> GetAllOrdersAsync(CancellationToken ct)
        {
            return await _context.Orders
                .Include(o => o.OrderItems)
                .ThenInclude(oi => oi.Book)
                .Include(o => o.Customer)
                .AsNoTracking()
                .ToListAsync(ct);
        }

        public async Task<Order?> UpdateOrderAsync(Order order, CancellationToken ct)
        {
            _context.Orders.Update(order);
            await _context.SaveChangesAsync(ct);
            return order;
        }
    }
}