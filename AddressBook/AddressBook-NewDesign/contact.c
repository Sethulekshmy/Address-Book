#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook) 
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("Name: %s\nMobile number :%s\nEmail :%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
 // populateAddressBook(addressBook);
    
  //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}





void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
   exit(EXIT_SUCCESS); // Exit the program
            

}



void createContact(AddressBook *addressBook)
{
      reenter_name: printf("Enter the name: ");
        getchar();
        scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].name);

                         
           int flag;
           int i=0;
           while (addressBook->contacts[addressBook->contactCount].name[i]) {
            int ret = isalpha(addressBook->contacts[addressBook->contactCount].name[i]);     //check whether the name contains only alphabets
            if (ret == 0 && addressBook->contacts[addressBook->contactCount].name[i]!=' ') {
                printf("Invalid name,Enter the correct name\n");       //if the name is invalid gotp renter name till the name becomes valid.
               
                
                goto reenter_name;     
            }
            i++;
            }                         

reenter_number:
        flag=0;
        i=0;
        printf("Enter the Mobile Number:");                  // if the name is valid the enter the number you want to create .
							                          
        getchar();
        scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].phone);
         if (strlen(addressBook->contacts[addressBook->contactCount].phone) != 10) //check the number contains only digits and 10  digits. if not renter the number.
        {
        printf("Invalid input!!Renter mobile number\n");
        goto reenter_number;
        }

    while (addressBook->contacts[addressBook->contactCount].phone[i])
    {
         if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
                 {
                 flag=1;
                 printf("Invalid input!!Renter mobile number\n");
                 goto reenter_number;
                 }
                 i++;
        }
         for(int i=0;i<addressBook->contactCount;i++)
            {
              if(strcmp((addressBook->contacts[addressBook->contactCount].phone),addressBook->contacts[i].phone)==0)
		                                                        //check whether no exists  already .if its unique goto eamil.
              {
                      printf("Already exist\n");
                      goto reenter_number;
              }

            }


       reenter_email: 
       flag=0;
       i=0;
       printf("Enter the E-mail: ");
        getchar();
        scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].email);

        for (i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[addressBook->contactCount].email, addressBook->contacts[i].email) == 0) {
		                                                        //check th email contain @.com and character present bw.
            printf("Email already exists! Please re-enter.\n");
            flag=1;
            goto reenter_email;
        }
    }
    if (strchr(addressBook->contacts[addressBook->contactCount].email, '@') == NULL || 
        strstr(addressBook->contacts[addressBook->contactCount].email, ".com") == NULL) { 
        printf(" Email must contain '@' and end with '.com'. Please re-enter.\n");
        goto reenter_email;
    }


        addressBook->contactCount++;
     printf("Contacts created successfully !!!");
 
}


