#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int book_id;
    char book_name[20];
    char author_name[20];
    int page_of_book;
    bool isRead;
} Book;

typedef struct {
    int reader_id;
    char reader_name[20];
    int book_id;
} Reader;
void CreateNewBook(int book_id, char *book_name, char *author_name, int page_of_book, Book **books, int *counter_of_book);
int findIndexOfBook(int id, Book **books, int *counter_of_book);
void DisplayAllBook(Book *books, int counter_of_book);
void CreateNewReader(int reader_id,char *reader_name,Reader **readers,int* counter_of_reader);
int findIndexOfReader(int id,Reader **readers,int *counter_of_reader);
void DisplayAllReader(Reader *readers, int counter_of_reader);
void ReadBook(int book_id,int reader_id,Book **books,Reader **readers,int *counter_of_book,int *counter_of_reader);
void ReleaseReadBook(int book_id,int reader_id,Book **books,Reader **readers,int *counter_of_book,int *counter_of_reader);

int main() {
    int selection, book_id, reader_id, page_of_book, counter_of_book = 0,counter_of_reader=0;
    char book_name[20], author_name[20],reader_name[20];

    Book *books = (Book *)malloc(sizeof(Book) * 4); // Allocate initial memory for 4 books
    Reader *readers = (Reader *)malloc(sizeof(Reader) * 4); // Allocate memory for 4 readers (
    do {
        printf("***************************************\n");
        printf("Create new Book (1)\n");
        printf("Create new Reader (2)\n");
        printf("Read Book (3)\n");
        printf("Release reading book (4)\n");
        printf("Display all book (5)\n");
        printf("Display all reader (6)\n");
        printf("Exit (7)\n");
        printf("Enter your selection:");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                printf("Enter book id:\n");
                scanf("%d", &book_id);
                printf("Enter book name:\n");
                scanf("%s", &book_name);
                printf("Enter author name:\n");
                scanf("%s", &author_name);
                printf("Enter book page:\n");
                scanf("%d", &page_of_book);
                CreateNewBook(book_id, book_name, author_name, page_of_book, &books, &counter_of_book);
                break;
            case 2:
                printf("Enter reader id:\n");
                scanf("%d", &reader_id);
                printf("Enter reader name:\n");
                scanf("%s", &reader_name);
                CreateNewReader(reader_id,reader_name,&readers,&counter_of_reader);
                break;
            case 3:
                printf("Enter book id:\n");
                scanf("%d", &book_id);
                printf("Enter reader  id:\n");
                scanf("%d", &reader_id);
                ReadBook(book_id,reader_id,&books,&readers,&counter_of_book,&counter_of_reader);
              
                break;
            case 4:
                printf("Enter book id:\n");
                scanf("%d", &book_id);
                printf("Enter reader  id:\n");
                scanf("%d", &reader_id);
                ReleaseReadBook(book_id,reader_id,&books,&readers,&counter_of_book,&counter_of_reader);
                break;
            case 5:
                DisplayAllBook(books, counter_of_book);
                break;
            case 6:
               DisplayAllReader(readers, counter_of_reader);
                break;
        }
    } while (selection != 7);

    // Free the allocated memory
    free(books);
    free(readers);

    return 0;
}
void ReleaseReadBook(int book_id,int reader_id,Book **books,Reader **readers,int *counter_of_book,int *counter_of_reader){
      int indexOfBook=findIndexOfBook(book_id,books,counter_of_book);
       int indexOfReader=findIndexOfReader(reader_id,readers,counter_of_reader);
       if(indexOfBook==-1){
        printf("this book not exist\n");
         return;
       }
       if(indexOfReader==-1){
          printf("this reader not exist\n");
          return;
       }
       books[indexOfBook]->isRead=false;
       readers[indexOfReader]->book_id=0;

 }
