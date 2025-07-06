#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<setjmp.h>
#include<ctype.h>
#include<stdbool.h>

#define FILE_NAME "accounts.txt"
#define COMPLAINT_FILE "complaints.txt"
#define MAX_LEN 50
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"



typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
} Account;


typedef struct
{
    int complaint_id;
    char student_name[50];
    long int student_id;
    char department[50];
    int year_of_study;
    char email[50];
    char phone[15];
    char category[20];
    char description[200];
    int date_filed;
    char status[20];
    char assigned_authority[50];

} Complaint;


bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


bool isValidDate(int date) {

    int day = date / 1000000;
    int month = (date / 10000) % 100;
    int year = date % 10000;


    if ((year <= 2024) && (year >= 2025))
        return true;


    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    if (isLeapYear(year))
        daysInMonth[2] = 29;


    if ((month <= 1) || (month >= 12))
        return true;
    if ((day <= 1) || (day > daysInMonth[month]))
        return true;

    return false;
}




int addComplaint()
{
    char term ;
    int err = 0 ;
    Complaint complaint;
    FILE *file;


file = fopen("complaints.dat", "ab");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }


    while(1)
    {
        printf("Enter Complaint ID: ");




        if(scanf("%d%c", &complaint.complaint_id, &term) != 2 || term != '\n')
        {
           printf("Invalid input! Please enter a valid number.\n");
           while (getchar() != '\n');


        }
        else{ break;}
      }

      while(1)
      {
          err = 0;
          printf("Enter Student Name: ");

          fgets(complaint.student_name, sizeof(complaint.student_name), stdin);
          complaint.student_name[strcspn(complaint.student_name, "\n")] = 0;

          for(int i=0;complaint.student_name[i]!='\0';i++)
          {

              if((isalpha(complaint.student_name[i])==0))
              {
                  printf("Please Enter a Valid Name \n");
                  err = 1;
                  break;
              }


          }
          if(err!=1){break;}


      }


      while(1)
    {
        printf("Enter Student ID: ");

        if(scanf("%d%c", &complaint.student_id, &term) != 2 || term != '\n')
        {
           printf("Invalid input! Please enter a valid number.\n");
           while (getchar() != '\n');


        }
        else{ break;}
      }


    while(1)
    {
        printf("Enter Department [ Computer Science , Information Technology , Electronics and Communication]: ");

        fgets(complaint.department, sizeof(complaint.department), stdin);
        complaint.department[strcspn(complaint.department, "\n")] = 0; // Remove newline

        if((strcmp(strlwr(complaint.department),"computer science")==0)){break ;}
        else if((strcmp(strlwr(complaint.department),"information technology")==0)) {break;}
        else if((strcmp(strlwr(complaint.department),"electronics and communication")==0)) {break ;}



        else {
            printf("Invalid Input!, Please Enter the Correct Department from the options ! \n");
        }


    }

    while(1)
    {
        printf("Enter Year of Study [ 2010-2024: ");


        if(scanf("%d%c", &complaint.year_of_study, &term) != 2 || term != '\n')
        {
           printf("Invalid input! Please enter a valid number.\n");
           while (getchar() != '\n');


        }

        else{

            if((complaint.year_of_study>=2010)&&(complaint.year_of_study<=2024)){break;}

            else{
                printf("Invalid Year of study \n");
            }

        }
      }


    while(1)
    {
        printf("Enter Phone Number: ");
        fgets(complaint.phone, sizeof(complaint.phone), stdin);
        complaint.phone[strcspn(complaint.phone, "\n")] = 0;

        if((strlen(complaint.phone)==10))
        {

              for(int i=0;complaint.phone[i]!='\0';i++)
              {
                  err = 0;

                 if((isdigit(complaint.phone[i])==0))
                 {
                    printf("Please Enter a Valid Number \n");
                    err = 1;
                    break;
                 }
                 if(err!=1){break;}


                }
                break;
        }
        else{
            printf("Invalid Number \n ");
        }

  }

    while(1)
    {
        printf("Enter Complaint Category (Academic, Administrative ,Infrastructure:): ");
        fgets(complaint.category, sizeof(complaint.category), stdin);
        complaint.category[strcspn(complaint.category, "\n")] = 0;


        if((strcmp(strlwr(complaint.category),"academic")==0)){break ;}
        else if((strcmp(strlwr(complaint.category),"administrative")==0)) {break;}
        else if((strcmp(strlwr(complaint.category),"infrastructure")==0)) {break ;}



        else {
            printf("Invalid Input!, Please Enter the Correct Department from the options ! \n");
        }
    }

    printf("Enter Complaint Description: ");
    fgets(complaint.description, sizeof(complaint.description), stdin);
    complaint.description[strcspn(complaint.description, "\n")] = 0;

    while(1)
    {
        term = 1;

        printf("Enter Date Filed (ddmmyyyy): ");



        if(scanf("%8d%c", &complaint.date_filed, &term) != 2 || term != '\n')
        {
           printf("Invalid input! Please enter a valid date \n");
           while (getchar() != '\n');



        }
        else{
                if (complaint.date_filed) { break ;}

                else{
                      printf("Invalid Date \n");
                       }

                }

        }

    fwrite(&complaint, sizeof(Complaint), 1, file);
    printf("Complaint added successfully!\n");


    fclose(file);

    return 0;
}

