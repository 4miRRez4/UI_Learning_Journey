using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace BookStore.Models
{
    public class OrderItem
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public int OrderId { get; set; }

        [Required]
        public int BookId { get; set; }

        [Required]
        public int Quantity { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal UnitPrice { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal Subtotal { get; set; }

        [Required]
        [Column(TypeName = "decimal(18,2)")]
        public decimal DiscountAmount { get; set; }

        // Navigation properties
        [ForeignKey("OrderId")]
        public Order Order { get; set; }

        [ForeignKey("BookId")]
        public Book Book { get; set; }

        public decimal UpdateOrderItemSubtotal()
        {
            this.Subtotal = (this.Quantity * this.UnitPrice) - this.DiscountAmount;

            if(Subtotal < 0) Subtotal = 0;

            return this.Subtotal;
        }
    }
} 