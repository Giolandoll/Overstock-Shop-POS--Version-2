/*
Name: Giovanni Falconer
Date: December 29, 2022
Description:

  This program is the second version of the OverStock Shop Program. 

•	Program will be able to do sales calculations for the owner. 
•	System tracks the stock amounts by automatically updating the database of the products sold throughout the day. 
•	System will output final amount of money earned for the day upon request from the owner. 
•	System will output a receipt of purchase for each sale throughout the day when requested.
•	System will give alert to notify the owner that a stock amount has fallen to zero. 
•	The program will import the data from the database automatically.
•	The program will generate an in-depth report about the number of items sold and the total earned.
•	The program will have a password system with the ability to change the password.
•	The program will allow for the storage of customer names, phone numbers and money owed for items they took with the intent of paying later.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

//This struct stores all information relating to products and shop operation.
struct items
{
  int itemnum;
  char itemname[255];
  double price;
  int stock;
  char receipt[250];
  double receiptprice;
  // int quantity;
  int receipt_count;
  int daily_sold;     // Amount of item sold.
  double item_total;  // Amount of money made by each item.
  double daily_total; // Total cash for the day.
  double daily_owed;
};

//This struct stores all information relating to the security of the program.
struct login
{
    char password[32];
    int condition;
};

// This struct deals with client database.
struct client
{
  double money_owed;
  char client_name[255];
  char client_phone[12];
};

// Lines declare functions to allow writing after main function
int login(struct login details[], int num1, struct items item[]);
void Menu();
void SUBMenu();
int updates(struct items item[], int num1);
void closing(struct items item[], struct login details[], int num1);
int import(struct items item[], struct login details[]);
void receipt(struct items item[], double change, double payment, double subtotal, int num1);
void price_list(struct items item[], int num1);
void stocks(struct items item[], int num1);
void calculations(struct items item[], int num1);
void daysfinal(struct items item[], int num1);
int import2(struct client clientInfo[]);
void writer(struct client clientInfo[], int c);
// void password(struct login details[]);

//Main Function that calls all functions when user requests..
int main()
{
  
  struct login details[3];
  struct items item[50];
  char temp, password[32];
  int userinput,userinput1, counter, userRank, validation;


  
  printf("                                    __    __  ________  __       __       ______     \n");
  printf("                                   | \\  | \\  |        \\|  \\     |  \\    /       \\      \n");
  printf("                                   | $$  | $$| $$$$$$$$| $$     | $$    |  $$$$$$\\    \n");
  printf("                                   | $$__| $$| $$__    | $$     | $$    | $$  | $$    \n");
  printf("                                   | $$    $$| $$  \\   | $$     | $$    | $$  | $$    \n");
  printf("                                   | $$$$$$$$| $$$$$   | $$     | $$    | $$  | $$  \n");
  printf("                                   | $$  | $$| $$_____ | $$_____| $$____| $$__/ $$  \n");
  printf("                                   | $$  | $$| $$     \\| $$     \\ $$     \\$$    $$  \n");
  printf("                                    \\$$   \\$$ \\$$$$$$$$\\$$$$$$$$$\\$$$$$$$$\\$$$$$$   \n");

  printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______\n");
  printf("|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|$$$$$$|\n");

  printf("|Click Enter:");
  getch();

  system("cls");

  counter = import(item, details);

  userRank = login(details, counter, item);

  do{
    switch(userRank){
      system("cls");
      case 1: 
          system("cls");
          Menu();
          printf("\t\t\t\t   Please select the number of the desired option: ");
          validation = scanf("%d", &userinput);
          while (validation != 1){
             printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
             scanf("%*[^\n]");
             printf("\n\t\t\t\t  |[CLICK ENTER]:");
             getch();
             printf("\t\t\t\t   Please select the number of the desired option: ");
             validation = scanf("%d", &userinput);
          }
          
          switch(userinput){

            case 1: 
              calculations(item,  counter);
              break;
            case 2:
              system("cls");
              stocks(item, counter);
              break;
            case 3:
              daysfinal(item, counter);
              break;
            case 4:
              system("cls");
              counter =updates(item, counter);
              break;
            case 5:
             system("cls");
             printf("\t\t |=========================================================================================|\n");
             printf("\t\t |                                          LOGIN                                          |\n");
             printf("\t\t |=========================================================================================|\n");
             printf("\t\t |                                                                                         |\n");
             printf("\t\t\t\t   Please enter your current password: ");
             scanf("%c", &temp);
             scanf("%[^\n]", password);

              
            if(!strcmp(password, details[0].password)){
              // while (strcmp(details[0].password, password))
              // {
                printf("\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t   Please enter your new password(<32 characters):");
                scanf("%c", &temp);
                scanf("%[^\n]", details[1].password);
                printf("\n\t\t\t\t  |[CLICK ENTER]:");
                getch();

                printf("\n\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t    Please enter your new password AGAIN(<32 characters):");
                scanf("%c", &temp);
                scanf("%[^\n]", details[2].password);

                if(strcmp(details[1].password, details[2].password)){
                   printf("\t\t\t\t  Passwords don't match. Try again.");
                }else{
                  printf("\t\t\t\t  Password set.");
                  strcpy(details[0].password, details[1].password);
                }

            }else{
              printf("\t\t\t\t  [= INCORRECT PASSWORD=]");
              printf("\n\t\t\t\t  |[CLICK ENTER]:");
              getch();
              
            }
          
            break;
          case 6:
            closing(item, details, counter);
            return 0;
            break;
          default:
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
            break;
        }
        break;
      
      case 2:
        system("cls");
        SUBMenu();  
        printf("\t\t\t\t   Please select the number of the desired option: ");
        validation = scanf("%d", &userinput);
        while (validation != 1){
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
            printf("\t\t\t\t   Please select the number of the desired option: ");
            validation = scanf("%d", &userinput);
        }
          
        switch (userinput)
        {
        case 1:
          system("cls");
          calculations(item, counter);
          break;
        case 2:
          system("cls");
          stocks(item, counter);
          break;
        case 3:
          system("cls");
          daysfinal(item, counter);
          break;
        case 4:
          closing(item, details, counter);
          return 0;
          break;
        
        default:
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          break;
        }
      break;         
    }

    printf("\n\t\t\t\t  |                                                             |\n");
    printf("\t\t\t\t  Execute another function? (Enter 1 for YES and 2 for NO):");

    validation = scanf("%d", &userinput1);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   DO YOU WISH TO EXCECUTE ANOTHER FUNCTION? (1 for YES and 2 FOR NO): ");
        validation = scanf("%d", &userinput1);
      }
      while ((userinput1 != 1) && (userinput1 != 2))
        {
          
        printf("\t\t\t\t  DO YOU WISH TO EXCECUTE ANOTHER FUNCTION? (1 for YES and 2 FOR NO): ");
        validation = scanf("%d", &userinput1);
        while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t  DO YOU WISH TO EXCECUTE ANOTHER FUNCTION? (1 for YES and 2 FOR NO): ");
            validation = scanf("%d", &userinput1);
          }
      }
    // printf("\t\t\t\t  |                                                             |\n");
    // printf("\t\t\t\t   Execute another function? (Enter 1 for YES and 2 for NO):");

    // validation = scanf("%d", &userinput1);
    // while(userinput1 != 1 && userinput1 != 2 && validation != 1){
    //   printf("\t\t\t\t   Execute another function? (Enter 1 for YES and 2 for NO):");
    //   validation = scanf("%d", &userinput1);
    // }

  }while(userinput1 == 1);
  printf("\t\t\t\t  Goodbye");
  closing(item, details, counter);
  return 0;
}


/*This function assigns the rank of the user based on the option they select and whether or not they know 
the password for the accounts. Allows for the setting of a new password for the first lauch of the program*/
int login(struct login details[], int num1, struct items item[] )
{
  system("cls");
  int userRank, userinput, found = 0;
  int choice, validation = 0;
  char password[32], temp;
  FILE * dpointer = NULL;
  printf("\t\t\t\t  |======================== LOGIN ========================|\n");
  printf("\t\t\t\t  |                                                       |\n");
  printf("\t\t\t\t  |                      USER OPTIONS                     |\n");
  printf("\t\t\t\t  |  1---> Owner                                          |\n");
  printf("\t\t\t\t  |  2---> Shopkeeper                                     |\n");
  printf("\t\t\t\t  |  3---> Exit                                           |\n");
  printf("\t\t\t\t  |=======================================================|\n");

  printf("\t\t\t\t   Please select the number of the desired option: ");
  validation = scanf("%d", &userinput);
  while (validation != 1)
  {
    printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
    scanf("%*[^\n]");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    system("cls");
    printf("\t\t\t\t  |======================== LOGIN ========================|\n");
    printf("\t\t\t\t  |                                                       |\n");
    printf("\t\t\t\t  |                      USER OPTIONS                     |\n");
    printf("\t\t\t\t  |  1---> Owner                                          |\n");
    printf("\t\t\t\t  |  2---> Shopkeeper                                     |\n");
    printf("\t\t\t\t  |  3---> Exit                                           |\n");
    printf("\t\t\t\t  |=======================================================|\n");
    printf("\t\t\t\t   Please select the number of the desired option: ");
    validation = scanf("%d", &userinput);
  }

  switch (userinput)
  {
  case 1:
    dpointer = fopen("OVERSTOCK-SHOP-SECURITY.txt", "r");
    // if(details[0].condition == NULL)
    if(dpointer == NULL || details[0].condition== 0){
      while (strcmp(details[0].password, details[1].password))
      {
          
        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t   Please enter your new password(<32 characters):");
        scanf("%c", &temp);
        scanf("%[^\n]", details[0].password);
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();

        printf("\n\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t   Please enter your new password AGAIN(<32 characters):");
        scanf("%c", &temp);
        scanf("%[^\n]", details[1].password);
        if(strcmp(details[0].password, details[1].password))
          printf("\t\t\t\t  Passwords don't match. Try again.");
        }
        printf("\t\t\t\t\t   [= PASSWORD SET =]\n");
        details[0].condition = 1;
    }
    fclose(dpointer);

    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                          LOGIN                                          |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");
    do
    {
      choice = 1;
      printf("\t\t\t\t  |                                                       |\n");
      printf("\t\t\t\t  |======================== OWNER ========================|\n");
      printf("\t\t\t\t   PASSWORD: ");
      scanf("%s", password);
      if (!strcmp(password, details[0].password))
      {
        found = 1;
        printf("\t\t\t\t  Login Successful\n");
        userRank = 1;
        printf("\n\t\t\t\t  |[CLICK ENTER]: ");
        getch();
        system("cls");
      }
      else
      {
        printf("\t\t\t\t   Incorrect password\n");
        printf("\t\t\t\t   Do you wish to try again? (Enter 1 for YES and 2 for No):");
        validation = scanf("%d", &choice);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t   Do you wish to try again? (Enter 1 for YES and 2 for No):");
          validation = scanf("%d", &choice);
        }
        while ((choice != 1) && (choice != 2))
        {
          printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
          printf("\t\t\t\t   Do you wish to try again? (Enter 1 for YES and 2 for No):");
          validation = scanf("%d", &choice);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
            printf("\n\t\t\t\t   Do you wish to try again? (Enter 1 for YES and 2 for No):");
            validation = scanf("%d", &choice);
          }
        }
        system("cls");
      }
    } while (found == 0 && choice == 1);
    // userRank = 1;
    break;
  case 2:
    printf("\t\t\t\t  |                                                       |\n");
    printf("\t\t\t\t   Login Successful \n");
    userRank = 2;
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    system("cls");
    break;
  case 3:
    closing(item, details, num1);
    break;
  default:
    printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    system("cls");
    printf("\t\t\t\t   The system will now be stopped. Please restart. ");
    break;
  }
  return userRank;
}