void viewComplaints()
{
    Complaint complaint;
    FILE *file;


     file = fopen("complaints.dat", "rb");

        if (file == NULL)
       {
            printf("Error: No complaints found or file cannot be opened!\n");
            return;
        }


    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size == 0)
    {
        printf("No complaints to view.\n");
        fclose(file);
        return;
    }


    printf("\n--- All Complaints ---\n");
    while (fread(&complaint, sizeof(Complaint), 1, file))
    {
        printf("\nComplaint ID: %d\n", complaint.complaint_id);
        printf("Student Name: %s\n", complaint.student_name);
        printf("Student ID: %d\n", complaint.student_id);
        printf("Department: %s\n", complaint.department);
        printf("Year of Study: %d\n", complaint.year_of_study);
        printf("Phone Number: %s\n", complaint.phone);
        printf("Category: %s\n", complaint.category);
        printf("Description: %s\n", complaint.description);
        printf("Date Filed: %d\n", complaint.date_filed);

        printf("---------------------------------\n");
    }


    fclose(file);
}

void adminMenu() {
    int choice;

    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. View All Complaints\n");
        printf("2. Delete a Complain \n");
        printf("3. Generate Report \n");
        printf("4. EXIT \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewComplaints();

                break;


            case 2:
                deleteComplaint();
                break ;

            case 3 :
                generateReport();
                break ;


            case 4:
                printf("Logging out...\n");
                return;


            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}




void deleteComplaint()
{
    Complaint complaint;
    FILE *file, *tempFile;
    int complaint_id, found = 0;


    file = fopen("complaints.dat", "rb");

    if (file == NULL)
    {
        printf("Error: No complaints found or file cannot be opened!\n");
        return;
    }


    tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }


    printf("Enter the Complaint ID to delete: ");
    scanf("%d", &complaint_id);



    while (fread(&complaint, sizeof(Complaint), 1, file))
    {
        if (complaint.complaint_id == complaint_id)
        {
            found = 1;
            printf("Complaint ID %d deleted successfully!\n", complaint_id);
        }
        else
        {
            fwrite(&complaint, sizeof(Complaint), 1, tempFile); // Copy non-deleted complaints
        }
    }

    fclose(file);
    fclose(tempFile);


    remove("complaints.dat");

    rename("temp.dat", "complaints.dat");


    if (!found)
    {
        printf("Invalid request: Complaint ID %d not found!\n", complaint_id);
    }
}

