using AutoMapper;
using BookStore.Models;
using BookStore.Dtos.Book;
using BookStore.Dtos.Author;

namespace BookStore.Mapping
{
    public class BookProfile : Profile
    {
        public BookProfile()
        {       
            CreateMap<Book, BookDto>();
            CreateMap<Author, AuthorDto>();

            CreateMap<CreateBookDto, Book>();
        }
    }
}