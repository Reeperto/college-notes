#include "linkedlist.h"
#include "hw2.h"

int intComparator(void *p, void *q)
{   
    long x =  ((long)p - (long)q);  // void* used to pass/store int values themselves! An address is just a num!

    if(x)
	    return x < 0 ? -1 : 1;
    return 0;
}

void intPrinter(void *data, void* fp, int unused)
{
        fprintf((FILE*) fp, "%ld", (long) data);
}

void intDeleter(void *data)
{
    return;   //Nothing to delete! data field is not a pointer to dynamically allocated data
}

int main(int argc, char* argv[]) {
    long start = 1;
    long end = 20;
    int i;

    // Create and initialize integer linked list
    list_t* list = CreateList(&intComparator, &intPrinter, &intDeleter);

    // Output: List is empty
    printf("**********Empty List**********\n");    
    PrintLinkedList(list, stdout, " ");
    printf("\n");


    // Output: 1
    printf("**********1 List Value**********\n");   
    // Insert first node. Why does start need to be casted?
    InsertAtHead(list, (void*)start);
    PrintLinkedList(list, stderr, "!");  //Print to STDERR
    printf("\n");


    printf("**********Full List except 10**********\n");   
    // Inserting the remaining values, skip value 10
    for (i = start + 1; i <= end; i++) {
        if(i != 10)
            InsertAtTail(list, (void*)(long)i);
    }
    // Output (each value on a line): 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 18 19 20
    PrintLinkedList(list, stdout, ", "); 
    printf("\n");

    printf("**********Full List**********\n");   
    InsertInOrder(list, (void*)10);
    // Output (each value on a line): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    PrintLinkedList(list, stdout, " ");  
    printf("\n");


    printf("**********Duplicate Odd Numbers In List**********\n");   
    // Inserting every other value again, inOrder based on comparator
    for (i = start; i <= end; i=i+2) {
        InsertInOrder(list, (void*) (long)i);
    }
    // Output (each value on a line): 1 1 2 3 3 4 5 5 6 7 7 8 9 9 10 11 11 12 13 13 14 15 15 16 17 17 18 19 19 20
    PrintLinkedList(list, stderr, ", ");  //Print test to STDERR
    printf("\n");

    // Delete the list  - Need to implement this function for HW 
    // DestroyList(&list);

    return 0;
}