void searchContact(AddressBook *addressBook) 
{
    int option;
    char name[50];
    char phone[20];
    char email[50];
    do{                                        // In search contact user can search the contacts available in the list.

    printf("\nChoose the option: \n");             //choose the option you want to search.
    printf("1.Name\n2.Mobile number \n3.Email \n4.EXIT\n");   
    scanf("%d",&option);
    int i;
   switch (option) {
            case 1:
               reenter: printf("Enter the name to be searched: ");
                getchar();
                scanf("%[^\n]", name);

                for (i=0;i<addressBook->contactCount;i++)    // Enter the name to be searched  compare the name with contacts list . 
                 {
                    if(strcmp(name,addressBook->contacts[i].name)==0) {    
                                                                              // if the name is present once .list the details of the contact.
                        for (int j=i+1;j<addressBook->contactCount;j++) 
                        {
                            if(strcmp(name, addressBook->contacts[j].name)==0) {   // if more than one name confirm it with phone.
                               
                                goto confirmPhone;                   
                            }
                        }
                        
                        goto searchContact;
                    }
                }
                printf("No contact found\n");     
                goto reenter;
                return;

confirmPhone:
                
                printf("Already exist!!\n Please enter the mobile number to confirm: ");
                getchar();  
                scanf("%[^\n]", phone);

                
                for (i=0;i<addressBook->contactCount;i++) 
                {
                    if (strcmp(name, addressBook->contacts[i].name) == 0 &&
                        strcmp(phone, addressBook->contacts[i].phone) == 0) {
                        goto searchContact;
                    }
                }

                printf("No contact found ");
                goto confirmPhone;
                return;

searchContact:
                printf("Name: %s\nMobile number: %s\nEmail: %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                
            break;
        case 2:
              printf("Enter the mobile number to be searched: ");    // enter the mobile no to be searched and  list the details.
              getchar();
                    scanf("%[^\n]",phone);
                    for(int i=0;i<addressBook ->contactCount;i++)
                    {
                            if(!strcmp(phone,addressBook->contacts[i].phone))
                            {
                                    printf("Name: %s\nMobile number :%s\nEmail :%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            }
                    }
                    break;    
              case 3:
             printf("Enter the email to be searched: ");    // enter the email  to bre  searched 
             getchar();
                    scanf("%[^\n]",email);
                    for(int i=0;i<addressBook ->contactCount;i++)
                    {
                            if(!strcmp(email,addressBook->contacts[i].email))
                            {
                                    printf("Name: %s\nMobile number :%s\nEmail :%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            }
                    }
                    break;

            default:
                printf("Invalid choice\n");    //  press 4 for the invalid choice t.
    }
    }while(option!=4);
}


void editContact(AddressBook *addressBook)
{
     char name[50];
     char phone[20];
     char email[50];
      printf("\nEnter the option: \n");                                                     
      printf("1.Name\n2.Mobile number \n3.E-mail \n");  //choose the opotion for edit.
         
      int option;
    scanf("%d",&option);
    int flag=0;
    switch(option)
    {
        case 1:
        reenter:
                        printf("Enter the name:");       // enter the name you want to edit.
            getchar();
            scanf("%[^\n]",name);
                        int i,j;
                    
                  
                       for (i=0; i<addressBook->contactCount; i++)
                       {  
                         if(strcmp(name,addressBook->contacts[i].name) == 0)  // if the name matches edit the name if more than one name confirm it eith mobile.
                          { 
                
                           for(j=i+1;j<addressBook->contactCount;j++)
                           {  
                           if(strcmp(name,addressBook->contacts[j].name)==0)
                           {
                        
                             goto confirmPhone;
                           }
                           } 
                
                           goto editContact;
                           }
                        } 
        printf(" Please Try again\n");   // if contcat not found renter .
        goto reenter;
    
        confirmPhone:
        reenter_mobile:printf("Enter the mobile number to confirm: ");    
        getchar(); 
        scanf("%[^\n]", phone);

        
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(name, addressBook->contacts[i].name) == 0 &&
                strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                goto editContact;
            }
        }
        printf("Please Try again\n");
        goto reenter_mobile;
        

editContact:
       
        printf("Enter the new name: ");  // enter the new name to edit
        getchar(); 
        scanf("%[^\n]", name);
        strcpy(addressBook->contacts[i].name, name);
        break;



              case 2:
                        printf("Enter the phone number:");   //enter the phone number  yoy wnt to edit  .compare ith with phone nuber from contacts .
							     // if found edit the phone number.
                        getchar();
                        scanf("%[^\n]",phone);
                         for(int i=0;i<addressBook ->contactCount;i++)
                         {
                                  if(!strcmp(phone,addressBook->contacts[i].phone))
                                  {
                      
                                          printf("Enter the new number:");
                                          getchar();
                                          scanf("%[^\n]",phone);
                                          strcpy(addressBook->contacts[i].phone,phone);
                      flag=1;
                      break;

                                           //printf("Name: %s\nMobile number :%s\nEmail :%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                  }
                         }
                         if (!flag) {
                                      printf("phone number not exist. Renter\n");
                                      editContact(addressBook);  
                                    } 
                                        break;
              case 3:
                        printf("Enter the email:");   //enter the email
                        getchar();
                        scanf("%[^\n]",email);
                         for(int i=0;i<addressBook ->contactCount;i++)
                         {
                                  if(!strcmp(email,addressBook->contacts[i].email))
                                  { 
                                          printf("Enter the new email:");   //enter the new mail yo want.
                                         getchar();
                                          scanf("%[^\n]",email);
                                          strcpy(addressBook->contacts[i].email,email);
                      flag=1;
                                break;		      
                                }
                         }
             if (!flag) 
             {
                              printf("Mail not found. Please try again.\n");
                              editContact(addressBook);  
                         }
                         break;
                        
              default:
                 
                printf("Invalid option. Please try again.\n");
                            editContact(addressBook);

              
        
    }
    
}

void deleteContact(AddressBook *addressBook) {
    char name[50], phone[20];
    int i, j;
    
    reenter: printf("\nEnter the name to delete:\n");     // enter the name to delete.
    getchar();
    scanf("%[^\n]", name); 
    
    
    for (i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(name, addressBook->contacts[i].name) == 0) {  // if the name presentdelete the contact .
								 // if more than one name confirm it with mobile number
            
            for (j = i + 1; j < addressBook->contactCount; j++) {
                
                if (strcmp(name, addressBook->contacts[j].name) == 0) {     
                    goto confirmPhone;  
                }
            }
            
            goto deleteContact; 
        }
    }
    
    
    printf("Contact not found.Please try again");   
    goto reenter;
    return;
    // compare the phone number present to confirm.
confirmPhone: 
       printf("\nEnter the mobile number to confirm:");
    getchar(); 
    scanf("%[^\n]", phone);

    
    for (i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(name, addressBook->contacts[i].name) == 0 &&
            strcmp(phone, addressBook->contacts[i].phone) == 0) {
            goto deleteContact; 
        }
    }
     printf("Phone number not exist.!! Please reenter");
     goto confirmPhone;
    return;
// to remove the contact shift the list.
deleteContact: 
    for (j = i; j < addressBook->contactCount - 1; j++) {
        addressBook->contacts[j] = addressBook->contacts[j + 1]; 
    }
    addressBook->contactCount--; 
    
} 
