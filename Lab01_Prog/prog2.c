// Write a C program to assign values to each members of the following structure. Pass the populated structure to a function Using call-by-value and another function using call-by-address and print the value of each member of the structure.
// struct student_info{
//     int roll_no;
//     char name[50];
//     float CGPA;
//     struct dob age;
// }

// struct dob{
//     int date;
//     int month;
//     int year;
// };

#include <stdio.h>
#include <stdlib.h>

struct dob
{
    int day;
    int month;
    int year;
};

typedef struct dob dob;

struct student_info
{
    int roll;
    char name[50];
    float CGPA;
    dob age;
};

typedef struct student_info Student;

void valuePrint(Student s);
void refPrint(Student *s);

int main()
{
    Student s1;

    while (getchar() != '\n')
        ;

    printf("Enter student name: ");
    fgets(s1.name, 50, stdin);

    fflush(stdin);

    printf("Enter student roll: ");
    scanf("%d", &s1.roll);

    fflush(stdin);

    printf("Enter CGPA: ");
    scanf("%f", &s1.CGPA);

    printf("Enter dob: \n");

    printf("Enter day: ");
    scanf("%d", &s1.age.day); // check s1.day

    printf("Enter month: ");
    scanf("%d", &s1.age.month);

    printf("Enter year: ");
    scanf("%d", &s1.age.year);

    valuePrint(s1);
    refPrint(&s1);

    return 0;
}

void valuePrint(Student s)
{
    printf("Using value print \n");
    printf("Roll number: %d \n", s.roll);
    printf("Name: %s", s.name);
    printf("CGPA: %f \n", s.CGPA);
    printf("Age: Day = %d, Month = %d, Year = %d \n", s.age.day, s.age.month, s.age.year);
}

void refPrint(Student *s)
{
    printf("Using reference print \n");
    printf("Roll number: %d \n", s->roll);
    printf("Name: %s", s->name);
    printf("CGPA: %f \n", s->CGPA);
    printf("Age: Day = %d, Month = %d, Year = %d \n", s->age.day, s->age.month, s->age.year);
}