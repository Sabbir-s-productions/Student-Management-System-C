#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getGrade(float gpa);

void header()
{
    printf("========================================\n");
    printf("      STUDENT MANAGEMENT SYSTEM\n");
    printf("========================================\n");
}

typedef struct
{
    int id;
    char name[100];
    int age;
    float gpa;
} Student;

int isDuplicateID(int id);



void addStudent()
{
    

    FILE *fp = fopen("students.dat", "ab");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }


    Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    if(isDuplicateID(s.id))
    {
        printf("Student with this ID already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    do
{
    printf("Enter Age: ");
    scanf("%d", &s.age);

    if(s.age <= 0 || s.age > 120)
        printf("Invalid Age!\n");

} while(s.age <= 0 || s.age > 120);

    printf("Enter Age: ");
    scanf("%d", &s.age);

  do
{
    printf("Enter GPA (0.00 - 4.00): ");
    scanf("%f", &s.gpa);

    if(s.gpa < 0 || s.gpa > 4)
        printf("Invalid GPA!\n");

} while(s.gpa < 0 || s.gpa > 4);

    fwrite(&s, sizeof(Student), 1, fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void viewStudents()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student s;

    int count = 0;

    printf("\n===== ALL STUDENTS =====\n");

    while(fread(&s, sizeof(Student), 1, fp))
    {
        count++;

        printf("\nStudent %d\n", count);
        printf("\nID   : %d\n", s.id);
        printf("Name : %s\n", s.name);
        printf("Age  : %d\n", s.age);
        printf("GPA  : %.2f\n", s.gpa);
        printf("Grade: %s\n", getGrade(s.gpa));
        printf("------------------------\n");
        
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student s;
    int searchID;
    int found = 0;

    printf("Enter Student ID: ");
    scanf("%d", &searchID);

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.id == searchID)
        {
            printf("\nStudent Found!\n");
            printf("ID   : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("Age  : %d\n", s.age);
            printf("GPA  : %.2f\n", s.gpa);
            printf("Grade: %s\n", getGrade(s.gpa));
            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

void updateStudent()
{
    FILE *fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student s;
    int searchID;
    int found = 0;

    printf("Enter Student ID to Update: ");
    scanf("%d", &searchID);

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.id == searchID)
        {
            found = 1;

            printf("\nNew Name: ");
            scanf(" %[^\n]", s.name);

            printf("New Age: ");
            scanf("%d", &s.age);

            printf("New GPA: ");
            scanf("%f", &s.gpa);

            fseek(fp, -sizeof(Student), SEEK_CUR);

            fwrite(&s, sizeof(Student), 1, fp);

            printf("\nStudent Updated Successfully!\n");

            break;
        }
    }

    if(found == 0)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

void deleteStudent()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");

    Student s;
    int searchID;
    int found = 0;

    printf("Enter Student ID to Delete: ");
    scanf("%d", &searchID);

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.id == searchID)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
    {
        printf("\nStudent Deleted Successfully!\n");
    }
    else
    {
        printf("\nStudent Not Found!\n");
    }
}

void statistics()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student s;

    int totalStudents = 0;
    float totalGPA = 0;
    float highestGPA = -1;
    float lowestGPA = 999;

    char highestName[100];
    char lowestName[100];

    while(fread(&s, sizeof(Student), 1, fp))
    {
        totalStudents++;
        totalGPA += s.gpa;

        if(s.gpa > highestGPA)
        {
            highestGPA = s.gpa;
            strcpy(highestName, s.name);
        }

        if(s.gpa < lowestGPA)
        {
            lowestGPA = s.gpa;
            strcpy(lowestName, s.name);
        }
    }

    fclose(fp);

    if(totalStudents == 0)
    {
        printf("No Student Records!\n");
        return;
    }

    printf("\n========== STATISTICS ==========\n");
    printf("Total Students : %d\n", totalStudents);
    printf("Average GPA    : %.2f\n", totalGPA / totalStudents);
    printf("Highest GPA    : %.2f (%s)\n", highestGPA, highestName);
    printf("Lowest GPA     : %.2f (%s)\n", lowestGPA, lowestName);
    printf("================================\n");
}
void gpaRanking()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student students[1000];
    int n = 0;

    while(fread(&students[n], sizeof(Student), 1, fp))
    {
        n++;
    }

    fclose(fp);

    if(n == 0)
    {
        printf("No Student Records!\n");
        return;
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(students[i].gpa < students[j].gpa)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n========== GPA RANKING ==========\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d. %s | GPA: %.2f | Grade: %s\n",
       i + 1,
       students[i].name,
       students[i].gpa,
       getGrade(students[i].gpa));
    }

    printf("=================================\n");
}

