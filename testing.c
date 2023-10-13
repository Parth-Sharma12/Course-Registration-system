#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<string.h>
#include "Structures.c"

int main() {
    // Initialize position to -1
    char targetFacultyID[20]; // Faculty ID to search for
    printf("Enter the Faculty ID to update: ");
    scanf("%s", targetFacultyID);
    long position = -1;
    struct course course;
    // Open the file in read mode to read its contents
    FILE *file = fopen("course.txt", "r");
    int fd = fileno(file);
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Find the record with the matching Faculty_id
    while (fscanf(file, "Faculty_id: %s\n", course.faculty_id) != EOF) {
        // Read other fields
        fscanf(file, "ID: %d\n", &course.id);
        fscanf(file, "Name: %s\n", course.name);
        fscanf(file, "Faculty_name: %s\n", course.faculty_name);
        fscanf(file, "Maximum Seats: %d\n", &course.seats);
        fscanf(file, "Course Code: %s\n", course.code);

        // Check if the Faculty_id matches the target
        if (strcmp(course.faculty_id, targetFacultyID) == 0) {
            position = ftell(file) - (sizeof("Faculty_id: ") + strlen(course.faculty_id) + 1);
            break;
        }
    }

    fclose(file);

// Rest of the code (lock, update, etc.)

    // ... Previous code for finding the record


    // Open the file again in write mode to update the record
    file = fopen("course.txt", "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Apply an exclusive lock to the record
    int fileDescriptor = fileno(file);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = position;
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct course);

    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("Error locking the file");
        fclose(file);
        return 1;
    }

    // Seek to the position of the record to update
    fseek(file, position, SEEK_SET);

    // Update the record (you can modify the course data as needed)
    // For example, updating the course name:
    fprintf(file, "Name: %s\n", "New Name");

    // Release the lock and close the file
    lock.l_type = F_UNLCK;
    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("Error releasing the lock");
    }   
    fclose(file);

    printf("Faculty ID %s updated.\n", targetFacultyID);

    return 0;

}

    

  