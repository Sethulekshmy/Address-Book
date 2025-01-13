#include <stdio.h>
#include "file.h"

void loadContactsFromFile(AddressBook *addressBook)
{
	int count;
	
	FILE *fptr = fopen("data.txt","r");
	if(fptr==NULL)
	{
		printf("File not exist");
	
		
	}
	 fscanf(fptr,"%d\n",&addressBook->contactCount);

	 // adressBook->contactCount=count;
	 
	 for(int i=0;i<addressBook->contactCount;i++)
	 {
	  fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
if(addressBook->contactCount==0)
    {
	printf("There is no file details");
    }
																  
	fclose(fptr);
}

/*
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
*/
void saveContactsToFile(AddressBook *addressBook)
{
	FILE *fptr = fopen("data.txt","w");
	if(fptr==NULL)
	{
		printf("File not exist");
	}
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fptr,"%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fptr);
}