void sortByID()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student students[1000];
    int n = 0;

    while(fread(&students[n], sizeof(Student), 1, fp))
    {
        n++;
    }

    fclose(fp);

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(students[i].id > students[j].id)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n===== STUDENTS SORTED BY ID =====\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d | %s | GPA: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].gpa);
    }
}

void exportCSV()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    FILE *csv = fopen("students.csv", "w");

    Student s;

    fprintf(csv, "ID,Name,Age,GPA\n");

    while(fread(&s, sizeof(Student), 1, fp))
    {
        fprintf(csv,
                "%d,%s,%d,%.2f\n",
                s.id,
                s.name,
                s.age,
                s.gpa);
    }

    fclose(fp);
    fclose(csv);

    printf("students.csv created successfully!\n");
}

void createDefaultPassword()
{
    FILE *fp = fopen("password.dat", "rb");

    if(fp == NULL)
    {
        fp = fopen("password.dat", "wb");

        char password[50] = "admin123";

        fwrite(password, sizeof(password), 1, fp);
    }

    fclose(fp);
}

void login()
{
    char password[50];

    while(1)
    {
        printf("\n========== LOGIN ==========\n");
        printf("Enter Admin Password: ");
        scanf("%s", password);

        if(strcmp(password, "admin123") == 0)
        {
            printf("\nLogin Successful!\n");
            break;
        }
        else
        {
            printf("Wrong Password! Try Again.\n");
        }
    }
}

int isDuplicateID(int id)
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
        return 0;

    Student s;

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.id == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void searchByName()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    char name[100];
    int found = 0;
    Student s;

    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(strcmp(s.name, name) == 0)
        {
            printf("\nID   : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("Age  : %d\n", s.age);
            printf("GPA  : %.2f\n", s.gpa);
            printf("Grade: %s\n", getGrade(s.gpa));

            found = 1;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void reportCard()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    int searchID;
    int found = 0;
    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &searchID);

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.id == searchID)
        {
            found = 1;

            printf("\n==================================\n");
            printf("        STUDENT REPORT CARD\n");
            printf("==================================\n");

            printf("ID      : %d\n", s.id);
            printf("Name    : %s\n", s.name);
            printf("Age     : %d\n", s.age);
            printf("GPA     : %.2f\n", s.gpa);
            printf("Grade   : %s\n", getGrade(s.gpa));

            if(s.gpa >= 2.00)
                printf("Status  : PASS\n");
            else
                printf("Status  : FAIL\n");

            printf("==================================\n");

            break;
        }
    }

    if(!found)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

void top5Students()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student students[1000];
    int n = 0;

    while(fread(&students[n], sizeof(Student), 1, fp))
    {
        n++;
    }

    fclose(fp);

    if(n == 0)
    {
        printf("No Student Records!\n");
        return;
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(students[i].gpa < students[j].gpa)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n===== TOP 5 STUDENTS =====\n");

    int limit = (n < 5) ? n : 5;

    for(int i = 0; i < limit; i++)
    {
        printf("%d. %s | GPA: %.2f\n",
               i + 1,
               students[i].name,
               students[i].gpa);
    }
}

void failedStudents()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student s;
    int found = 0;

    printf("\n===== FAILED STUDENTS =====\n");

    while(fread(&s, sizeof(Student), 1, fp))
    {
        if(s.gpa < 2.00)
        {
            printf("\nID   : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("GPA  : %.2f\n", s.gpa);
            printf("----------------------\n");

            found = 1;
        }
    }

    if(!found)
    {
        printf("No Failed Students Found!\n");
    }

    fclose(fp);
}

void sortByGPAHigh()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student students[1000];
    int n = 0;

    while(fread(&students[n], sizeof(Student), 1, fp))
    {
        n++;
    }

    fclose(fp);

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(students[i].gpa < students[j].gpa)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n===== GPA HIGH TO LOW =====\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d | %s | GPA: %.2f | Grade: %s\n",
               students[i].id,
               students[i].name,
               students[i].gpa);
    }
}

