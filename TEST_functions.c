#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Structures.c"
//#include "newserver.c"

void searchFacultyByID(int ID) {
                struct Faculty faculty;
                FILE *file = fopen("faculty.txt", "r");
                if (file == NULL) {
                    perror("File opening failed");
                    return;
                }

                int found = 0; // Flag to check if the student was found
                while (fscanf(file, "ID: %10d\n", &faculty.id) == 1) { // Read ID and check if successful
                fscanf(file, "Name: %49s\n", faculty.name);
                fscanf(file, "Department: %49s\n", faculty.department);
                fscanf(file, "Email: %49s\n", faculty.email);
                fscanf(file, "Address: %99s\n", faculty.address);
                fscanf(file, "Designation: %49s\n", faculty.designation);
                fscanf(file, "login_id: %49s\n", faculty.login_id);

                if (faculty.id== ID) {
                // Student found, print their information
                    
                    printf("ID: %d\n", faculty.id);
                    printf("Name: %s\n", faculty.name);
                    printf("Email: %s\n", faculty.email);
                    printf("Address: %s\n", faculty.address);

                    found = 1;
                    break; // Stop searching
                }
                }

                if (!found) {
                printf("Faculty with ID '%d' not found.\n", ID);
            }

        fclose(file);
    }
 int main(){
    searchFacultyByID(123);
 }