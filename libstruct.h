#ifndef LIBSTRUCT_H
#define LIBSTRUCT_H

#define MAX_BOOKS 100
#define MAX_TITLE 1024
#define MAX_AUTHOR 1024

//structure definitions
typedef struct Book{
    //dynamic array of characters for title of book
    char *title;
    //dynamic array of characters for author of book
    char *author;
    //integer representing year book was published 
    int year;
    //integer representing whether the book is avaliable(1) or checked out (0)
    int isAvailable;
}Book;

typedef struct Library{
    //dynamic array of book pointers 
    Book *books[MAX_BOOKS];
    //integer to current number of books in library 
    int count;
}Library;

//function prototypes
Book* findBook(Library *library, const char *bookTitle, const char *bookAuthour, int bookYear);
void addBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear);
void removeBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear);
void printLibrary(Library *library);
void checkoutBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear);
void returnBook(Library *library, const char *booktitle, const char *bookAuthor, int bookYear);
void readFile(Library *library, char *fileName);

#endif 