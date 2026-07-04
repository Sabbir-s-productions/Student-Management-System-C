#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[100];
    int age;
    float gpa;
} Student;

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

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

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

    printf("\n===== ALL STUDENTS =====\n");

    while(fread(&s, sizeof(Student), 1, fp))
    {
        printf("\nID   : %d\n", s.id);
        printf("Name : %s\n", s.name);
        printf("Age  : %d\n", s.age);
        printf("GPA  : %.2f\n", s.gpa);
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
        printf("%d. %s | GPA: %.2f\n",
               i + 1,
               students[i].name,
               students[i].gpa);
    }

    printf("=================================\n");
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Statistics\n");
        printf("7. GPA Ranking\n");
        printf("8. Exit\n");

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
            printf("Good Bye!\n");
            break;
        }
        else{
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