void searchComplaint()
{
    Complaint complaint;
    FILE *file;
    int choice, search_id, found = 0;
    char search_category[20], search_status[20];


    file = fopen("complaints.dat", "rb");

    if (file == NULL)
    {
        printf("Error: No complaints found or file cannot be opened!\n");
        return;
    }


    printf("Search Complaint by:\n");
    printf("1. Complaint ID\n");
    printf("2. Student ID\n");


    printf("Enter your choice: ");
    scanf("%d", &choice);


    switch (choice)
    {
    case 1:

        printf("Enter Complaint ID: ");
         scanf("%d", &search_id);


        while (fread(&complaint, sizeof(Complaint), 1, file))
        {
            if (complaint.complaint_id == search_id)
            {
                found = 1;
                printf("\nComplaint ID: %d\n", complaint.complaint_id);
                printf("Student Name: %s\n", complaint.student_name);
                printf("Student ID: %d\n", complaint.student_id);
                printf("Department: %s\n", complaint.department);
                printf("Year of Study: %d\n", complaint.year_of_study);
                printf("Phone Number: %s\n", complaint.phone);
                printf("Category: %s\n", complaint.category);
                printf("Description: %s\n", complaint.description);
                printf("Date Filed: %d\n", complaint.date_filed);

                break;
            }
        }
        break;

    case 2:

        printf("Enter Student ID: ");
        scanf("%d", &search_id);


        while (fread(&complaint, sizeof(Complaint), 1, file))
        {
            if (complaint.student_id == search_id)
            {
                found = 1;
                printf("\nComplaint ID: %d\n", complaint.complaint_id);
                printf("Student Name: %s\n", complaint.student_name);
                printf("Department: %s\n", complaint.department);
                printf("Year of Study: %d\n", complaint.year_of_study);
                printf("Category: %s\n", complaint.category);
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        break;

    case 3:

        printf("Enter Complaint Category: ");
        getchar();
        fgets(search_category, sizeof(search_category), stdin);
        search_category[strcspn(search_category, "\n")] = 0;
        while (fread(&complaint, sizeof(Complaint), 1, file))
        {
            if (strcmp(complaint.category, search_category) == 0)
            {
                found = 1;
                printf("\nComplaint ID: %d\n", complaint.complaint_id);
                printf("Student Name: %s\n", complaint.student_name);
                printf("Category: %s\n", complaint.category);

                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        break;

    case 4:

        printf("Enter Complaint Status (Pending, Resolved): ");
        getchar();
        fgets(search_status, sizeof(search_status), stdin);
        search_status[strcspn(search_status, "\n")] = 0;
        while (fread(&complaint, sizeof(Complaint), 1, file))
        {
            if (strcmp(complaint.status, search_status) == 0)
            {
                found = 1;
                printf("\nComplaint ID: %d\n", complaint.complaint_id);
                printf("Student Name: %s\n", complaint.student_name);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        break;

    default:
        printf("Invalid choice.\n");
    }

    if (!found)
    {
        printf("No complaints found matching the search criteria.\n");
    }


    fclose(file);
}



void generateReport()
{
    Complaint complaint;
    FILE *file;
    int choice;
    int academic_count = 0, admin_count = 0, infra_count = 0;
    int pending_count = 0, resolved_count = 0;
    int cs_count = 0, it_count = 0, ece_count = 0;


file = fopen("complaints.dat", "rb");

    if (file == NULL)
    {
        printf("Error: No complaints found or file cannot be opened!\n");
        return;
    }


    printf("Generate Report by:\n");
    printf("1. Complaints by Category\n");
    printf("2. Complaints by Department\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);



    while (fread(&complaint, sizeof(Complaint), 1, file))
    {

        if (strcmp(complaint.category, "Academic") == 0)
            academic_count++;
        else if (strcmp(complaint.category, "Administrative") == 0)
            admin_count++;
        else if (strcmp(complaint.category, "Infrastructure") == 0)
            infra_count++;

        if (strcmp(complaint.department, "Computer Science") == 0)
            cs_count++;
        else if (strcmp(complaint.department, "Information Technology") == 0)
            it_count++;
        else if (strcmp(complaint.department, "Electronics and Communication") == 0)
            ece_count++;

       resolved_count++;
    }


    fclose(file);


    switch (choice)
    {
    case 1:
        printf("\n--- Complaints by Category ---\n");
        printf("Academic: %d\n", academic_count);
        printf("Administrative: %d\n", admin_count);
        printf("Infrastructure: %d\n", infra_count);
        break;

    case 2:
        printf("\n--- Complaints by Department ---\n");
        printf("Computer Science: %d\n", cs_count);
        printf("Information Technology: %d\n", it_count);
        printf("Electronics and Communication: %d\n", ece_count);
        break;

    case 3:
        printf("\n--- Status Report ---\n");
        printf("Pending: %d\n", pending_count);
        printf("Resolved: %d\n", resolved_count);
        break;

    default:
        printf("Invalid choice.\n");
    }
}

void displayMenu()
{
    printf("\n University Complaint Management System \n");
    printf("1. Add Complaint \n");
    //printf("2. Modify Complaint \n");
    printf("2. Search Complaint \n");
    printf("3. Exit\n");
    printf("Enter your choice: \n\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}



char currentUser[MAX_LEN] = "";


void createAccount();
int login();
void editPassword();
void complaintManagementSystem();




void createAccount() {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file for account creation!\n");
        return;
    }

    Account account;
    printf("Enter a new username: ");
    scanf("%s", account.username);

    printf("Enter a new password: ");
    scanf("%s", account.password);

    fprintf(file, "%s %s\n", account.username, account.password);
    fclose(file);
    printf("Account created successfully!\n");
}

int login() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No accounts exist. Please create an account first.\n");
        return 0;
    }

    char username[MAX_LEN], password[MAX_LEN];
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {


        printf("Admin login successful!\n");
        adminMenu();
        return 0;
    }

    Account account;
    while (fscanf(file, "%s %s", account.username, account.password) != EOF) {
        if (strcmp(account.username, username) == 0 && strcmp(account.password, password) == 0) {
            fclose(file);
            strcpy(currentUser, username);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password.\n");
    return 0;
}

void editPassword() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No accounts exist. Please create an account first.\n");
        return;
    }

    char username[MAX_LEN], oldPassword[MAX_LEN], newPassword[MAX_LEN];
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your current password: ");
    scanf("%s", oldPassword);

    Account accounts[100];
    int count = 0, found = 0;

    while (fscanf(file, "%s %s", accounts[count].username, accounts[count].password) != EOF) {
        if (strcmp(accounts[count].username, username) == 0 && strcmp(accounts[count].password, oldPassword) == 0) {
            printf("Enter your new password: ");
            scanf("%s", newPassword);
            strcpy(accounts[count].password, newPassword);
            found = 1;
        }
        count++;
    }

    fclose(file);

    if (!found) {
        printf("Account not found or incorrect password.\n");
        return;
    }

    file = fopen(FILE_NAME, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s\n", accounts[i].username, accounts[i].password);
    }
    fclose(file);

    printf("Password updated successfully!\n");
}


void complaintManagementSystem()
{
    int choice;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);


        switch (choice)
        {
        case 1:
            addComplaint();
            break;



        case 2:
            searchComplaint();
            break;
        case 3:
            printf("Exiting the system.\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }



}


int main() {
    int choice;

    do {


        printf("\n--- Main Menu ---\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Edit Password\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                if (login()) {
                    complaintManagementSystem();
                }

                break;
            case 3:
                editPassword();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }


    } while (choice != 4);

    return 0;
}