//************************************************************************************************
//read operatıon
void ReadBook(int book_id,int reader_id,Book **books,Reader **readers,int *counter_of_book,int *counter_of_reader){
       int indexOfBook=findIndexOfBook(book_id,books,counter_of_book);
       int indexOfReader=findIndexOfReader(reader_id,readers,counter_of_reader);
       if(indexOfBook==-1){
        printf("this book not exist\n");
         return;
       }
       if(indexOfReader==-1){
          printf("this reader not exist\n");
          return;
       }
       books[indexOfBook]->isRead=true;
       readers[indexOfReader]->book_id=book_id;
}
//************************************************************************************************
//reader operations
void CreateNewReader(int reader_id,char *reader_name,Reader **readers,int* counter_of_reader){
    if (findIndexOfReader(reader_id, readers, counter_of_reader) == -1) {
        Reader *new_reader = (Reader *)malloc(sizeof(Reader)); // Allocate memory for a new book
        new_reader->reader_id = reader_id;
        strcpy(new_reader->reader_name, reader_name);
        new_reader->book_id = 0;

        (*readers) = (Reader *)realloc(*readers, sizeof(Reader) * (*counter_of_reader + 1)); // Reallocate memory for the entire book array
        (*readers)[*counter_of_reader] = *new_reader; // Assign the new book to the end of the array
        (*counter_of_reader)++; // Increment counter only when a book is added

        free(new_reader); // Free the temporary new_book pointer memory
        printf("reader created..\n");
        printf("counter of reader:%d\n", *counter_of_reader);
    } else {
        printf("Reader with ID %d already exists.\n", reader_id);
    }



}
int findIndexOfReader(int id,Reader **readers,int *counter_of_reader){
    for(int i=0;i<(*counter_of_reader);i++){
        if(readers[i]->reader_id==id){
          return i;
        }
    }
  return -1;
}
void DisplayAllReader(Reader *readers, int counter_of_reader) {
    printf("counter :%d\n", counter_of_reader);
    for (int i = 0; i < counter_of_reader; i++) {
        printf("-------------------\n");
        printf("%d\n", readers[i].reader_id);
        printf("%s\n", readers[i].reader_name);
        if (readers[i].book_id > 0) {
            printf("This reader is  reading now\n");
        } else {
            printf("This reader is not  reading now\n");
        }
    }
}
//*************************************************************************************
//book operaions
void CreateNewBook(int book_id, char *book_name, char *author_name, int page_of_book, Book **books, int *counter_of_book) {
    if (findIndexOfBook(book_id, books, counter_of_book) == -1) {
        Book *new_book = (Book *)malloc(sizeof(Book)); // Allocate memory for a new book
        new_book->book_id = book_id;
        strcpy(new_book->book_name, book_name);
        strcpy(new_book->author_name, author_name);
        new_book->page_of_book = page_of_book;
        new_book->isRead = false;

        (*books) = (Book *)realloc(*books, sizeof(Book) * (*counter_of_book + 1)); // Reallocate memory for the entire book array
        (*books)[*counter_of_book] = *new_book; // Assign the new book to the end of the array
        (*counter_of_book)++; // Increment counter only when a book is added

        free(new_book); // Free the temporary new_book pointer memory
        printf("Book created..\n");
        printf("counter of book:%d\n", *counter_of_book);
    } else {
        printf("Book with ID %d already exists.\n", book_id);
    }
}

int findIndexOfBook(int id, Book **books, int *counter_of_book) {
    for (int i = 0; i < (*counter_of_book); i++) {
        if (books[i]->book_id == id) {
            return i;
        }
    }
    return -1;
}

void DisplayAllBook(Book *books, int counter_of_book) {
    printf("counter :%d\n", counter_of_book);
    for (int i = 0; i < counter_of_book; i++) {
        printf("-------------------\n");
        printf("%d\n", books[i].book_id);
        printf("%s\n", books[i].book_name);
        printf("%s\n", books[i].author_name);
        printf("%d\n", books[i].page_of_book);
        if (books[i].isRead == true) {
            printf("This book is being read\n");
        } else {
            printf("This book is not being read\n");
        }
    }
}

