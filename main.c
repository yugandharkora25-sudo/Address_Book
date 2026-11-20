#include <stdio.h>
#include "contact.h"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); 

    do
    {
        printf("\n");
        
        printf("    ADDRESS BOOK MENU     \n\n");
        
        printf(" 1. Create Contact               \n");
        printf(" 2. Search Contact               \n");
        printf(" 3. Edit Contact                 \n");
        printf(" 4. Delete Contact               \n");
        printf(" 5. List All Contacts            \n");
        printf(" 6. Save and Exit                \n");
       

        int valid;

        do
        {
            printf("Enter your choice: ");

            valid = scanf("%d", &choice);

            if (valid != 1)
            {
                printf(RED "\n⚠️  Invalid input! Please enter a number.\n\n" RESET);

                while (getchar() != '\n');
            }

        } while (valid != 1);

        printf("You entered: %d\n", choice);

        printf("\n");

        switch (choice)
        {
        case 1:

            printf("---- [ CREATE CONTACT ] ----\n\n");
            createContact(&addressBook);
            break;

        case 2:

            printf("---- [ SEARCH CONTACT ] ----\n\n");
            searchContact(&addressBook);
            break;

        case 3:

            printf("---- [ EDIT CONTACT ] ----\n\n");
            editContact(&addressBook);
            break;

        case 4:

            printf("---- [ DELETE CONTACT ] ----\n\n");
            deleteContact(&addressBook);
            break;

        case 5:

            int sortChoice, valid1;

            do
            {
                printf("---- [ LIST CONTACTS ] ----\n\n");
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");

                valid1 = scanf("%d", &sortChoice);
                if(sortChoice < 0 || sortChoice > 3)
                {
                    printf(RED"\n⚠️  Invalid input! Please enter a number.\n\n" RESET);
                    continue;
                }
                if (valid1 == 0)
                {
                    printf(RED "\n⚠️  Invalid input! Please enter a number.\n\n" RESET);

                    while (getchar() != '\n');

                }
            } while (valid1 != 1 || sortChoice < 0 || sortChoice > 3);

            printf("\n");
            listContacts(&addressBook, sortChoice);
            break;

        case 6:

            printf(GREEN "Saving and Exiting...\n\n" RESET);
            saveContactsToFile(&addressBook);
            break;

        default:
            printf(RED "⚠️  Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 6);

    return 0;
}