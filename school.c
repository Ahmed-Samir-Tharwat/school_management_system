#include <string.h>
#include "school.h"

/* Declarations of static functions start*/
static void GET_DATA(student_node *new_std);

static student_node *FIND_STUDENT(List *list_ptr, uint32 id);

static void swap(student_node *a, student_node *b);

static void bubble_sort(student_node **students_array, uint32 size);

static boolean is_valid_input(Data *student_data);
/* Declarations of static functions end*/

/*  function to initialize the Students list */
 void CREATE_LIST(List *list_ptr) {
    list_ptr->head = NULL;
    list_ptr->Size = 0;
}

/* Menu to make user select required operation */
void MAIN_MENU(List *list_ptr) {
    uint8 choose;
    boolean error_status;
    printf("Welcome!! There is our school system\n\n\n");

    /* Initialize the list at the beginning of the menu */
    while(choose!=7) {
    printf("Enter 1 to Add a new Student \n");
    printf("Enter 2 to delete a student \n");
    printf("Enter 3 to edit student data \n");
    printf("Enter 4 to update student score\n");
    printf("Enter 5 to rank students by Computer Science scores\n");
    printf("Enter 6 to Display Student List\n");
    printf("Enter 7 to Exit\n\n\n");

    /* Read the user's choice */
    scanf("%d", &choose);
    fflush(stdin);
    /* Use a switch statement to handle the chosen option*/
    switch (choose) {
        case 1: {
            /* Option 1: Add a new student */
            error_status = ADD_STUDENT(list_ptr);
            break;
        }

        case 2: {
            char *deleted_name = DELETE_STUDENT(list_ptr);
            if (deleted_name != NULL) {
                printf("Deleted student name: %s\n", deleted_name);
                free(deleted_name); // Free the allocated memory for the deleted_name
            }
            break;
        }

        case 3: {
            /* Option 3: Edit student data */
            EDIT_STUDENT_DATA(list_ptr);
            break;
        }

        case 4: {
            /* Option 4: Update student score */
            UPDATE_ALL_SCORES(list_ptr);
            break;
        }

        case 5: {
            /* Option 5: Rank students by Computer Science scores */
            RANK_STUDENTS(list_ptr);
            break;
        }

        case 6: {
            /* Option 6: Display the student list alphabetically */
            DISPLAY_STUDENT_LIST(list_ptr);
            break;
        }
        case 7: {
            /* Option 7: Exit the menu */
            printf("Thanks a lot\n");
            break;
        }
        default: {
            /* Invalid option */
            printf("Invalid choice. Please choose a valid option.\n");
            break;
    }

    }
        printf("**********************\n\n");
    }
}

/*Function to add a new student to students list*/
boolean ADD_STUDENT(List *list_ptr) {
    student_node *new_std = (student_node *) malloc(sizeof(student_node));
    if (new_std) {
        GET_DATA(new_std);
        /* Check if the ID already exists */
        if (FIND_STUDENT(list_ptr, new_std->student_data.id) != NULL) {
            printf("Student with ID %d already exists in the list. Cannot add duplicate ID\n", new_std->student_data.id);
            free(new_std);
            return 0;
        }

        new_std->next = list_ptr->head;
        list_ptr->head = new_std;
        list_ptr->Size++;
        return 1;
    }
     else {
        return 0;
    }
}

/* Function to get student data from the user */
static void GET_DATA(student_node *new_std) {
    printf("Please enter student name: ");
    gets(new_std->student_data.name);

    printf("Please enter student id: ");
    fflush(stdin);

    scanf("%d", &new_std->student_data.id);
    fflush(stdin);

    printf("Please enter student address: ");
    gets(new_std->student_data.address);
    fflush(stdin);

    printf("Please enter student phone number: ");
    gets(new_std->student_data.phone_num);
    fflush(stdin);

    printf("Please enter student birthday\n");
    printf("Day: ");
    scanf("%d", &new_std->student_data.birth_date.day);
    printf("Month: ");
    scanf("%d", &new_std->student_data.birth_date.month);
    printf("Year: ");
    scanf("%d", &new_std->student_data.birth_date.year);

    printf("Please enter student Computer Science mark: ");
    scanf("%d", &new_std->student_data.c_science_score);

}

/*Function to get the student using his id*/
static student_node *FIND_STUDENT(List *list_ptr, uint32 id) {
    student_node *current = list_ptr->head;
    while (current != NULL) {
        if (current->student_data.id == id) {
            return current;
            /* Return the student node if found */
        }
        current = (student_node *) current->next;
    }
    return NULL; /* Return NULL if the student is not found */
}

/*Function to delete a student*/
char *DELETE_STUDENT(List *list_ptr) {
    uint32 id;
    printf("Please enter the ID of the student to delete: ");
    scanf("%d", &id);

    student_node  *student_to_delete = FIND_STUDENT(list_ptr, id);
    if (student_to_delete != NULL) {
        if (list_ptr->head == student_to_delete) {
            /* If the student to delete is the head of the list */
            list_ptr->head = (student_node *) student_to_delete->next;
        }
        else {
            student_node *current = list_ptr->head;
            while (current != NULL && student_to_delete != (student_node *) current->next) {
                current = (student_node *) current->next;
            }
            if (current != NULL) {
                current->next = student_to_delete->next;
            }
        }
        char *deleted_name = strdup((char *) student_to_delete->student_data.name); /* Create a copy of the name */
        free(student_to_delete);
        list_ptr->Size--;
        printf("Student with ID %d deleted successfully.\n", id);
        return deleted_name;
    }
     else {
        printf("Student with ID %d not found in the list.\n", id);
        return NULL;
    }
}

    /*Function  to edit student data*/
