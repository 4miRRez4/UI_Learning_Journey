using AutoMapper;
using BookStore.Models;
using BookStore.Dtos.Book;
using BookStore.Dtos.Author;
using BookStore.Application.Books.Commands;

namespace BookStore.Mapping
{
    public class BookProfile : Profile
    {
        public BookProfile()
        {       
            CreateMap<Book, BookDto>();
            CreateMap<Author, AuthorDto>();

            CreateMap<CreateBookDto, Book>();

            CreateMap<UpdateBookDto, Book>()
                .ForAllMembers(opts => opts.Condition((src, dest, srcMember) =>
                    srcMember != null));

            CreateMap<Book, UpdateBookDto>();

            CreateMap<AddBookCommand, CreateBookDto>();
            CreateMap<UpdateBookCommand,  UpdateBookDto>();

            CreateMap<BookDto, Book>().ReverseMap();
            CreateMap<AuthorDto, Author>().ReverseMap();
        }
    }
}