//This function displays the options for the Rank: 1 USER.
void Menu()

{

  printf("\t\t\t\t  |========================  MENU  ========================|\n");
  printf("\t\t\t\t  |                                                        |\n");
  printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
  printf("\t\t\t\t  |  1---> CONDUCT A SALE                                  |\n");
  // printf("\t\t\t\t  |  2---> CLIENT DATABASE                                 |\n");
  printf("\t\t\t\t  |  2---> STOCK AMOUNTS                                   |\n");
  printf("\t\t\t\t  |  3---> DAILY REPORT                                    |\n");
  printf("\t\t\t\t  |  4---> ADD ITEM OR UPDATE ITEM INFORMATION             |\n");
  // printf("\t\t\t\t  |  5---> MONTHLY REPORT                                  |\n");
  printf("\t\t\t\t  |  5---> PASSWORD CHANGE                                 |\n");
  printf("\t\t\t\t  |  6---> Exit                                            |\n");
  printf("\t\t\t\t  |========================================================|\n");
}

//This function displays the options for the Rank: 2 USER.
void SUBMenu()
{

  printf("\t\t\t\t  |========================  MENU  ========================|\n");
  printf("\t\t\t\t  |                                                        |\n");
  printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
  printf("\t\t\t\t  |  1---> CONDUCT A SALE                                  |\n");
  // printf("\t\t\t\t  |  2---> CLIENT DATABASE                                 |\n");
  printf("\t\t\t\t  |  2---> STOCK AMOUNTS                                   |\n");
  printf("\t\t\t\t  |  3---> DAILY REPORT                                    |\n");
  printf("\t\t\t\t  |  4---> Exit                                            |\n");
  printf("\t\t\t\t  |========================================================|\n");
}

