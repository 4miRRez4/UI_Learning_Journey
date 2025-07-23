using BookStore.Repositories.Interfaces;
using BookStore.Models;
using BookStore.Data;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace BookStore.Repositories
{
    public class CustomerRepository : ICustomerRepository
    {
        private readonly AppDbContext _context;

        public CustomerRepository(AppDbContext context)
        {
            _context = context;
        }

        public async Task<Customer?> GetCustomerByIdAsync(int id, CancellationToken ct)
        {
            return await _context.Customers
                .Include(c => c.User)
                .Include(c => c.Orders)
                .FirstOrDefaultAsync(c => c.Id == id, ct);
        }

        public async Task<List<Customer>> GetAllCustomersAsync(CancellationToken ct)
        {
            return await _context.Customers
                .Include(c => c.User)
                .Include(c => c.Orders)
                .ToListAsync(ct);
        }
        public async Task<Customer> CreateCustomerAsync(Customer customer, CancellationToken ct)
        {
            _context.Customers.Add(customer);
            await _context.SaveChangesAsync(ct);
            return customer;
        }

        public async Task<bool> CustomerExistsAsync(int id, CancellationToken ct)
        {
            return await _context.Customers.AnyAsync(c => c.Id == id, ct);
        }
        public async Task DeleteCustomerAsync(int id, CancellationToken ct)
        {
            var customer = await GetCustomerByIdAsync(id, ct);
            if (customer != null)
            {
                _context.Customers.Remove(customer);
                await _context.SaveChangesAsync(ct);
            }
        }
        public async Task<Customer?> GetCustomerByEmailAsync(string email, CancellationToken ct)
        {
            return await _context.Customers
                .Include(c => c.User)
                .FirstOrDefaultAsync(c => c.Email == email, ct);
        }

        public async Task<Customer?> GetCustomerByUserIdAsync(string userId, CancellationToken ct)
        {
            return await _context.Customers
                .Include(c => c.User)
                .FirstOrDefaultAsync(c => c.UserId == userId, ct);
        }

        public async Task<Customer?> GetCustomerByUsernameAsync(string username, CancellationToken ct)
        {
            return await _context.Customers
                .Include(c => c.User)
                .FirstOrDefaultAsync(c => c.User.UserName == username, ct);
        }
    }
}