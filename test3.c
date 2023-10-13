#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Structures.c"

int Next_ID(){
    struct course course;
    FILE *file3 = fopen("course.txt", "a+");
    if (file3 == NULL) {
        perror("File opening failed");
        exit(1);
    }
    int highestNumericId1 = 0;

    while (fscanf(file3, "Faculty_id: %s\n", course.faculty_id) == 1) {
        // Read and discard the other information
        fscanf(file3, "ID: %d\n", &course.id);
        //printf("%d\n",course.id);
        if (course.id > highestNumericId1) {
            highestNumericId1 = course.id;
        }

        fscanf(file3, "Name: %s\n", course.name);
        fscanf(file3, "Faculty_name: %s\n", course.faculty_name);
        fscanf(file3, "Maximum Seats: %d\n", &course.seats);
        fscanf(file3, "Course Code: %s\n", course.code);
    }
    return highestNumericId1+1;
}

int main() {
    int a = Next_ID();
    printf("%d\n",a);
}