//This function writes data from the main Stock info file and the Security file into their respective structs. 
int import(struct items item[], struct login details[])
{
  char c;
  int i = 0;
  char line[255];
  FILE *dpointer = fopen("OVERSTOCK-SHOP-INFO.txt", "r");

  if (dpointer == NULL) {
    printf("\t\t\t\t [= Unable to open file =]\n");
    scanf("%*[^\n]");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    system("cls");

  }
  else {
    while (fgets(line, sizeof(line), dpointer)) {
      char * word = strtok(line, "|");
      item[i].itemnum = atoi(word);
      // strcpy(clientInfo[i].client_phone, word);

      word = strtok(NULL, "|");
      strcpy(item[i].itemname, word);

      // word = strtok(NULL, "|");
      // strcpy(clientInfo[i].client_name, word);

      word = strtok(NULL, "|");
      item[i].price = atof(word);

      word = strtok(NULL, "|");
      item[i].stock = atoi(word);

      // word = strtok(NULL, "|");
      // strcpy(passengers[i].lname, word);

      // word = strtok(NULL, "|");
      // strcpy(passengers[i].school, word);

      // word = strtok(NULL, "|");
      // passengers[i].balance_due = atof(word);

      // word = strtok(NULL, "|");
      // passengers[i].total_attendance = atoi(word);

      i++;
    }
  }
  fclose(dpointer);
 


  FILE *spointer = fopen("OVERSTOCK-SHOP-SECURITY.txt", "r");
  // while ((c = getc(spointer)) != EOF)
  // {
  //   // fscanf(spointer, "%s %d", details[0].password, &details[0].condition);
  // }
   while (fgets(line, sizeof(line), spointer)) {
      char * word = strtok(line, "|");
      strcpy(details[0].password, word);
      
      
      word = strtok(NULL, "|");
      details[0].condition = atoi(word);
   }
  fclose(spointer);

   return i;
}

//This function writes data to the main Stock info file and the security file. 
void closing(struct items item[], struct login details[], int num1){
  int j;
  FILE *dpointer = fopen("OVERSTOCK-SHOP-INFO.txt", "w");

  for (j = 0; j < num1; j++) {
    fprintf(dpointer, " %d|%s|%.2f|%d|\n", item[j].itemnum, item[j].itemname, item[j].price, item[j].stock);
  }
  fclose(dpointer);

  FILE *spointer = fopen("OVERSTOCK-SHOP-SECURITY.txt", "w");

    fprintf(spointer, "%s|%d|", details[0].password, details[0].condition);

  fclose(spointer);
}

//This function reads data to the client database struct.
int import2(struct client clientInfo[]){ 
  //  int i = 0;
  //  char c;

  //   FILE *dpointer = fopen("OVERSTOCK-CLIENT-INFO.txt", "r");

  // while ((c = getc(dpointer)) != EOF)
  // {
  //   fscanf(dpointer, " %s %lf  %s", clientInfo[i].client_phone, &clientInfo[i].money_owed,  clientInfo[i].client_name);
  //   // printf("hello\n");
  //   // getch();
  //   i++;
  // }
  int i = 0;
  char line[255];
  FILE * dpointer = NULL;
  dpointer = fopen("OVERSTOCK-CLIENT-INFO.txt", "r");

  if (dpointer == NULL) {
    printf("\t\t\t\t [= Unable to open file =]\n");
    // scanf("%*[^\n]");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    
    // system("cls");
    return 0;

  }
  else {
    while (fgets(line, sizeof(line), dpointer)) {
      char * word = strtok(line, "|");
      strcpy(clientInfo[i].client_phone, word);

      word = strtok(NULL, "|");
      clientInfo[i].money_owed = atof(word);

      word = strtok(NULL, "|");
      strcpy(clientInfo[i].client_name, word);

      // word = strtok(NULL, "|");
      // strcpy(passengers[i].lname, word);

      // word = strtok(NULL, "|");
      // strcpy(passengers[i].school, word);

      // word = strtok(NULL, "|");
      // passengers[i].balance_due = atof(word);

      // word = strtok(NULL, "|");
      // passengers[i].total_attendance = atoi(word);

      i++;
    }
  }
  fclose(dpointer);
  return i;
}
  
//This function stores data to the client data file. 
void writer(struct client clientInfo[], int c){
  int j;
  FILE *dpointer = fopen("OVERSTOCK-CLIENT-INFO.txt", "w");

  for (j = 0; j < c; j++) {
    fprintf(dpointer, " %s|%.2f|%s|\n", clientInfo[j].client_phone, clientInfo[j].money_owed, clientInfo[j].client_name);
  }
  fclose(dpointer);
}