void EDIT_STUDENT_DATA(List *list_ptr) {
    uint32 id;
    printf("Please enter the ID of the student to edit: ");
    scanf("%d", &id);
    fflush(stdin);
    student_node *student_to_edit = FIND_STUDENT(list_ptr, id);

    if (student_to_edit != NULL) {
        printf("Editing student with ID %d\n", id);
        printf("Enter new student name: ");
        gets(student_to_edit->student_data.name);
        fflush(stdin);

        printf("Enter new student address: ");
        gets(student_to_edit->student_data.address);
        fflush(stdin);

        printf("Enter new student phone number: ");
        gets(student_to_edit->student_data.phone_num);
        fflush(stdin);

        printf("Enter new student Computer Science mark: ");
        scanf("%i", &student_to_edit->student_data.c_science_scores);


        printf("Student data updated successfully.\n");
    }
    else {
        printf("Student with ID %d not found in the list.\n", id);
    }
}

/*Function to add the new students grades*/
void UPDATE_ALL_SCORES(List *list_ptr) {
    if (list_ptr->Size == 0) {
        printf("No students in the list.\n");
        return;
    }

    student_node *current = list_ptr->head;

    while (current != NULL) {
        printf("Enter new Computer Science score for student %s: ", current->student_data.name);
        scanf("%d", &current->student_data.c_science_score);
        fflush(stdin);

        current = current->next;
    }

    printf("All students' Computer Science scores have been updated successfully.\n");
}

/*Function to swap 2 student Data*/
static void swap(student_node *a, student_node *b) {
    Data temp = a->student_data;
    a->student_data = b->student_data;
    b->student_data = temp;
}

/*Function to rank student according to grades and Display top three */
void RANK_STUDENTS(List *list_ptr) {
    uint32 i;
    uint32 j;
    if (list_ptr->Size == 0) {
        printf("No students in the list.\n");
        return;
    }

    /* Create an array of pointers to student nodes to store addresses of students */
    student_node **students_array = (student_node **) malloc(list_ptr->Size * sizeof(student_node *));
    if (students_array == NULL) {
        printf("Memory allocation error.\n");
        return;
    }

    /*Fill the students_array with the addresses of the student nodes*/
    student_node *current = list_ptr->head;
    while (current != NULL) {
        students_array[i] = current;
        current = (student_node *)current->next;
        i++;
    }

    /* Perform  sort on the students_array based on Computer Science scores */
    for (i = 0; i < list_ptr->Size - 1; i++) {
        for ( j = 0; j < list_ptr->Size - i - 1; j++) {
            if (students_array[j]->student_data.c_science_score < students_array[j + 1]->student_data.c_science_score) {
                swap(students_array[j], students_array[j + 1]);
            }
        }
    }

    /*Display the students with the highest Computer Science scores*/
    printf("Students with the highest Computer Science scores:\n");
    for (i = 0; i < list_ptr->Size; i++) {
        printf("Name: %s, Computer Science Score: %d\n",
               students_array[i]->student_data.name,
               students_array[i]->student_data.c_science_score);
    }

    /*Free the dynamically allocated array*/
    free(students_array);
}

/*function to display students alphabetically*/
void DISPLAY_STUDENT_LIST(List *list_ptr) {
    if (list_ptr->Size == 0) {
        printf("No students in the list.\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-10s | %-30s | %-12s | %-12s | %-8s |\n", "No.", "Name", "ID", "Address", "Birth Date", "Phone Number", "CS Score");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    /* Create an array of pointers to student nodes to store addresses of students */
    student_node **students_array = (student_node **) malloc(list_ptr->Size * sizeof(student_node *));
    if (students_array == NULL) {
        printf("Memory allocation error.\n");
        return;
    }

    /*Fill the students_array with the addresses of the student nodes*/
    student_node *current = list_ptr->head;
    uint32 i = 0;
    while (current != NULL) {
        students_array[i] = current;
        current = (student_node *)current->next;
        i++;
    }

    /*Sort the students_array alphabetically based on student names*/
    bubble_sort(students_array, list_ptr->Size);

    // Display the sorted student list in tabular form
    for (i = 0; i < list_ptr->Size; i++) {
        Data student_data = students_array[i]->student_data;
        printf("| %-5d | %-20s | %-10ld | %-30s | %02d/%02d/%04d | %-12s | %-8d |\n",
               i + 1,
               student_data.name,
               student_data.id,
               student_data.address,
               student_data.birth_date.day,
               student_data.birth_date.month,
               student_data.birth_date.year,
               student_data.phone_num,
               student_data.c_science_score);
    }

    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    // Free the dynamically allocated array
    free(students_array);
}

/* Compare the student names and swap if needed */
static void bubble_sort(student_node **students_array, uint32 size) {
    uint32 i;
    uint32 j;

    for ( i = 0; i < size - 1; i++) {
        for ( j = 0; j < size - i - 1; j++) {
            if (strcmp(students_array[j]->student_data.name, students_array[j + 1]->student_data.name) > 0) {
                swap(students_array[j], students_array[j + 1]);
            }
        }
    }
}






