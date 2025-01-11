#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char title[50];
    char descrp[400];
    char date[30];
    int status;
    char category[30];
    float amount;
} record;

void manage_section(char section);
void show_menu();
void add_new(char section);
void edit(char section);
void delete_entry(char section);
void search(char section);
void view(char section);

int main() {
    printf("---------------- Welcome to Personal Diary ----------------\n");
    while (1) {
        printf(" \"Home Page\"\n");
        printf("[1] Memory Management\n");
        printf("[2] Tasks Management\n");
        printf("[3] Expenditure Management\n");
        printf("[4] Exit\n");
        printf("Enter your option: ");
        int opt;
        if (scanf("%d", &opt) != 1) { // Input validation
            printf("Invalid input. Please enter a number.\n\n");
            while (getchar() != '\n');
            continue;
        }
        switch (opt) {
            case 1: manage_section('m'); 
			        break;
            case 2: manage_section('t');
			        break;
            case 3: manage_section('e'); 
			        break;
            case 4: printf("Exiting... Goodbye!\n");
			        return 0;
            default: printf("Invalid choice. Try again.\n\n");
        }
    }
}
// Function to manage a specific section (Memory, Tasks, or Expenditure)
void manage_section(char section) {
    const char *section_name = (section == 'm') ? "Memories" : (section == 't') ? "Tasks" : "Expenditure";
    printf("---Welcome to %s Section---\n", section_name);
    while (1) {
        show_menu();
        printf("Enter your option: ");
        int opt;
        if (scanf("%d", &opt) != 1) { // Input validation
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear input buffer
        continue;
        }
        switch (opt) {
            case 1: add_new(section); 
			        break;
            case 2: edit(section); 
			        break;
            case 3: delete_entry(section); 
		            break;
            case 4: search(section); 
			        break;
			case 5: view(section);
			        break;
            case 6: printf("Returning to Home Page...\n\n");
			        return;
            default: printf("Invalid choice. Try again.\n\n");
        }
    }
}
// Display menu for a section
void show_menu() {
    printf("\nWhich function do you want to perform?\n");
    printf("[1] Add New Record\n");
    printf("[2] Edit Existing Record\n");
    printf("[3] Delete Existing Record\n");
    printf("[4] Search for a Record\n");
    printf("[5] View All Records\n");
    printf("[6] Exit to Home Page\n");
}

// Function to add a new record to the specified section (memory, tasks, expenditure)
void add_new(char ch) {
    record r;
    getchar();  
    printf("Enter Title: ");
    fgets(r.title, sizeof(r.title), stdin);
    r.title[strcspn(r.title, "\n")] = '\0';

    printf("Enter Description: ");
    fgets(r.descrp, sizeof(r.descrp), stdin);
    r.descrp[strcspn(r.descrp, "\n")] = '\0';

    printf("Enter Date: ");
    fgets(r.date, sizeof(r.date), stdin);
    r.date[strcspn(r.date, "\n")] = '\0'; 

    FILE *p = NULL;

    if (ch == 'm') {  // Memory section
        p = fopen("memory.bin", "ab");
        if (p != NULL) {
            fwrite(&r, sizeof(r), 1, p);
            fclose(p);
            printf("Memory Added Successfully\n");
        } else {
            printf("Failed to open memory file\n");
        }
    } 
    else if (ch == 't') {  // Task section
        printf("Enter Task Status (0 for pending, 1 for completed): ");
        scanf("%d", &r.status); 
        getchar();  // 

        p = fopen("task.bin", "ab");
        if (p != NULL) {
            fwrite(&r, sizeof(r), 1, p);
            fclose(p);
            printf("Task Added Successfully\n");
        } else {
            printf("Failed to open task file\n");
        }
    }
    else if (ch == 'e') {  // Expense section
        printf("Enter Category: ");
        fgets(r.category, sizeof(r.category), stdin);  
        r.category[strcspn(r.category, "\n")] = '\0';

        printf("Enter Amount: ");
        scanf("%f", &r.amount);
        p = fopen("expense.bin", "ab");
        if (p != NULL) {
            fwrite(&r, sizeof(r), 1, p);
            fclose(p);
            printf("Expense Added Successfully\n");
        } else {
            printf("Failed to open expense file\n");
        }
    }
    else {
        printf("Invalid section identifier\n");
    }
}


