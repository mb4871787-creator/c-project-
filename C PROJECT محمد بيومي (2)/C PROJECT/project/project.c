

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NAME_LEN 64

/* Student structure */
struct student {
    int id;
    char name[NAME_LEN];
    int age;
    float gpa;
};

/* Linked list node */
struct node {
    struct student data;
    struct node *next;
};

/* Head pointer for the list */
static struct node *head = NULL;

/* Utility declarations */
static void flush_stdin(void);
static void addStudent(const struct student *const s);
static void displayStudents(void);
static struct node* findStudentNodeByID(int id);
static void searchStudentByID(int id);
static void updateStudent(int id);
static void deleteStudent(int id);
static float calculateAverageGPA(void);
static void searchHighestGPA(void);
static int idExists(int id);

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice = 0;
    int id;

    while (1) {
        printf("\n--- Student Management System ---");
        printf("1. Add a Student");
        printf("2. Display All Students");
        printf("3. Search for a Student by ID");
        printf("4. Update Student Information");
        printf("5. Delete a Student");
        printf("6. Calculate Average GPA");
        printf("7. Find Student with Highest GPA");
        printf("8. Exit");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            flush_stdin();
            continue;
        }

        switch (choice) {
            case 1: {
                struct student s;
                printf("Enter student ID: ");
                if (scanf("%d", &s.id) != 1) { printf("Invalid ID.\n"); flush_stdin(); break; }
                if (idExists(s.id)) { printf("Error: ID already exists.\n"); break; }
                flush_stdin();
                printf("Enter name: ");
                if (!fgets(s.name, NAME_LEN, stdin)) { strcpy(s.name, ""); }
                /* remove trailing newline */
                s.name[strcspn(s.name, "\n")] = '\0';
                printf("Enter age: ");
                if (scanf("%d", &s.age) != 1) { printf("Invalid age.\n"); flush_stdin(); break; }
                printf("Enter GPA: ");
                if (scanf("%f", &s.gpa) != 1) { printf("Invalid GPA.\n"); flush_stdin(); break; }
                addStudent(&s);
                break;
            }
            case 2:
                displayStudents();
                break;
            case 3:
                printf("Enter ID to search: ");
                if (scanf("%d", &id) != 1) { printf("Invalid ID.\n"); flush_stdin(); break; }
                searchStudentByID(id);
                break;
            case 4:
                printf("Enter ID to update: ");
                if (scanf("%d", &id) != 1) { printf("Invalid ID.\n"); flush_stdin(); break; }
                updateStudent(id);
                break;
            case 5:
                printf("Enter ID to delete: ");
                if (scanf("%d", &id) != 1) { printf("Invalid ID.\n"); flush_stdin(); break; }
                deleteStudent(id);
                break;
            case 6: {
                float avg = calculateAverageGPA();
                if (avg == 0.0f) printf("No students present.\n");
                else printf("Average GPA = %.2f\n", avg);
                break;
            }
            case 7:
                searchHighestGPA();
                break;
            case 8:
                /* free list before exit */
                while (head) {
                    struct node *tmp = head;
                    head = head->next;
                    free(tmp);
                }
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

/* ----------------- Utilities ----------------- */
static void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}

/* Check if ID already exists */
static int idExists(int id)
{
    struct node *cur = head;
    while (cur) {
        if (cur->data.id == id) return 1;
        cur = cur->next;
    }
    return 0;
}

/* Add a student to the end of the list */
static void addStudent(const struct student *const s)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    /* Development-time check */
    assert(newNode != NULL);
    /* Production-safe handling */
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        return;
    }

    newNode->data = *s; /* struct copy */
    newNode->next = NULL;

    if (!head) {
        head = newNode;
    } else {
        struct node *cur = head;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }

    printf("Student added successfully.\n");
}

/* Display all students */
static void displayStudents(void)
{
    if (!head) { printf("No students to display.\n"); return; }

    printf("\n--- Students List ---\n");
    struct node *cur = head;
    while (cur) {
        printf("ID: %d\n", cur->data.id);
        printf("Name: %s\n", cur->data.name);
        printf("Age: %d\n", cur->data.age);
        printf("GPA: %.2f\n", cur->data.gpa);
        puts("----------------------");
        cur = cur->next;
    }
}

/* Return node pointer by ID (or NULL) */
static struct node* findStudentNodeByID(int id)
{
    struct node *cur = head;
    while (cur) {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

/* Search and display */
static void searchStudentByID(int id)
{
    struct node *n = findStudentNodeByID(id);
    if (!n) { printf("Student with ID %d not found.\n", id); return; }
    printf("Student found:\n");
    printf("ID: %d\n", n->data.id);
    printf("Name: %s\n", n->data.name);
    printf("Age: %d\n", n->data.age);
    printf("GPA: %.2f\n", n->data.gpa);
}

/* Update student */
static void updateStudent(int id)
{
    struct node *n = findStudentNodeByID(id);
    if (!n) { printf("Student with ID %d not found.\n", id); return; }

    printf("Updating student with ID %d\n", id);
    flush_stdin();
    char buf[NAME_LEN];
    printf("Enter new name (leave empty to keep current): ");
    if (fgets(buf, NAME_LEN, stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (buf[0] != '\0') strncpy(n->data.name, buf, NAME_LEN-1);
        n->data.name[NAME_LEN-1] = '\0';
    }
    printf("Enter new age (0 to keep current %d): ", n->data.age);
    int age;
    if (scanf("%d", &age) == 1 && age > 0) n->data.age = age;
    printf("Enter new GPA (negative to keep current %.2f): ", n->data.gpa);
    float gpa;
    if (scanf("%f", &gpa) == 1 && gpa >= 0.0f) n->data.gpa = gpa;
    printf("Student updated.\n");
}

/* Delete student */
static void deleteStudent(int id)
{
    struct node *cur = head, *prev = NULL;
    while (cur) {
        if (cur->data.id == id) break;
        prev = cur;
        cur = cur->next;
    }
    if (!cur) { printf("Student with ID %d not found.\n", id); return; }

    if (!prev) {
        /* deleting head */
        head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
    printf("Student with ID %d deleted.\n", id);
}

/* Calculate average GPA */
static float calculateAverageGPA(void)
{
    if (!head) return 0.0f;
    int count = 0;
    float sum = 0.0f;
    struct node *cur = head;
    while (cur) {
        sum += cur->data.gpa;
        count++;
        cur = cur->next;
    }
    return (count > 0) ? (sum / count) : 0.0f;
}

/* Find student with highest GPA */
static void searchHighestGPA(void)
{
    if (!head) { printf("No students present.\n"); return; }
    struct node *cur = head;
    struct node *best = head;
    while (cur) {
        if (cur->data.gpa > best->data.gpa) best = cur;
        cur = cur->next;
    }
    printf("Student with highest GPA:\n");
    printf("ID: %d\n", best->data.id);
    printf("Name: %s\n", best->data.name);
    printf("Age: %d\n", best->data.age);
    printf("GPA: %.2f\n", best->data.gpa);
}
