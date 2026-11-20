#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

int check_duplicate1(AddressBook *addressBook, char *mail)
{
    int i;
    int n = addressBook->contactCount;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].email, mail) == 0)
        {
            printf(RED "\n⚠️  Mail id already exist enter different id\n\n" RESET);
            return 1;
        }
    }
    return 0;
}

int valid_mail(char *mail)
{
    char *ptr = mail;
    int len = strlen(mail);

    if (strstr(mail, ".@") || strstr(mail, "@."))
    {
        printf(RED "\n⚠️  Mail id sholud not contain '.' and '@' consicutive manner\n\n" RESET);
        return 1;
    }

    int i, dot_count = 0, at_count = 0, index;
    if (!isalpha(ptr[0]))
    {
        printf(RED "\n⚠️  Mail id sholud not start with numbers or any special characters\n\n" RESET);
        return 1;
    }

    for (i = 0; i < len; i++)
    {
        if (mail[i] == '@')
        {
            at_count++;
            index = i;
        }

        else if (mail[i] == '.')
            dot_count++;

        else if (!(isalnum(mail[i]) || mail[i] == '.' || mail[i] == '-' || mail[i] == '_'))
        {
            printf(RED "\n⚠️  Mail id contain invalid inputs \n\n" RESET);
            return 1;
        }
    }

    if (at_count == 0)
    {
        printf(RED "\n⚠️  Mail id should contain one @ \n\n" RESET);
        return 1;
    }

    if (at_count != 1)
    {
        printf(RED "\n⚠️  Mail id should not contain extra @ \n\n" RESET);
        return 1;
    }

    for (i = 0; i < len - 1; i++)
    {
        if (mail[i] == '.' && mail[i + 1] == '.')
        {
            printf(RED "\n⚠️  Mail id should not have consicutive dots(.)\n\n" RESET);
            return 1;
        }
    }

    if (strcmp(mail + len - 4, ".com") != 0)
    {
        printf(RED "\n⚠️  Mail id must end with '.com'\n\n" RESET);
        return 1;
    }

    if (!(strstr(mail, "gmail") == 0 || strstr(mail, "@yahoo") == 0 || strstr(mail, "@outlook") == 0 || strstr(mail, "@hotmail") == 0 || strstr(mail, "@icloud") == 0))
    {
        printf(RED "\n⚠️  Invalid email address! Please try again.\n\n" RESET);
        return 1;
    }

    return 0;
}

int check_duplicate(AddressBook *addressBook, char *number)
{
    int i;
    int n = addressBook->contactCount;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].phone, number) == 0)
        {
            printf(RED "\n⚠️  Phone number already exist enter different phone number\n\n" RESET);
            return 1;
        }
    }
    return 0;
}

int valid_number(char *number)
{
    int i = 0;

    while (number[i])
    {
        if (!isdigit(number[i]))
        {
            printf(RED "\n⚠️  ERROR : Number should be digits only\n\n" RESET);
            return 1;
        }
        i++;
    }

    if (strlen(number) != 10)
    {
        printf(RED "\n⚠️  Number should have 10 digits\n\n" RESET);
        return 1;
    }

    return 0;
}

int valid_name(char *name)
{
    int i;
    for (i = 0; name[i]; i++)
    {
        if (!(isalpha(name[i]) || isspace(name[i])))
        {
            printf(RED "\n⚠️  Name should contain only alphabates\n\n" RESET);
            return 1;
        }
    }

    return 0;
}

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the chosen criteria
    int n = addressBook->contactCount;
    if (addressBook->contactCount == 0)
    {
        printf("Addressbook is empty\n");
        return;
    }

    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            int cmp = 0;
            if (sortCriteria == 1)
                cmp = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);

            else if (sortCriteria == 2)
                cmp = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);

            else if (sortCriteria == 3)
                cmp = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);

            if (cmp > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];

                addressBook->contacts[j] = temp;
            }
        }
    }

    
    
    printf("| No. | Name            | Phone Number     | Email ID                      |\n");
    

    for (i = 0; i < n; i++)
    {
        printf("| %-3d | %-15s | %-16s | %-29s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED "❌ Address book full! Cannot add more contacts.\n" RESET);
        return;
    }

    char name[30];
    char number[11];
    char mail[30];
    int valid, valid1;

    // Validtion of name

    do
    {
        printf("Enter name: ");
        scanf(" %[^\n]", name);

        valid = valid_name(name);

    } while (valid);

    // Validation of Number

    do
    {
        printf("Enter mobile number: ");
        scanf(" %[^\n]", number);

        valid = valid_number(number);
        valid1 = check_duplicate(addressBook, number);

        if (valid == 0 && valid1 == 0)
            break;

    } while (1);

    do
    {
        printf("Enter email id: ");
        scanf(" %[^\n]", mail);

        valid = valid_mail(mail);

        valid1 = check_duplicate1(addressBook, mail);

        if (valid == 0 && valid1 == 0)
            break;

    } while (1);

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, number);

    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    addressBook->contactCount++;

    printf(GREEN "\n✅ Contact saved successfully🎉\n" RESET);
}

