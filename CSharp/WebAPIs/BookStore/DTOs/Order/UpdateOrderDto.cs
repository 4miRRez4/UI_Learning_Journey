using System.ComponentModel.DataAnnotations;
using BookStore.Models.Enums;

namespace BookStore.Dtos.Order
{
    public class UpdateOrderDto
    {
        public OrderStatus? Status { get; set; }
        public PaymentStatus? PaymentStatus { get; set; }
        public string? PaymentMethod { get; set; }
        public string? TransactionId { get; set; }
        public string? ShippingAddress { get; set; }
        public string? ShippingMethod { get; set; }
        public string? Notes { get; set; }
    }
} 