// Function to edit an existing record in the specified section
void edit(char ch) {
	record r;
    FILE *p = NULL;
    char title[50];
    int found = 0; 
    getchar(); 
    printf("Enter title for edit record: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; 
    if (ch == 'm') {
        record m;
        record *tem = (record *)malloc(sizeof(record)); // Allocate memory for temp structure
        if (tem == NULL) {
            perror("Memory allocation failed");
            return;
        }
        p = fopen("memory.bin", "rb+"); // Open in read/write mode
        if (p == NULL) {
            perror("Error opening memory file");
            free(tem);
            return;
        }
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) == 0) {
                printf("Record found! Enter new details:\n");
                printf("New Title: ");
                fgets(tem->title, sizeof(tem->title), stdin);
                tem->title[strcspn(tem->title, "\n")] = '\0';
                printf("New Date: ");
                fgets(tem->date, sizeof(tem->date), stdin);
                tem->date[strcspn(tem->date, "\n")] = '\0';
                printf("New Description: ");
                fgets(tem->descrp, sizeof(tem->descrp), stdin);
                tem->descrp[strcspn(tem->descrp, "\n")] = '\0';

                // Move file pointer back to the record's position and update
                fseek(p, -(long int)sizeof(r), SEEK_CUR);
                fwrite(tem, sizeof(*tem), 1, p);
                found = 1;
                printf("Record updated successfully.\n");
                break;
            }
        }
        if (!found)
            printf("Record not found.\n");
            fclose(p);
            free(tem);
    }
    // Task section (t)
    else if (ch == 't') {
        record *tem = (record *)malloc(sizeof(record));
        if (tem == NULL) {
            perror("Memory allocation failed");
            return;
        }
        p = fopen("task.bin", "rb+");
        if (p == NULL) {
            perror("Error opening task file");
            free(tem);
            return;
        }
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) == 0) {
                printf("Record found! Enter new details:\n");
                printf("New Title: ");
                fgets(tem->title, sizeof(tem->title), stdin);
                tem->title[strcspn(tem->title, "\n")] = '\0';
                printf("New Date: ");
                fgets(tem->date, sizeof(tem->date), stdin);
                tem->date[strcspn(tem->date, "\n")] = '\0';
                printf("New Description: ");
                fgets(tem->descrp, sizeof(tem->descrp), stdin);
                tem->descrp[strcspn(tem->descrp, "\n")] = '\0';
                printf("New Status: ");
                scanf("%d",&tem->status);
//                getchar();
                fseek(p, -(long int)sizeof(r), SEEK_CUR);
                fwrite(tem, sizeof(*tem), 1, p);
                found = 1;
                printf("Record updated successfully.\n");
                break;
            }
        }
        if (!found)
            printf("Record not found.\n");
            fclose(p);
            free(tem);
    }
    // Expense section (e)
    else if (ch == 'e') {
        record *tem = (record *)malloc(sizeof(record));
        if (tem == NULL) {
            perror("Memory allocation failed");
            return;
        }
        p = fopen("expense.bin", "rb+");
        if (p == NULL) {
            perror("Error opening expense file");
            free(tem);
            return;
        }
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) == 0) {
                printf("Record found! Enter new details:\n");
                printf("New Title: ");
                fgets(tem->title, sizeof(tem->title), stdin);
                tem->title[strcspn(tem->title, "\n")] = '\0';
                printf("New Date: ");
                fgets(tem->date, sizeof(tem->date), stdin);
                tem->date[strcspn(tem->date, "\n")] = '\0';
                printf("New Description: ");
                fgets(tem->descrp, sizeof(tem->descrp), stdin);
                tem->descrp[strcspn(tem->descrp, "\n")] = '\0';
                printf("New Category: ");
                fgets(tem->category, sizeof(tem->category), stdin);
                tem->category[strcspn(tem->category, "\n")] = '\0';
                printf("New Amount: ");
                scanf("%f",&tem->amount);
                
                fseek(p, -(long int)sizeof(r), SEEK_CUR);
                fwrite(tem, sizeof(*tem), 1, p);
                found = 1;
                printf("Record updated successfully.\n");
                break;
            }
        }
        if (!found)
            printf("Record not found.\n");
            fclose(p);
            free(tem);
    }else
        printf("Invalid section identifier\n");
}


// Function to delete a record from the specified section
// DELETE FUNCTION:
void delete_entry(char section){
    char filename[20], temp_filename[25], title[50];
    FILE *p, *temp;
    record r;

    // Set filenames based on section
    if (section == 'm') {
        strcpy(filename, "memory.bin");
        strcpy(temp_filename, "temp_memory.bin");
    } else if (section == 't') {
        strcpy(filename, "task.bin");
        strcpy(temp_filename, "temp_task.bin");
    } else if (section == 'e') {
        strcpy(filename, "expense.bin");
        strcpy(temp_filename, "temp_expense.bin");
    } else {
        printf("Invalid section.\n");
        return;
    }

    // Open the files
    p = fopen(filename, "rb");
    temp = fopen(temp_filename, "wb");

    if (p == NULL || temp == NULL) {
        perror("Error opening file");
        return;
    }
    getchar(); // Clear input buffer
    printf("Enter the title to delete: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove newline

    int found = 0;

    // Read and write based on section
    if (section == 'm') {
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) != 0)
                fwrite(&r, sizeof(r), 1, temp);
            else
                found = 1;
        }
    } else if (section == 't') {
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) != 0) 
                fwrite(&r, sizeof(r), 1, temp);
            else 
                found = 1; 
        }
    } else if (section == 'e') {
        while (fread(&r, sizeof(r), 1, p) == 1) {
            if (strcmp(r.title, title) != 0)
                fwrite(&r, sizeof(r), 1, temp);
            else 
                found = 1;
        }
    }
    fclose(p);
    fclose(temp);
    // Replace old file with temp file if entry was found
    if (found == 1) {
        remove(filename);
        rename(temp_filename, filename);
        printf("Entry deleted successfully.\n");
    } else {
        remove(temp_filename);
        printf("Entry not found.\n");
    }
}