void searchContact(AddressBook *addressBook)
/* Define the logic for search */
{
    int i, search, found, count = 0, valid;
    char compare[30];
    int size = addressBook->contactCount;

    if (size == 0)
    {
        printf(RED "❌ No contacts availble to search\n" RESET);
        return;
    }

    while (1)
    {
        printf("Enter search criteria: ");
        printf("\n1. Search by name\n2. Search by phone number\n3. Search by email id\n4. Exit\n");

        do
        {
            printf("Enter your choice: ");

            valid = scanf("%d", &search);

            if (valid != 1)
            {
                printf(RED "\n⚠️  Invalid input! Please enter a number.\n\n" RESET);

                while (getchar() != '\n')
                    ;
            }

        } while (valid != 1);

        if (search == 1)
            printf("\nEnter name to search: ");

        else if (search == 2)
            printf("\nEnter phone number to search: ");

        else if (search == 3)
            printf("\nEnter mail id to search: ");

        else if (search == 4)
            break;

        if (search <= 0 || search > 4)
        {
            printf(RED "\n⚠️  Invalid input\n\n" RESET);
            continue;
        }

        scanf(" %[^\n]", compare);

        int match = 0;
        for (i = 0; i < size; i++)
        {
            found = 0;

            if (search == 1 && strcasestr(addressBook->contacts[i].name, compare))
                found = 1;

            else if (search == 2 && strcmp(addressBook->contacts[i].phone, compare) == 0)
                found = 1;

            else if (search == 3 && strcasestr(addressBook->contacts[i].email, compare))
                found = 1;

            if (found)
            {
                if (match == 0)
                {

                    
                    
                    printf("| No | %-15s | %-14s | %-24s |\n", "Name", "Phone Number", "Email ID");
                    
                }
                count++;
                printf("| %-2d | %-15s | %-14s | %-24s |\n", count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                
                match = 1;
            }
        }
        if (match == 0)
        {
            printf("\033[1;31m"); // Red bold text
            
            printf("       ❌  NO CONTACT FOUND       \n");
            
            printf("\033[0m"); // Reset color
            return;
        }

        printf( "\n✅ Search completed successfully!\n");
        return;
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    if (addressBook->contactCount == 0)
    {
        printf(RED "\n❌ No contacts available to edit.\n" RESET);
        return;
    }

    int size = addressBook->contactCount;
    int i, search, Found_contact[MAX_CONTACTS], found_count = 0, match = 0, found, valid, valid1;
    char edit[30];

    while (1)
    {
        do
        {
            printf("Enter search criteria: ");
            printf("\n1. Search by name\n2. Search by phone number\n3. Search by email id\n4. Exit\n");

            printf("Enter your choice: ");

            valid1 = scanf("%d", &search);

            if (valid1 != 1)
            {
                printf( "\n⚠️  Invalid input! Please enter a number.\n");

                while (getchar() != '\n')
                    ;
            }

        } while (valid1 != 1);

        if (search == 1)
            printf("\nEnter name to search: ");

        else if (search == 2)
            printf("\nEnter phone number to search: ");

        else if (search == 3)
            printf("\nEnter mail id to search: ");

        else if (search == 4)
            break;

        if (search <= 0 || search > 4)
        {
            printf(RED "\n⚠️  Invalid input\n\n" RESET);
            continue;
        }

        scanf(" %[^\n]", edit);
        for (i = 0; i < size; i++)
        {
            found = 0;

            if (search == 1 && strcasestr(addressBook->contacts[i].name, edit))
                found = 1;

            else if (search == 2 && strcmp(addressBook->contacts[i].phone, edit) == 0)
                found = 1;

            else if (search == 3 && strcasestr(addressBook->contacts[i].email, edit))
                found = 1;

            if (found)
            {
                if (match == 0)
                {
                    
                    
                    printf("| Sl.No  | Name            | Phone Number     | Email ID                      |\n");
                    
                }

                Found_contact[found_count++] = i;

                printf("| %-6d | %-15s | %-16s | %-29s |\n",
                       found_count,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                

                match = 1;
            }
        }

        if (match == 0)
        {
            printf("\033[1;31m"); // Red bold text
            
            printf("      ❌  NO CONTACT FOUND       \n");
            
            printf("\033[0m"); // Reset color
            return;
        }

        int choice;
        printf("Enter serial number to edit: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > found_count)
        {
            printf(RED "\n⚠️  Invalid input editing failed!  \n\n" RESET);
            return;
        }

        int index = Found_contact[choice - 1];

        while (1)
        {
            printf("\nEnter edit criteria: \n");
            printf("1. Edit name\n2. Edit phone number\n3. Edit mail id\n4. Exit\nEnter your choice: ");
            scanf("%d", &search);

            if (search == 1)
            {
                do
                {
                    printf("\nEnter new name: ");
                    scanf(" %[^\n]", edit);
                    valid = valid_name(edit);
                } while (valid);

                strcpy(addressBook->contacts[index].name, edit);
                printf( "\n✅ Name edited succussfully 🎉\n");
                return;
            }

            else if (search == 2)
            {
                do
                {
                    printf("\nEnter new phone number: ");
                    scanf(" %[^\n]", edit);
                    valid = valid_number(edit);
                } while (valid);

                strcpy(addressBook->contacts[index].phone, edit);
                printf( "\n✅ Phone number edited succussfully 🎉\n");
                return;
            }

            else if (search == 3)
            {
                do
                {
                    printf("\nEnter new mail id: ");
                    scanf(" %[^\n]", edit);
                    valid = valid_mail(edit);
                } while (valid);

                strcpy(addressBook->contacts[index].email, edit);
                printf( "\n✅ Mail id edited succussfully 🎉\n");
                return;
            }

            else if (search == 4)
            {
                printf("\nYou are exit Without editing\n\n");
                return;
            }

            else
            {
                printf(RED "\n⚠️  Invalid input\n\n" RESET);
                return;
            }
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    addressBook->contactCount;

    int i, num, match, found, j, Found_contact[MAX_CONTACTS], count = 0, valid;

    char delete[30], confirm;

    while (1)
    {
        do
        {
            printf("Enter delete criteria: \n");

            printf("1. By Name\n2. By phone number\n3. By email id\n4. Exit\nEnter your choice:");

            valid = scanf("%d", &num);

            if (valid != 1)
            {
                printf( "\n⚠️  Invalid input! Please enter a number.\n");

                while (getchar() != '\n')
                    ;
            }

        } while (valid != 1);

        if (num == 1)
            printf("Enter name: ");

        else if (num == 2)
            printf("Enter phone number: ");

        else if (num == 3)
            printf("Enter email id: ");

        else if (num == 4)
            return;

        else
        {
            printf(RED "\n⚠️  Invalid input\n\n" RESET);
            continue;
        }

        scanf(" %[^\n]", delete);

        match = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {

            found = 0;

            if (num == 1 && strcasestr(addressBook->contacts[i].name, delete))
                found = 1;

            else if (num == 2 && strcmp(addressBook->contacts[i].phone, delete) == 0)
                found = 1;

            else if (num == 3 && strcasestr(addressBook->contacts[i].email, delete))
                found = 1;

            if (found)
            {
                if (match == 0)
                {
                   
                    
                    printf(" Sl.No   Name             Phone Number      Email ID                      \n");
                    
                }

                {
                    Found_contact[count++] = i;
                    printf("| %-6d | %-15s | %-16s | %-29s |\n", count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    
                    match = 1;
                }
            }
        }

        if (match == 0)
        {
            printf("\033[1;31m"); // Red bold text
            
            printf("       ❌  NO CONTACT FOUND       \n");
            
            printf("\033[0m"); // Reset color
            return;
        }

        int choice;
        printf("Choose serial number to delete the contact: ");
        scanf("%d", &choice);

        int index = Found_contact[choice - 1];

        if (choice < 1 || choice > count)
        {
            printf(RED "\n⚠️  Invalid input\n\n" RESET);
            return;
        }

        printf("Are you sure you want to delete this contact Yes(y) or No(n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y')
        {
            for (j = index; j < count - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf( "\n✅ Contact succufully deleted 🎉\n");
            return;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            printf(RED "\n❌ Deletion cancelled. The contact was not deleted\n\n" RESET);
            return;
        }
        else
            printf(RED "⚠️  Invalid input\n\n" RESET);
    }
}