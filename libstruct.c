/* Meagan Hendrickson 
UCF ID: 5562145
COP 3223C
Professor Parra 
11/11/2024
Assignment 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstruct.h"

//function searches for book by title and returns pointer to matching Book struct 
Book* findBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear){
    //loop through books in library
    for(int i=0; i<(*library).count; i++){
        //if book is not NULL and details match inputted details
        if((*library).books[i] != NULL && strcmp((*(*library).books[i]).title, bookTitle) == 0 && strcmp((*(*library).books[i]).author, bookAuthor) == 0 && (*(*library).books[i]).year == bookYear){
            //confirm book has been found 
            printf("Book with title '%s', author '%s', and year %d is found!\n", bookTitle, bookAuthor, bookYear);
            //return a pointer to the book in the library
            return(*library).books[i];
        }
    }
    //if book is not found in library
    return NULL;
}

//function to get info from file and add it to library
void addBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear){
    //check if library is full 
    if((*library).count == MAX_BOOKS){
        printf("The library is full. Cannot add more books.\n");
        return;
    }
    //if book is already in library 
    if(findBook(library, bookTitle, bookAuthor, bookYear) != NULL){
        printf("Book with title '%s', author '%s', and year %d is already in the library.\n", bookTitle, bookAuthor, bookYear);
        return;
    }
    //allocate memory for new book
    Book *addedBook = (Book *)malloc(sizeof(Book));
    if(addedBook == NULL){
        printf("Memory allocation failed.\n");
        return;
    }
    //allocate memory for book details 
    (*addedBook).title = (char *)malloc(strlen(bookTitle)+1);
    (*addedBook).author = (char *)malloc(strlen(bookAuthor)+1);
    if((*addedBook).title == NULL || (*addedBook).author == NULL){
        printf("Memory allocation failed.\n");
        free((*addedBook).title);
        free((*addedBook).author);
        free(addedBook);
        return;
    }
    //if book is not already in the library

    strcpy((*addedBook).title, bookTitle);
    strcpy((*addedBook).author, bookAuthor);
    (*addedBook).year = bookYear;
    (*addedBook).isAvailable = 1;
    (*library).books[(*library).count] = addedBook;
    (*library).count ++;
    //confirm that book as been added
    printf("Book with title '%s', author '%s', and year %d added to the library.\n", bookTitle, bookAuthor, bookYear);
}

//function to search for book by title and remove it from the library, no shifting
void removeBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear){
    //loop through books in library 
    for(int i=0; i<(*library).count; i++){
        if((*library).books[i] != NULL && strcmp((*(*library).books[i]).title, bookTitle) == 0 && strcmp((*(*library).books[i]).author, bookAuthor) == 0 && (*(*library).books[i]).year == bookYear){
            //free memory
            free((*(*library).books[i]).title);
            free(((*library).books[i])->author);
            free((*library).books[i]);
            //mark spot of removed book as NULL 
            (*library).books[i] = NULL;
            //decrease count
            (*library).count --;
            printf("Book with title '%s', author '%s', and year %d has been removed from the library.\n", bookTitle, bookAuthor, bookYear);
            return;
        }
    }
    //if book is not found in the library 
    printf("Book not found\n");
}

//function prints details of all books in library 
void printLibrary(Library *library){
    //loop through all books in library 
    for(int i=0; i<MAX_BOOKS; i++){
        //when book in library is  not NULL 
        if((*library).books[i] != NULL){
            //if book is avaliable to be checked out 
            if((*library).books[i]->isAvailable == 1){
                printf("Book with title '%s', author '%s', and year %d is in the library and isn't checked out.\n", (*(*library).books[i]).title, (*(*library).books[i]).author, (*(*library).books[i]).year);
            }
            //if book is not avaliable to be checked out 
            if((*library).books[i]->isAvailable == 0){
                printf("Book with the title '%s', author '%s', and year %d is in the library and is checked out.\n", (*(*library).books[i]).title, (*(*library).books[i]).author, (*(*library).books[i]).year);
            }
        }
    } 
}

//function to change isAvaliable feild to show unavaliable
void checkoutBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear){
    //use find book function to find inputted book in library 
    Book *book = findBook(library, bookTitle, bookAuthor, bookYear);
    //if book is found in library 
    if(book != NULL){
        //if book is avaliable to be checked out 
        if((*book).isAvailable == 1){
            //change avaliability 
            (*book).isAvailable = 0;
            printf("Book with title '%s', author '%s', and year %d is checked out.\n", bookTitle, bookAuthor, bookYear);
        }
        //if book is already checked out 
        else if((*book).isAvailable == 0){
            printf("Book with title '%s', author '%s', and year %d is already checked out.\n", bookTitle, bookAuthor, bookYear);
        }
    }
    //when book is not found in library
    else{
        printf("Book not found\n");
    }
}

//function to change isAvaliable feild to show avaliable 
void returnBook(Library *library, const char *bookTitle, const char *bookAuthor, int bookYear){
    //use find book function to find inputted book in library 
    Book *book = findBook(library, bookTitle, bookAuthor, bookYear);
    //if book is found in library
    if(book != NULL){
        //if book is checked out 
        if((*book).isAvailable == 0){
            //change avaliablity
            (*book).isAvailable = 1;
            printf("Book with title '%s', auhtor '%s', and year %d is returned.\n", bookTitle, bookAuthor, bookYear);
        }
        //if book is already returned 
        else if((*book).isAvailable == 1){
            printf("Book with title '%s', author '%s', and year %d is not checked out.\n", bookTitle, bookAuthor, bookYear);
    }
    //when book is not found in library
    else{
        printf("Book not found\n");
    }
}
}

//create a function that reads the inputted file 
void readFile(Library *library, char *fileName){
    //open and read file 
    FILE *file = fopen(fileName, "r");
    //if trouble opening and reading file 
    if(file == NULL){
        printf("Error opening and reading the file.\n");
        return;
    }
    //define variables 
    char command[130];
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
    
    //read file line by line
    while(fscanf(file, "%s", command) != EOF){
        //check if command is add 
        if(strcmp(command, "add") == 0){
            //read next line for book details 
            fscanf(file, " %[^\n]", title);
            fscanf(file, " %[^\n]", author);
            fscanf(file, " %d", &year);
            //call add book function 
            addBook(library, title, author, year);
        }
        //check if command is remove
        else if(strcmp(command, "remove") == 0){
            //read next line for book details 
            fscanf(file, " %[^\n]", title);
            fscanf(file, " %[^\n]", author);
            fscanf(file, " %d", &year);
            //call function to remove book from library
            removeBook(library, title, author, year);
        }
        //check if command is checkout 
        else if(strcmp(command, "checkout") == 0){
            //read next line for book details
            fscanf(file, " %[^\n]", title);
            fscanf(file, " %[^\n]", author);
            fscanf(file, " %d", &year);
            //call function to checkout book from library 
            checkoutBook(library, title, author, year);
        }
        //check if command is return 
        else if(strcmp(command, "return") == 0){
            //read next line for book details 
            fscanf(file, " %[^\n]", title);
            fscanf(file, " %[^\n]", author);
            fscanf(file, " %d", &year);
            //call function to return book to library 
            returnBook(library, title, author, year);
        }
        //check if command is print
        else if(strcmp(command, "print") == 0){
            //call function to print library 
            printLibrary(library);
        }
    }
    //close file after reading 
    fclose(file);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Invalid argument.\n");
        return 1;
    }
    //initialize library
    Library library ={.count = 0};
    //call function that reads file
    readFile(&library, argv[1]);

    return 0;
}
