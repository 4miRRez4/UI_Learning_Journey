using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data;
using BookStore.Models.Enums;

namespace BookStore.Models
{
    public class Order
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public int CustomerId { get; set; }

        [Required]
        public DateTime OrderDate { get; set; } = DateTime.UtcNow;

        [Required]
        public OrderStatus Status { get; set; } = OrderStatus.Pending;

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal TotalAmount { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal Subtotal { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal TaxAmount { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal ShippingAmount { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal DiscountAmount { get; set; }

        [Required]
        public PaymentStatus PaymentStatus { get; set; } = PaymentStatus.Pending;

        [MaxLength(50)]
        public string? PaymentMethod { get; set; }

        [MaxLength(100)]
        public string? TransactionId { get; set; }

        [MaxLength(200)]
        public string ShippingAddress { get; set; }


        [MaxLength(50)]
        public string? ShippingMethod { get; set; }

        [MaxLength(500)]
        public string? Notes { get; set; }

        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        public DateTime UpdatedAt { get; set; } = DateTime.UtcNow;

        // Navigation properties
        [ForeignKey("CustomerId")]
        public Customer Customer { get; set; }

        public ICollection<OrderItem> OrderItems { get; set; } = new List<OrderItem>();

        public void CalculateOrderItemsSubtotal()
        {
            if(OrderItems == null || !OrderItems.Any())
            {
                return 0;
            }

            return OrderItems.Sum(item => item.Subtotal);
        }

        public void UpdateOrderSubtotal()
        {
            this.Subtotal = CalculateOrderItemsSubtotal();
            this.UpdatedAt = DateTime.UtcNow;
        }

        public void CalculateTax()
        {
            if (this.Subtotal <= 0)
            {
                return 0;
            }
            decimal taxRate = 0.1m; // TODO: implement a dynamic tax rate based on location or other factors
            return this.Subtotal * taxRate;
        }

        public void UpdateOrderTax()
        {
            this.TaxAmount = CalculateTax(this.Subtotal);
            this.UpdatedAt = DateTime.UtcNow;
        }

        public void UpdateOrderDiscount()
        {
            this.DiscountAmount = OrderItems.Sum(item => item.DiscountAmount);
            this.UpdatedAt = DateTime.UtcNow;
        }

        public void UpdateOrderTotalAmount()
        {
            this.TotalAmount = this.Subtotal + this.TaxAmount + this.ShippingAmount - this.DiscountAmount;
            this.UpdatedAt = DateTime.UtcNow;
        }

        public void UpdateOrderTotals()
        {
            UpdateOrderSubtotal();
            UpdateOrderTax();
            UpdateOrderDiscount();
            UpdateOrderTotalAmount();
        }

        public void AddOrderItem(Book book, int quantity)
        {
            var orderItem = new OrderItem
            {
                BookId = book.Id,
                Quantity = quantity,
                UnitPrice = book.Price,
                DiscountAmount = 0
            };
            orderItem.UpdateOrderItemSubtotal();

            var existingItem = OrderItems.FirstOrDefault(item => item.BookId == book.Id);
            if(existingItem != null)
            {
                existingItem.Quantity += quantity;
                existingItem.UpdateOrderItemSubtotal();
            }
            else
            {
                this.OrderItems.Add(orderItem);
            }

            UpdateOrderTotals();
        }
    }
} 