/*This function allows for the modification of item's data. Items are using this function .The stock and price are able to be changed.
Items can also be deleted using this function*/ 
int updates(struct items item[], int num1)
{
  int userinput, i, counter, found, validation = 0;
  char temp, name[255];
  double price;

  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                                                                         |\n");

  printf("\t\t\t\t  |========================  MENU  ========================|\n");
  printf("\t\t\t\t  |                                                        |\n");
  printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
  printf("\t\t\t\t  |  1---> ADD NEW ITEMS                                   |\n");
  printf("\t\t\t\t  |  2---> UPDATE CURRENT ITEMS                            |\n");
  printf("\t\t\t\t  |========================================================|\n");

  printf("\t\t\t\t   Please select the number of the desired option: ");
  validation = scanf("%d", &userinput);
  while (validation != 1)
  {
    printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
    scanf("%*[^\n]");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");

    printf("\t\t\t\t  |========================  MENU  ========================|\n");
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
    printf("\t\t\t\t  |  1---> ADD NEW ITEMS                                   |\n");
    printf("\t\t\t\t  |  2---> UPDATE CURRENT ITEMS                            |\n");
    printf("\t\t\t\t  |========================================================|\n");
    printf("\t\t\t\t   Please select the number of the desired option: ");
    validation = scanf("%d", &userinput);
  }

  switch (userinput)
  {
  case 1:
    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");

    printf("\t\t\t\t  |========================  MENU  ========================|\n");
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
    printf("\t\t\t\t  |  1---> CREATE NEW LIST                                 |\n");
    printf("\t\t\t\t  |  2---> ADD TO CURRENT LIST                             |\n");
    printf("\t\t\t\t  |========================================================|\n");
    printf("\t\t\t\t   Please select the number of the desired option: ");

    validation = scanf("%d", &userinput);
    while (validation != 1)
    {
      printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
      scanf("%*[^\n]");
      printf("\n\t\t\t\t  |[CLICK ENTER]:");
      getch();
      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t  |========================  MENU  ========================|\n");
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
      printf("\t\t\t\t  |  1---> CREATE NEW LIST                                 |\n");
      printf("\t\t\t\t  |  2---> ADD TO CURRENT LIST                             |\n");
      printf("\t\t\t\t  |========================================================|\n");
      printf("\t\t\t\t   Please select the number of the desired option: ");
      validation = scanf("%d", &userinput);
    }
    switch (userinput)
    {
    case 1:
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t   Enter the number of items(LESS THAN 50):");
      validation = scanf("%d", &counter);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   Enter the number of items(LESS THAN 50):");
        validation = scanf("%d", &counter);
      }

      printf("\t\t\t\t  |                                                        |\n");
      if (counter > 50)
      {
        printf("\t\t\t\t\t   [=Value entered is too large=]\n");
        printf("\t\t\t\t   Enter the number of items(LESS THAN 50):");
        validation = scanf("%d", &counter);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t   Enter the number of items(LESS THAN 50):");
          validation = scanf("%d", &counter);
        }
      }

      for (i = 0; i < counter; i++)
      {
        printf("\n\t\t\t\t  |--------------------------------------------------------|\n");

        printf("\t\t\t\t   Name of item: ");
        scanf("%c", &temp);
        scanf("%[^\n]", item[i].itemname);

        printf("\t\t\t\t   Price: ");
        validation = scanf("%lf", &item[i].price);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t    Price: ");
          validation = scanf("%lf", &item[i].price);
        }

        printf("\t\t\t\t   Stock Amount:");
        validation = scanf("%d", &item[i].stock);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t    Stock Amount:");
          validation = scanf("%lf", &item[i].stock);
        }

        item[i].itemnum = i + 1;

        printf("\t\t\t\t\t [= ITEM NUMBER %d HAS BEEN ENTERED =] \n", i + 1);
        printf("\t\t\t\t  |[CLICK ENTER]: ");
        getch();
      }

      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t\t  THE LIST OF ITEMS IS AS FOLLOWS\n");
      price_list(item, counter);
      printf("\t\t |                                                                                         |\n");
      printf("\t\t\t\t  |[CLICK ENTER]: ");
      getch();

      break;
    case 2:
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t   Enter the number of items to add:");
      validation = scanf("%d", &counter);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   Enter the number of items to add:");
        validation = scanf("%d", &counter);
      }

      printf("\t\t\t\t  |                                                        |\n");
      int remainder = 50 - num1;
      while (counter > remainder)
      {
        printf("\t\t\t\t   [=The number added will exceed limit=]\n");
        printf("\t\t\t\t   Enter value less than %d. \n", remainder);
        printf("\t\t\t\t  |--------------------------------------------------------|\n");
        printf("\t\t\t\t   Enter the number of items to add:");
        validation = scanf("%d", &counter);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t   Enter the number of items to add:");
          validation = scanf("%d", &counter);
        }
      }

      for (i = num1; i < (counter + num1); i++)
      {

        printf("\n\t\t\t\t  |--------------------------------------------------------|\n");

        printf("\t\t\t\t   Name of item: ");
        scanf("%c", &temp);
        scanf("%[^\n]", item[i].itemname);

        printf("\t\t\t\t   Price: ");
        validation = scanf("%lf", &item[i].price);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t    Price: ");
          validation = scanf("%lf", &item[i].price);
        }

        printf("\t\t\t\t   Stock Amount:");
        validation = scanf("%d", &item[i].stock);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t    Stock Amount:");
          validation = scanf("%lf", &item[i].stock);
        }

        item[i].itemnum = i + 2;

        printf("\t\t\t\t\t [= ITEM NUMBER %d HAS BEEN ENTERED =] \n", i + 1);
        printf("\t\t\t\t  |[CLICK ENTER]: ");
        getch();
      }
      counter = counter + num1;

      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t\t   THE LIST OF ITEMS IS AS FOLLOWS\n");
      price_list(item, counter);
      printf("\t\t |                                                                                         |\n");
      printf("\t\t\t\t  |[CLICK ENTER]: ");
      getch();
      break;
    default:
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
      printf("\n\t\t\t\t  |[CLICK ENTER]:");
      getch();
      break;
    }
    break;
  case 2:
    counter = num1;
    do
    {

      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");
      price_list(item, counter);

      printf("\t\t\t |--------------------------------------------------------------------------|\n");
      printf("\t\t\t  Please enter the item-number of the item you wish to update: ");
      validation = scanf("%d", &userinput);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   Please enter the item-number of the item you wish to find:");
        validation = scanf("%d", &userinput);
      }

      i = 0;
      found = 0;
      while (found == 0 && i <= counter)
      {
        if (userinput == item[i].itemnum)
        {
          found = 1;
          printf("\t\t\t  Your item was selected.\n");
          printf("\t\t\t\t  |[CLICK ENTER]: ");
          getch();
        }
        else
        {
          i++;
        }
      }

      if (found == 1)
      {
        system("cls");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                                                                         |\n");

        printf("\t\t\t  Item number: %d\n", item[i].itemnum);
        printf("\t\t\t  Item name: %s\n", item[i].itemname);
        printf("\t\t\t  Price: %.2f\n", item[i].price);
        printf("\t\t\t  Stock: %d\n", item[i].stock);

        printf("\t\t |                                                                                         |\n");

        printf("\t\t\t\t  |========================  MENU  ========================|\n");
        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
        printf("\t\t\t\t  |  1---> CHANGE STOCK AMOUNT                             |\n");
        printf("\t\t\t\t  |  2---> CHANGE PRICE                                    |\n");
        printf("\t\t\t\t  |  3---> DELETE ITEM                                     |\n");
        printf("\t\t\t\t  |========================================================|\n");
        printf("\t\t\t\t   Please select the number of the desired option: ");

        validation = scanf("%d", &userinput);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();

          system("cls");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                                                                         |\n");

          printf("\t\t\t  Item number: %d\n", item[i].itemnum);
          printf("\t\t\t  Item name: %s\n", item[i].itemname);
          printf("\t\t\t  Price: %.2f\n", item[i].price);
          printf("\t\t\t  Stock: %d\n", item[i].stock);

          printf("\t\t |                                                                                         |\n");

          printf("\t\t\t\t  |========================  MENU  ========================|\n");
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
          printf("\t\t\t\t  |  1---> CHANGE STOCK AMOUNT                             |\n");
          printf("\t\t\t\t  |  2---> CHANGE PRICE                                    |\n");
          printf("\t\t\t\t  |  3---> DELETE ITEM                                     |\n");
          printf("\t\t\t\t  |========================================================|\n");
          printf("\t\t\t\t   Please select the number of the desired option: ");
          validation = scanf("%d", &userinput);
        }

        switch (userinput)
        {
        case 1:
          printf("\t\t\t\t   Please enter the update for the item's stock:");
          validation = scanf("%d", &userinput);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t   Please enter the update for the item's stock:");
            validation = scanf("%d", &userinput);
          }
          item[i].stock = item[i].stock + userinput;

          printf("\t\t\t\t\t\t  [= STOCK CHANGE COMPLETED =]\n");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          break;
        case 2:
          printf("\t\t\t\t   Please enter the update for the item's price:");
          validation = scanf("%lf", &price);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t   Please enter the update for the item's price:");
            validation = scanf("%lf", &price);
          }
          item[i].price = price;

          printf("\t\t\t\t\t\t  [= PRICE CHANGE COMPLETED =]\n");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          break;
        case 3:
          printf("\t\t\t\t   Are you sure you want to delete item-number: [%d]?\n", item[i].itemnum);
          printf("\t\t\t\t   Enter 1 for YES and 2 for NO:");
          validation = scanf("%d", &userinput);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
            printf("\t\t\t\t   Are you sure you want to delete item-number %d?", item[i].itemnum);
            printf("\t\t\t\t   Enter 1 for YES and 2 for NO:");
            validation = scanf("%d", &userinput);
          }

          if (userinput == 1)
          {
            for (int j = i - 1; j < num1; j++)
            {
              item[j].itemnum = item[j + 1].itemnum;
              strcpy(item[j].itemname, item[j + 1].itemname);
              item[j].price = item[j + 1].price;
              item[j].stock = item[j + 1].stock;
            }
            counter = num1 - 1;
            system("cls");
            printf("\t\t |=========================================================================================|\n");
            printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
            printf("\t\t |=========================================================================================|\n");
            printf("\t\t |                                                                                         |\n");

            printf("\t\t\t\t   THE UPDATED LIST OF ITEMS IS AS FOLLOWS\n");
            price_list(item, counter);
            printf("\t\t |                                                                                         |\n");
            printf("\t\t\t\t  |[CLICK ENTER]: ");
            getch();
          }
          else
          {
            printf("\t\t\t\t   DELETION PROCESS CANCELLED");
          }
          break;
        default:
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          break;
        }
      }
      else if (found == 0)
      {
        system("cls");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                                                                         |\n");
        printf("\t\t\t  Your item was not found.\n");
        printf("\t\t\t\t  |[CLICK ENTER]: ");
        getch();
      }
      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t   SEARCH AGAIN? (Enter 1 for YES and 2 for NO):");
      validation = scanf("%d", &userinput);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();
        printf("\t\t\t\t   SEARCH AGAIN? (Enter 1 for YES and 2 for NO):");
        validation = scanf("%d", &userinput);
      }

      printf("\t\t\t\t  |[CLICK ENTER]: ");
      getch();

      while ((userinput != 1) && (userinput != 2))
      {
        system("cls");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                 UPDATE ITEM INFROMATION                                 |\n");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                                                                         |\n");

        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
        printf("\t\t\t\t   SEARCH AGAIN? (Enter 1 for YES and 2 for NO):");
        validation = scanf("%d", &userinput);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          printf("\t\t\t\t   SEARCH AGAIN? (Enter 1 for YES and 2 for NO):");
          validation = scanf("%d", &userinput);
        }
      }
    } while (userinput == 1);
    break;
  default:
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    break;
  }
  return counter;
}

