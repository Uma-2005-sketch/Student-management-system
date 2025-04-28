#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5

// Function prototypes
void student_details();
void read_details();
void calc_avg();
void print_avg();
int *bin_search(int, int *);

// Global variables
int i, n;

struct student {
    char name_of_the_student[50];
    int regno;
    int ENG, MATHS, COMP_PRG;
    int total;
    float avg;
};

struct student st[MAX_STUDENTS];

struct details {
    int op, low, high, mid;
} dt;  // Declare dt as global variable

struct contt {
    char cont;
};

int main() {
    student_details();
    return 0;
}

void student_details() {
    int rollno[MAX_STUDENTS];
    int *ptr = rollno;

    printf("********* name:UMA SHANKAR REDDY ***********\n");
    printf("********* Reg no:2262265 **************\n");
    printf("********* class & sec:1BTCHE-2B **********\n");
    printf("********** Subject:COMPUTER PROGRAMMING(mini project) *************\n");
    printf("########## CHRIST UNIVERSITY ##############\n");
    printf("################### STUDENT ADMISSIONS MANAGEMENT ##################\n");
    printf("Enter the no.of students (max %d): ", MAX_STUDENTS);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students. Please enter between 1 and %d.\n", MAX_STUDENTS);
        return;
    }

    struct contt ct;
    struct contt *ptrct = &ct;

    do {
        printf("\nEnter the option\n1. Read Details\n2. Calculate Marks\n3. Print Details\n4. Binary Search\n5. Exit\n");
        scanf("%d", &dt.op);

        switch (dt.op) {
            case 1:
                read_details();
                for (i = 0; i < n; i++) {
                    rollno[i] = st[i].regno;
                }
                break;
            case 2:
                printf("\nTOTAL AND AVERAGE MARKS OF THE STUDENTS\n");
                calc_avg();
                break;
            case 3:
                printf("\n...........Print Student Details........\n");
                printf("Studentname\tRegno\tENG\tMATHS\tCOMP_PRG\tTotal\tAverage\tGrade\n");
                print_avg();
                break;
            case 4: {
                int search;
                printf("\nEnter the registration number to be searched: ");
                scanf("%d", &search);
                int *bin_result = bin_search(search, rollno);
                if (bin_result != NULL) {
                    printf("Student found with Regno: %d\n", *bin_result);
                }
                break;
            }
            case 5:
                printf("Exiting program...\n");
                ptrct->cont = 'n';
                break;
            default:
                printf("Invalid option. Please choose between 1-5.\n");
                break;
        }
        
        if (dt.op != 5) {
            printf("\nChoose another option? (y/n): ");
            scanf(" %c", &ptrct->cont);
        }
    } while (ptrct->cont == 'y' || ptrct->cont == 'Y');
}

void read_details() {
    FILE *fp;
    fp = fopen("student_records.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i+1);
        printf("Enter the name of the student: ");
        scanf("%s", st[i].name_of_the_student);
        printf("Enter the student Regno: ");
        scanf("%d", &st[i].regno);
        printf("Enter the marks in ENG (out of 100): ");
        scanf("%d", &st[i].ENG);
        printf("Enter the marks in MATHS (out of 100): ");
        scanf("%d", &st[i].MATHS);
        printf("Enter the marks in COMP_PRG (out of 100): ");
        scanf("%d", &st[i].COMP_PRG);
        
        if (st[i].ENG < 0 || st[i].ENG > 100 || 
            st[i].MATHS < 0 || st[i].MATHS > 100 || 
            st[i].COMP_PRG < 0 || st[i].COMP_PRG > 100) {
            printf("Invalid marks! Marks should be between 0-100.\n");
            i--;
            continue;
        }
    }

    fprintf(fp, "STUDENT ADMISSIONS MANAGEMENT\n");
    for (i = 0; i < n; i++) {
        fprintf(fp, "\nName: %s\tRegno: %d\tENG: %d\tMATHS: %d\tCOMP_PRG: %d",
                st[i].name_of_the_student, st[i].regno, st[i].ENG, st[i].MATHS, st[i].COMP_PRG);
    }

    printf("\nData written to file successfully\n");
    fclose(fp);
}

void calc_avg() {
    FILE *fp;
    fp = fopen("student_records.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "\n\nCalculated Marks:\n");
    for (i = 0; i < n; i++) {
        st[i].total = st[i].ENG + st[i].MATHS + st[i].COMP_PRG;
        st[i].avg = (float) st[i].total / 3;
        fprintf(fp, "Name: %s\tTotal: %d\tAverage: %.2f\n", 
                st[i].name_of_the_student, st[i].total, st[i].avg);
    }

    printf("Average calculations written to file successfully\n");
    fclose(fp);
}

void print_avg() {
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%.2f\t", 
               st[i].name_of_the_student, st[i].regno, 
               st[i].ENG, st[i].MATHS, st[i].COMP_PRG, st[i].total, st[i].avg);

        if (st[i].avg >= 50 && st[i].avg <= 60)
            printf("Grade: E (Passed - Try Harder)\n");
        else if (st[i].avg > 60 && st[i].avg <= 70)
            printf("Grade: D (Passed - Satisfactory)\n");
        else if (st[i].avg > 70 && st[i].avg <= 80)
            printf("Grade: C (Passed - Good)\n");
        else if (st[i].avg > 80 && st[i].avg <= 90)
            printf("Grade: B (Passed - Very Good)\n");
        else if (st[i].avg > 90 && st[i].avg <= 100)
            printf("Grade: A (Passed - Excellent)\n");
        else
            printf("Grade: F (Failed - Better luck next time)\n");
    }
}

int *bin_search(int search, int *ptr) {
    dt.low = 0;
    dt.high = n - 1;
    int j, k;  // Declare loop variables before loops (C89 compatible)

    // Bubble sort
    for (j = 0; j < n-1; j++) {
        for (k = 0; k < n-j-1; k++) {
            if (ptr[k] > ptr[k+1]) {
                int temp = ptr[k];
                ptr[k] = ptr[k+1];
                ptr[k+1] = temp;
            }
        }
    }

    while (dt.low <= dt.high) {
        dt.mid = (dt.low + dt.high) / 2;

        if (ptr[dt.mid] < search)
            dt.low = dt.mid + 1;
        else if (ptr[dt.mid] == search) {
            printf("%d found at position %d\n", search, dt.mid);
            return &ptr[dt.mid];
        } else
            dt.high = dt.mid - 1;
    }

    printf("%d isn't present in the list\n", search);
    printf("*** Project successfully completed ****\n");
    printf("************ THANK YOU *************\n");
    return NULL;
}