void sortByGPALow()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No Data Found!\n");
        return;
    }

    Student students[1000];
    int n = 0;

    while(fread(&students[n], sizeof(Student), 1, fp))
    {
        n++;
    }

    fclose(fp);

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(students[i].gpa > students[j].gpa)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n===== GPA LOW TO HIGH =====\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d | %s | GPA: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].gpa);
    }
}
char* getGrade(float gpa)
{
    if(gpa >= 4.00)
        return "A+";
    else if(gpa >= 3.75)
        return "A";
    else if(gpa >= 3.50)
        return "A-";
    else if(gpa >= 3.00)
        return "B";
    else if(gpa >= 2.50)
        return "C";
    else if(gpa >= 2.00)
        return "D";
    else
        return "F";
}
void dashboard()
{
    
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\n====================================\n");
        printf("      STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("No Student Records Found!\n");
        printf("====================================\n");
        return;
    }

    Student s;

    int totalStudents = 0;
    int failedStudents = 0;

    float totalGPA = 0;
    float highestGPA = -1;

    while(fread(&s, sizeof(Student), 1, fp))
    {
        totalStudents++;

        totalGPA += s.gpa;

        if(s.gpa > highestGPA)
        {
            highestGPA = s.gpa;
        }

        if(s.gpa < 2.00)
        {
            failedStudents++;
        }
    }

    fclose(fp);

    printf("\n====================================\n");
    printf("      STUDENT MANAGEMENT SYSTEM\n");
    printf("====================================\n");

    printf("Total Students : %d\n", totalStudents);

    if(totalStudents > 0)
    {
        printf("Average GPA    : %.2f\n",
               totalGPA / totalStudents);

        printf("Highest GPA    : %.2f\n",
               highestGPA);
    }

    printf("Failed Student : %d\n",
           failedStudents);

    printf("====================================\n");
}

void changePassword()
{
    char oldPass[50];
    char savedPass[50];
    char newPass[50];

    FILE *fp = fopen("password.dat", "rb");

    fread(savedPass, sizeof(savedPass), 1, fp);

    fclose(fp);

    printf("Enter Old Password: ");
    scanf("%s", oldPass);

    if(strcmp(oldPass, savedPass) != 0)
    {
        printf("Incorrect Password!\n");
        return;
    }

    printf("Enter New Password: ");
    scanf("%s", newPass);

    fp = fopen("password.dat", "wb");

    fwrite(newPass, sizeof(newPass), 1, fp);

    fclose(fp);

    printf("Password Changed Successfully!\n");
}


int main()
{
    createDefaultPassword();
    login();
    dashboard();

    int choice;

    while(1)
    {
        header();
        printf("\n===== MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Statistics\n");
        printf("7. GPA Ranking\n");
        printf("8. Sort by ID\n");
        printf("9. Export to CSV\n");
        printf("10. Search by Name\n");
        printf("11. Change Password\n");
        printf("12. Top 5 Students\n");
        printf("13. Failed Students\n");
        printf("14. Sort by GPA (Low to High)\n");
        printf("15. Sort by GPA (High to Low)\n");
        printf("16. Student Report Card\n");
        printf("17. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            addStudent();
        }
        else if(choice == 2)
        {
            viewStudents();
        }
        else if(choice == 3)
        {
            searchStudent();
        }
        else if(choice == 4)
        {
            updateStudent();
        }
        else if(choice == 5)
        {
            deleteStudent();
        }
        else if(choice == 6)
        {
            statistics();
        }
        else if(choice == 7)
        {
            gpaRanking();
        }
        else if(choice == 8)
        {
            sortByID();
        }
        else if(choice == 9)
{
    exportCSV();
}
else if(choice == 10)
{
    searchByName();
}
else if(choice == 11)
{
    changePassword();
}
else if(choice == 12)
{
    top5Students();
}
else if(choice == 13)
{
    failedStudents();
}
else if(choice == 14)
{
    sortByGPALow();
}
else if(choice == 15)
{
    sortByGPAHigh();
}
else if(choice == 16)
{
    reportCard();
}
else if(choice == 17)
{
    printf("\n=================================\n");
printf("Thank You For Using SMS v2.0\n");
printf("Good Bye!\n");
printf("=================================\n");
    break;
}
else
{
    printf("Invalid Choice!\n");
}
    }

    return 0;
}