//Displays the list of items and their respective prices.
void price_list(struct items item[], int num1)
{
  int i;
  printf("\t\t\t\t  |                                                     |\n");
  printf("\t\t\t\t  | ITEM CODE |\t ITEM NAME \t|\t PRICE \t\t|\n");

  for (i = 0; i < num1; i++)
  {
    printf("\t\t\t\t  |     %d     |\t %s \t|\t $%.2f \t| \n", item[i].itemnum, item[i].itemname, item[i].price);
  }
  printf("\t\t\t\t  |=====================================================|\n");
}

//Displays the list of items and their respective stock amounts.

void stocks(struct items item[], int num1)
{
  int i, userinput;

  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                   STOCK INFROMATION                                     |\n");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                                                                         |\n");
  printf("\t\t\t\t\t  | ITEM CODE |\t ITEM NAME\t|\tSTOCK\t|\n");
  printf("\t\t\t\t\t  |                                             |\n");

  for (i = 0; i < num1; i++)
  {
    printf("\t\t\t\t\t  |     %d     |\t %s \t| \t%d\t| \n", item[i].itemnum, item[i].itemname, item[i].stock);
  }
}


/*This function carries out all calculations done for sales throughtout the days. It allows for the creation of a client 
in the "PAY LATER" database as customers can take goods and pay later. The function also updates stock amounts as sales take place.*/
void calculations(struct items item[], int num1)
{
  int i, counter, found, userinput, validation, c;
  double change, payment, subtotal;
  char temp;
  double money_owed;
  char name[255], d;
  char client_phone[12];
  struct client clientInfo[100];

  system("cls");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                           SALES                                         |\n");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                                                                         |\n");

  printf("\t\t\t\t  |========================  MENU  ========================|\n");
  printf("\t\t\t\t  |                                                        |\n");
  printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
  printf("\t\t\t\t  |  1---> CONDUCT A SALE                                  |\n");
  printf("\t\t\t\t  |  2---> PAY-LATER CLIENTS                               |\n");
  printf("\t\t\t\t  |========================================================|\n");

  printf("\t\t\t\t   Please select the number of the desired option: ");
  validation = scanf("%d", &userinput);
  while (validation != 1)
  {
    printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
    scanf("%*[^\n]");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();

    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                           SALES                                         |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");

    printf("\t\t\t\t  |========================  MENU  ========================|\n");
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
    printf("\t\t\t\t  |  1---> CONDUCT A SALE                                  |\n");
    printf("\t\t\t\t  |  2---> PAY-LATER CLIENTS                               |\n");
    printf("\t\t\t\t  |========================================================|\n");
    printf("\t\t\t\t   Please select the number of the desired option: ");
    validation = scanf("%d", &userinput);
  }

  switch (userinput)
  {
  case 1:
    c = 0;
    subtotal = 0;
    do
    {
      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                           SALES                                         |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      price_list(item, num1);

      printf("\t\t\t\t   Please enter the item code: ");
      validation = scanf("%d", &userinput);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   Please enter the item code:");
        validation = scanf("%d", &userinput);
      }

      i = 0;
      found = 0;
      while (found == 0 && i < num1)
      {
        if (item[i].itemnum == userinput)
        {
          found = 1;
        }
        else
        {
          i++;
        }
      }

      if (found == 1)
      {
        system("cls");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                           SALES                                         |\n");
        printf("\t\t |=========================================================================================|\n");
        printf("\t\t |                                                                                         |\n");
        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t   Item selected: %s\n", item[i].itemname);
        printf("\t\t\t\t   Quantity ordered: ");
        validation = scanf("%d", &userinput);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t  Quantity ordered: ");
          validation = scanf("%d", &userinput);
        }

        if (item[i].stock >= userinput)
        {
          item[i].stock = item[i].stock - userinput;

          if (item[i].stock == 0)
          {
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT HAS FALLEN TO 0 =]                 \n");
            printf("\t\t\t\t  |                                                        |\n");
          }
          strcpy(item[c].receipt, item[i].itemname);
          item[c].receiptprice = item[i].price * userinput;
          c++;

          item[i].daily_sold = item[i].daily_sold + userinput;
          item[i].item_total = item[i].item_total + (item[i].price * userinput);
          item[0].daily_total = item[0].daily_total + (item[i].price * userinput);

          subtotal = subtotal + (item[i].price * userinput);
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t   Current Subtotal: $%.2f \n", subtotal);
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
        }
        else if (item[i].stock < userinput && item[i].stock != 0)
        {
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t\t [= INSUFFICIENT SUPPLY OF ITEM =]\n");
          printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
          validation = scanf("%d", &userinput);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
            validation = scanf("%d", &userinput);
          }
          while ((userinput != 1) && (userinput != 2))
          {
            printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
            printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
            validation = scanf("%d", &userinput);
            while (validation != 1)
            {
              printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
              scanf("%*[^\n]");
              printf("\n\t\t\t\t  |[CLICK ENTER]:");
              getch();
              printf("\n\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
              validation = scanf("%d", &userinput);
            }
          }

          if (userinput == 1)
          {
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t   Current stock held for item: %d\n", item[i].stock);
            printf("\t\t\t\t   Quantity ordered: ");
            validation = scanf("%d", &userinput);
            while (validation != 1)
            {
              printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
              scanf("%*[^\n]");
              printf("\t\t\t\t  Quantity ordered: ");
              validation = scanf("%d", &userinput);
            }
            while (userinput > item[i].stock)
            {
              printf("\t\t\t\t  |                                                        |\n");
              printf("\t\t\t\t\t [= INSUFFICIENT SUPPLY OF ITEM =]\n");
              printf("\t\t\t\t   Quantity ordered: ");
              validation = scanf("%d", &userinput);
              while (validation != 1)
              {
                printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
                scanf("%*[^\n]");
                printf("\t\t\t\t  Quantity ordered: ");
                validation = scanf("%d", &userinput);
              }
            }
            item[i].stock = item[i].stock - userinput;

            if (item[i].stock == 0)
            {
              printf("\t\t\t\t  |                                                        |\n");
              printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT HAS FALLEN TO 0 =]                 \n");
              printf("\t\t\t\t  |                                                        |\n");
            }
            strcpy(item[c].receipt, item[i].itemname);
            item[c].receiptprice = item[i].price * userinput;
            c++;

            item[i].daily_sold = item[i].daily_sold + userinput;
            item[i].item_total = item[i].item_total + (item[i].price * userinput);
            item[0].daily_total = item[0].daily_total + (item[i].price * userinput);

            subtotal = subtotal + (item[i].price * userinput);
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t   Current Subtotal: $%.2f\n", subtotal);
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
          }
          else
          {
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t   This item will not be added to the order list.\n");
            printf("\n\t\t\t\t  |[CLICK ENTER]:");
            getch();
          }
        }
        else if (item[i].stock == 0)
        {
          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT IS 0 =]                 \n");
          printf("\t\t\t\t  |                                                        |\n");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
        }
      }
      else
      {
        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t\t  [= ITEM NUMBER NOT FOUND =]                 \n");
        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t  |[CLICK ENTER]:");
        getch();
      }

      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                           SALES                                         |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
      validation = scanf("%d", &userinput);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
        validation = scanf("%d", &userinput);
      }
      while ((userinput != 1) && (userinput != 2))
      {
        printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
        printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
        validation = scanf("%d", &userinput);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\n\t\t\t\t  |[CLICK ENTER]:");
          getch();
          printf("\n\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
          validation = scanf("%d", &userinput);
        }
      }
    } while (userinput == 1);
    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                           SALES                                         |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t   Current Subtotal: $%.2f\n", subtotal);
    printf("\t\t\t\t   Payment Received: ");
    validation = scanf("%lf", &payment);
    while (validation != 1)
    {
      printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
      scanf("%*[^\n]");
      printf("\t\t\t\t  Payment Received: ");
      validation = scanf("%lf", &payment);
    }
    while (payment < subtotal)
    {
      printf("\t\t\t\t\t [= INSUFFICIENT AMOUNT ENTERED =] \n");
      printf("\t\t\t\t   ReEnter Payment Received:");
      validation = scanf("%lf", &payment);
      while (validation != 1)
      {
        printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
        scanf("%*[^\n]");
        printf("\t\t\t\t Payment Received: ");
        validation = scanf("%lf", &payment);
      }
    }

    change = payment - subtotal;
    receipt(item, change, payment, subtotal, c);
    break;
  case 2:
 
    c = 0;
    
    c = import2(clientInfo);
    subtotal = 0;
    //  printf("hello");
    // getch();

    system("cls");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                           SALES                                         |\n");
    printf("\t\t |=========================================================================================|\n");
    printf("\t\t |                                                                                         |\n");

    printf("\t\t\t\t  |========================  MENU  ========================|\n");
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
    printf("\t\t\t\t  |  1---> ADD NEW CLIENT                                  |\n");
    printf("\t\t\t\t  |  2---> LIST OF CLIENTS                                 |\n");
    printf("\t\t\t\t  |  3---> ACCEPT PAYMENT                                  |\n");
    printf("\t\t\t\t  |========================================================|\n");

    printf("\t\t\t\t   Please select the number of the desired option: ");
    validation = scanf("%d", &userinput);
    while (validation != 1)
    {
      printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
      scanf("%*[^\n]");
      printf("\n\t\t\t\t  |[CLICK ENTER]:");
      getch();

      system("cls");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                           SALES                                         |\n");
      printf("\t\t |=========================================================================================|\n");
      printf("\t\t |                                                                                         |\n");

      printf("\t\t\t\t  |========================  MENU  ========================|\n");
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t  |                      USER OPTIONS                      |\n");
      printf("\t\t\t\t  |  1---> ADD NEW CLIENT                                  |\n");
      printf("\t\t\t\t  |  2---> LIST OF CLIENTS                                 |\n");
      printf("\t\t\t\t  |  3---> ACCEPT PAYMENT                                  |\n");
      printf("\t\t\t\t  |========================================================|\n");

      printf("\t\t\t\t   Please select the number of the desired option: ");
      validation = scanf("%d", &userinput);
    }

    switch (userinput)
    {
    case 1:


        printf("\t\t\t\t  |                                                        |\n");
        printf("\t\t\t\t   Name: ");
        scanf("%c", &temp);
        scanf("%[^\n]", name);

        printf("\t\t\t\t   Phone Number(xxx-xxx-xxxx): ");
        scanf("%c", &temp);
        scanf("%[^\n]", client_phone);

        scanf("%[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();

        do
        {
          system("cls");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                           SALES                                         |\n");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                                                                         |\n");

          price_list(item, num1);

          printf("\t\t\t\t   Please enter the item code: ");
          validation = scanf("%d", &userinput);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t   Please enter the item code:");
            validation = scanf("%d", &userinput);
          }

          i = 0;
          found = 0;
          while (found == 0 && i < num1)
          {
            if (item[i].itemnum == userinput)
            {
              found = 1;
            }
            else
            {
              i++;
            }
          }

          if (found == 1)
          {
            system("cls");
            printf("\t\t |=========================================================================================|\n");
            printf("\t\t |                                           SALES                                         |\n");
            printf("\t\t |=========================================================================================|\n");
            printf("\t\t |                                                                                         |\n");
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t   Item selected: %s\n", item[i].itemname);
            printf("\t\t\t\t   Quantity ordered: ");
            validation = scanf("%d", &userinput);
            while (validation != 1)
            {
              printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
              scanf("%*[^\n]");
              printf("\t\t\t\t  Quantity ordered: ");
              validation = scanf("%d", &userinput);
            }

            if (item[i].stock >= userinput)
            {
              item[i].stock = item[i].stock - userinput;

              if (item[i].stock == 0)
              {
                printf("\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT HAS FALLEN TO 0 =]                 \n");
                printf("\t\t\t\t  |                                                        |\n");
              }

              // strcpy(item[c].receipt, item[i].itemname);
              // item[c].receiptprice = item[i].price * userinput;
              // c++;

              item[i].daily_sold = item[i].daily_sold + userinput;
              item[i].item_total = item[i].item_total + (item[i].price * userinput);
              item[0].daily_owed = item[0].daily_owed + (item[i].price * userinput);

              subtotal = subtotal + (item[i].price * userinput);
              printf("\t\t\t\t  |                                                        |\n");
              printf("\t\t\t\t   Current Subtotal: %.2f \n", subtotal);
              printf("\n\t\t\t\t  |[CLICK ENTER]:");
              getch();
            }
            else if (item[i].stock < userinput && item[i].stock != 0)
            {
              printf("\t\t\t\t  |                                                        |\n");
              printf("\t\t\t\t\t [= INSUFFICIENT SUPPLY OF ITEM =]\n");
              printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
              validation = scanf("%d", &userinput);
              while (validation != 1)
              {
                printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
                scanf("%*[^\n]");
                printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
                validation = scanf("%d", &userinput);
              }
              while ((userinput != 1) && (userinput != 2))
              {
                printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
                printf("\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
                validation = scanf("%d", &userinput);
                while (validation != 1)
                {
                  printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
                  scanf("%*[^\n]");
                  printf("\n\t\t\t\t  |[CLICK ENTER]:");
                  getch();
                  printf("\n\t\t\t\t   Do you wish to reorder? (Enter 1 for YES and 2 for NO): ");
                  validation = scanf("%d", &userinput);
                }
              }

              if (userinput == 1)
              {
                printf("\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t   Current stock held for item: %d\n", item[i].stock);
                printf("\t\t\t\t   Quantity ordered: ");
                validation = scanf("%d", &userinput);
                while (validation != 1)
                {
                  printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
                  scanf("%*[^\n]");
                  printf("\t\t\t\t  Quantity ordered: ");
                  validation = scanf("%d", &userinput);
                }

                while (userinput > item[i].stock)
                {
                  printf("\t\t\t\t  |                                                        |\n");
                  printf("\t\t\t\t\t [= INSUFFICIENT SUPPLY OF ITEM =]\n");
                  printf("\t\t\t\t   Quantity ordered: ");
                  validation = scanf("%d", &userinput);
                  while (validation != 1)
                  {
                    printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
                    scanf("%*[^\n]");
                    printf("\t\t\t\t  Quantity ordered: ");
                    validation = scanf("%d", &userinput);
                  }
                }

                item[i].stock = item[i].stock - userinput;

                if (item[i].stock == 0)
                {
                  printf("\t\t\t\t  |                                                        |\n");
                  printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT HAS FALLEN TO 0 =]                 \n");
                  printf("\t\t\t\t  |                                                        |\n");
                }

                // strcpy(item[c].receipt, item[i].itemname);
                // item[c].receiptprice = item[i].price * userinput;
                // c++;

                item[i].daily_sold = item[i].daily_sold + userinput;
                item[i].item_total = item[i].item_total + (item[i].price * userinput);
                item[0].daily_owed = item[0].daily_owed + (item[i].price * userinput);

                subtotal = subtotal + (item[i].price * userinput);
                printf("\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t   Current Subtotal: %.2f\n", subtotal);
                printf("\n\t\t\t\t  |[CLICK ENTER]:");
                getch();
              }
              else
              {
                printf("\t\t\t\t  |                                                        |\n");
                printf("\t\t\t\t   This item will not be added to the order list.\n");
                printf("\n\t\t\t\t  |[CLICK ENTER]:");
                getch();
              }
            }
            else if (item[i].stock == 0)
            {
              printf("\t\t\t\t  |                                                        |\n");
              printf("\t\t\t\t\t  [= ITEM STOCK AMOUNT IS 0 =]                 \n");
              printf("\t\t\t\t  |                                                        |\n");
              printf("\n\t\t\t\t  |[CLICK ENTER]:");
              getch();
            }
          }
          else
          {
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t\t  [= ITEM NUMBER NOT FOUND =]                 \n");
            printf("\t\t\t\t  |                                                        |\n");
            printf("\t\t\t\t  |[CLICK ENTER]:");
            getch();
          }

          system("cls");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                           SALES                                         |\n");
          printf("\t\t |=========================================================================================|\n");
          printf("\t\t |                                                                                         |\n");

          printf("\t\t\t\t  |                                                        |\n");
          printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
          validation = scanf("%d", &userinput);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
            validation = scanf("%d", &userinput);
          }
          while ((userinput != 1) && (userinput != 2))
          {
            printf("\t\t\t\t\t   [= INVALID OPTION =]\n");
            printf("\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
            validation = scanf("%d", &userinput);
            while (validation != 1)
            {
              printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
              scanf("%*[^\n]");
              printf("\n\t\t\t\t  |[CLICK ENTER]:");
              getch();
              printf("\n\t\t\t\t   Add another item? (Enter 1 for YES and 2 for NO): ");
              validation = scanf("%d", &userinput);
            }
          }
        } while (userinput == 1);

        money_owed = subtotal;

        
        strcpy(clientInfo[c].client_name, name);        
        strcpy(clientInfo[c].client_phone,  client_phone);
        clientInfo[c].money_owed = money_owed;
        c++;
        

        // printf("%s", clientInfo[f].client_name);
        // getch();

        // push(clientInfo, top1, money_owed, name, client_phone);
        // top1++;
        writer(clientInfo, c);

      break;
    case 2:    
      // printf("\t\t\t\t  |                                                        |\n");
      // printlist(clientInfo, c);
      // scanf("%*[^\n]");
      // printf("\n\t\t\t\t  |[CLICK ENTER]:");
      // getch();

      if (c == 0){
        printf("\t\t\t\t\t   [=CLIENT LIST EMPTY=]\n");
        scanf("%*[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();
        
      }else{
        printf("\t\t\t  |                                                                             |\n");
        printf("\t\t\t  |\t  Name  \t |\t Phone Number \t\t|\t Amount Owed \t|\n");

        // for(int g = 0; g < c; g++){
        //   printf("\t\t\t  |\t %s \t |\t %s \t|\t $%.2f \t| \n", clientInfo[g].client_name, clientInfo[g].client_phone, clientInfo[g].money_owed);
        // }
        int g = 0;
        while (g < c)
        {
           printf("\t\t\t  |\t %s \t |\t %s \t|\t $%.2f \t| \n", clientInfo[g].client_name, clientInfo[g].client_phone, clientInfo[g].money_owed);
            g++;
        }
        
        printf("\t\t\t\t  |=====================================================|\n");
      }
      scanf("%*[^\n]");
      printf("\n\t\t\t\t  |[CLICK ENTER]:");
      getch();
      writer(clientInfo, c);
      break;

    case 3:
      // printf("\t\t\t\t  |                                                        |\n");
      // int l = printlist(clientInfo, c);
      if(c == 0){
        printf("\t\t\t\t\t   [=CLIENT LIST EMPTY=]\n");
        scanf("%*[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        return;
      }else{
        int g = 0;
        while (g < c)
        {
           printf("\t\t\t  |\t %s \t |\t %s \t\t|\t $%.2f \t\t| \n", clientInfo[g].client_name, clientInfo[g].client_phone, clientInfo[g].money_owed);
            g++;
        }
      }
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t   Name:  ");
      scanf("%c", &temp);
      // scanf("%[^\n]", name);
      scanf("%s", name);

      found = 0;
      i = 0;
      while(found == 0 && i<c){
        if(!strcmp(clientInfo[i].client_name, name)){
          found = 1;
        }else{
          // pop(clientInfo, clientInfo2, top1, top2);
          // top1--;
          // top2++;
          i++;
        }
      }

      if (found == 1)
      {
        printf("\t\t\t\t   Amount Owed: %.2f \n", clientInfo[i].money_owed);
        printf("\t\t\t\t   Payment:  ");
        validation = scanf("%lf", &payment);
        while (validation != 1)
        {
          printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
          scanf("%*[^\n]");
          printf("\t\t\t\t  Payment Received: ");
          validation = scanf("%lf", &payment);
        }
        while (payment < clientInfo[i].money_owed)
        {
          printf("\t\t\t\t\t [= INSUFFICIENT AMOUNT ENTERED =] \n");
          printf("\t\t\t\t   ReEnter Payment Received:");
          validation = scanf("%lf", &payment);
          while (validation != 1)
          {
            printf("\t\t\t\t\t   [=Value entered is not a number=]\n");
            scanf("%*[^\n]");
            printf("\t\t\t\t  Payment Received: ");
            validation = scanf("%lf", &payment);
          }
        }

        change = payment - clientInfo[i].money_owed;
        printf("\t\t\t\t   Change: $ %.2f", change);
        scanf("%*[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();


        // pop2(clientInfo, top1);
        // top1--;

        // for(i = 0; i <top2; i++){
        //   pop3(clientInfo, clientInfo2, top1, top2);
        // }
        // top1 = top1 + top2;
        for (int j = i - 1; j < c; j++)
        {
          clientInfo[j].money_owed = clientInfo[j + 1].money_owed;
          strcpy(clientInfo[j].client_name, clientInfo[j + 1].client_name);
          strcpy(clientInfo[j].client_phone, clientInfo[j + 1].client_phone);
        }
        c--;
      }
      else
      {
        printf("\t\t\t\t   [= CLIENT NOT FOUND =]  ");
        scanf("%*[^\n]");
        printf("\n\t\t\t\t  |[CLICK ENTER]:");
        getch();
      }   
      writer(clientInfo, c);   
      break;
    default:
      printf("\t\t\t\t  |                                                        |\n");
      printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
      printf("\n\t\t\t\t  |[CLICK ENTER]:");
      getch();
      writer(clientInfo, c);
      break;
    
    }
    break;
  default:
    printf("\t\t\t\t  |                                                        |\n");
    printf("\t\t\t\t\t   [=INVALID OPTION ENTERED=]\n");
    printf("\n\t\t\t\t  |[CLICK ENTER]:");
    getch();
    break;
  }
 
}

