using AutoMapper;
using BookStore.Models;
using BookStore.Dtos.Order;


namespace BookStore.Mapping
{
    public class OrderProfile : Profile
    {
        public OrderProfile()
        {
            CreateMap<Order, OrderDto>()
                .ForMember(dest => dest.TotalAmount, opt => opt.MapFrom(src => src.TotalAmount))
                .ForMember(dest => dest.CustomerName, opt => opt.MapFrom(src => src.Customer.FirstName))
                .ForMember(dest => dest.CustomerEmail, opt => opt.MapFrom(src => src.Customer.Email));

            CreateMap<OrderItem, OrderItemDto>()
                .ForMember(dest => dest.BookTitle, opt => opt.MapFrom(src => src.Book.Title));

            CreateMap<CreateOrderDto, Order>();
            CreateMap<UpdateOrderDto, Order>()
                .ForAllMembers(opts => opts.Condition((src, dest, srcMember) =>
                    srcMember != null));
        }
    }
}