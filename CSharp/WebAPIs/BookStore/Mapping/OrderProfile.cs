using AutoMapper;
using BookStore.Models;
using BookStore.Dtos.Order;


namespace BookStore.Mapping
{
    public  OrderProfile : Profile
    {
        public OrderProfile()
    {
        CreateMap<Order, OrderDto>()
            .ForMember(dest => dest.TotalPrice, opt => opt.MapFrom(src => src.CalculateTotalPrice()));
        CreateMap<OrderItem, OrderItemDto>()
            .ForMember(dest => dest.BookTitle, opt => opt.MapFrom(src => src.Book.Title))
            .ForMember(dest => dest.BookAuthor, opt => opt.MapFrom(src => src.Book.Authors.FirstOrDefault().Name));
        CreateMap<CreateOrderDto, Order>();
        CreateMap<UpdateOrderDto, Order>()
            .ForAllMembers(opts => opts.Condition((src, dest, srcMember) =>
                srcMember != null));
    }
}   
}