//This function prints the receipt for the user with values given by the calculation function. 
void receipt(struct items item[], double change, double payment, double subtotal, int num1)
{
  int i;
  system("cls");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                        OVERSTOCK SHOP                                   |\n");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                                                                         |\n");
  printf("\t\t\t\t  |========================================================|\n");
  for (i = 0; i < num1; i++)
  {
    printf("\t\t\t\t   %s \t\t\t %.2f\n", item[i].receipt, item[i].receiptprice);
  }
  printf("\t\t\t\t   Subtotal: \t\t\t %.2f\n", subtotal);
  printf("\t\t\t\t   Payment: \t\t\t %.2f\n", payment);
  printf("\t\t\t\t   Change: \t\t\t %.2f\n", change);
  printf("\t\t\t\t  |                                                        |\n");
  printf("\n\t\t\t\t  |[CLICK ENTER]: ");
  getch();
}

//This function prints a report of the day's earning and each product sales- which includes the amount that is sold and the cost of that amount. 
void daysfinal(struct items item[], int num1){
  char date[10], temp;

  system("cls");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                           REPORT                                        |\n");
  printf("\t\t |=========================================================================================|\n");
  printf("\t\t |                                                                                         |\n");
  printf("\t\t\t\t  Please enter the date (mm/dd/yyyy): ");
  // scanf("%c", &temp);
  scanf("%s", date);

   FILE *dpointer = fopen("OVERSTOCK-SHOP-DAYSFINAL.txt", "a+");
   
   fprintf(dpointer, "Date: %s \n |                                                                                         |\n", date);
   
   for(int i = 0; i< num1; i++){
    fprintf(dpointer, "Item-name: %s \n", item[i].itemname);
    fprintf(dpointer, "Total Sold: %d \n", item[i].daily_sold);
    fprintf(dpointer, "Item Total: $%.2f \n|                                                                                         |\n", item[i].item_total);
    
   }
   fprintf(dpointer, "Daily Owed Total: $%.2f \n", item[0].daily_owed);
   fprintf(dpointer, "Daily-total: $%.2f \n|===================================================================|\n ", item[0].daily_total);
                                           

   fclose(dpointer);

   for(int i = 0; i < num1; i++){
    printf("\t\t\t\t  Item-name: %s \n", item[i].itemname);
    printf("\t\t\t\t  Total Sold: %d \n", item[i].daily_sold);
    printf("\t\t\t\t  Item Total: $%.2f \n", item[i].item_total);
    printf("\t\t\t\t  |                                                                  |\n");
   }
   printf("\t\t\t\t  Daily Owed Total: $%.2f \n", item[0].daily_owed);
   printf("\t\t\t\t  Daily Total: $%.2f \n  ", item[0].daily_total);
   printf("\t\t\t\t  |===================================================================|\n");
   
}