// Function to search for a record in the specified section

void search(char ch) {
	record r;
    FILE *p = NULL;
    if (ch == 'm') {  // Memory section
        char tit[50];
        printf("Enter Title to search: ");
        getchar();  
        fgets(tit, sizeof(tit), stdin);
        tit[strcspn(tit, "\n")] = '\0'; 
        p = fopen("memory.bin", "rb");
        if (p != NULL) {
            int found = 0;
            while (fread(&r, sizeof(r), 1, p))  {
                if (strcmp(r.title, tit) == 0) {
                    printf("Title : %s\n", r.title);
                    printf("Date : %s\n", r.date);
                    printf("Description: %s\n", r.descrp);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Memory with the given title not found.\n");
                fclose(p);
        }   else 
                printf("Failed to open memory file\n");
    }
    else if (ch == 't') {  // Task section
        int option; 
        printf("\n[1] Search by Status\n");
        printf("[2] Search by Title\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        getchar(); 
        if (option == 2) {  // Search by title
            char tit[50];
            printf("Enter Title to search: ");
            fgets(tit, sizeof(tit), stdin);
            tit[strcspn(tit, "\n")] = '\0'; 
            p = fopen("task.bin", "rb");
            if (p != NULL) {
                int found = 0;
                while (fread(&r, sizeof(r), 1, p)) {
                    if (strcmp(r.title, tit) == 0) {
                        printf("Title : %s\n", r.title);
                        printf("Date : %s\n", r.date);
                        printf("Description: %s\n", r.descrp);
                        printf("Status : %d\n", r.status);
                        found = 1;
                        break;
                    }
                }
                if (!found) 
                    printf("Task with the given title not found.\n");
                    fclose(p);
            }   else
                    printf("Failed to open task file\n");
        }
        else if (option == 1) {  // Search by status
            int st;
            printf("\nEnter: \n[1] for Completed tasks\n[0] for Pending tasks: ");
            scanf("%d", &st);
            p = fopen("task.bin", "rb");
            if (p != NULL) {
                int found = 0;
                while (fread(&r, sizeof(r), 1, p)) {
                    if (r.status == st) {
                        printf("Title : %s\n", r.title);
                        printf("Date : %s\n", r.date);
                        printf("Description: %s\n", r.descrp);
                        printf("Status : %d\n", r.status);
                        found = 1;
                    }
                }
                if (!found) 
                    printf("No tasks found with the given status.\n");
                    fclose(p);
            }else 
                printf("Failed to open task file\n");
        }else 
            printf("Invalid option selected.\n");
    }
    else if (ch == 'e') {  // Expense section
        char tit[50];
        printf("Enter Title to search: ");
        getchar(); 
        fgets(tit, sizeof(tit), stdin);
        tit[strcspn(tit, "\n")] = '\0';  
        p = fopen("expense.bin", "rb");
        if (p != NULL) {
            int found = 0;
            while (fread(&r, sizeof(r), 1, p)) {
                if (strcmp(r.title, tit) == 0) {
                    printf("Title : %s\n", r.title);
                    printf("Date : %s\n", r.date);
                    printf("Description: %s\n", r.descrp);
                    printf("Category: %s\n", r.category);
                    printf("Amount: %.2f\n", r.amount);
                    found = 1;
                    break;
                }
            }
            if (!found) 
                printf("Expense with the given title not found.\n");
                fclose(p);
        } else
            printf("Failed to open expense file\n");
    }
    else
        printf("Invalid section identifier\n");
}
// View All:
void view(char section)
{
	FILE *p;
	record r;
	if(section == 'm')
	{
		int i=1;
		p = fopen("memory.bin", "rb");
		while(fread(&r, sizeof(r),1,p) == 1){
			printf("Record %d: \n",i);
			i++;
			printf("Title : %s\n", r.title);
            printf("Date : %s\n", r.date);
            printf("Description: %s\n\n", r.descrp);
		}printf("Record Ended\n");
	}
	else if(section == 't')
	{
		int i=1;
		p = fopen("task.bin", "rb");
		while(fread(&r, sizeof(r),1,p) == 1){
			printf("Record %d: \n",i);
			i++;
			printf("Title : %s\n", r.title);
            printf("Date : %s\n", r.date);
            printf("Description: %s\n", r.descrp);
            printf("Status : %d\n\n", r.status);
		}printf("Record Ended\n");
	}
	else if(section == 'e'){
		int i=1;
		p = fopen("expense.bin", "rb");
		while(fread(&r, sizeof(r),1,p) == 1){
			printf("Record %d: \n",i);
			i++;
			printf("Title : %s\n", r.title);
            printf("Date : %s\n", r.date);
            printf("Description: %s\n", r.descrp);
            printf("Amount : %f\n", r.amount);
            printf("Category: %s\n\n",r.category);
		}printf("Record Ended\n");
	}
	fclose(p);
}