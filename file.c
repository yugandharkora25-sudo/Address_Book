#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    
    addressBook->contactCount;
    FILE *fptr=fopen("contact.txt","w");

    fprintf(fptr,"%d\n",addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fptr);
    return;
  
}

void loadContactsFromFile(AddressBook *addressBook) {

    addressBook->contactCount;
    FILE *fptr=fopen("contact.txt","r");

    if(NULL==fptr)
    {
        perror(" ");
        return;
    }

    fscanf(fptr,"%d\n",&addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fptr);
    return;
  
}
