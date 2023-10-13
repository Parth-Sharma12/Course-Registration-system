#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Structures.c"
#include <fcntl.h>

int searchFacultyByID(char *ID,char *password,int br) {
        int file = open("faculty.txt", O_RDONLY);
        
        struct Faculty facultyinfo;
        int found = 0; // Flag to check if the student was found
        while (read(file,&facultyinfo,sizeof(struct Faculty))) { // Read ID and check if successfull
        int ver[2];
        if (strcmp(facultyinfo.id,ID)==0) {
        // Student found, print their information
            if(strcmp(facultyinfo.password,password)==0){
                br = 23;
                break;
            }
        }
    }
    return br;
}
int main() {
    int fileDescriptor = open("course.txt", O_RDONLY);
    if (fileDescriptor == -1) {
        perror("File opening failed");
        return 1;
    }
    /*char buffer[20];
    strcpy(buffer,"2");
    int id=atoi(buffer);*/
    struct course course;
    ssize_t bytesRead;
   // int offset=(id-1)*sizeof(struct student);
    //int seekinfo=lseek(fileDescriptor,offset,SEEK_SET);
    // while ((bytesRead = read(fileDescriptor, &student_data, sizeof(struct student))) > 0) {
    //     // Process the data from the struct
    //     printf("ID: %s\n", student_data.id);
    //     printf("Name: %s\n", student_data.name);
    //     printf("Password: %s\n", student_data.password);
    //     printf("Email: %s\n", student_data.email);
    //     printf("Address: %s\n", student_data.address);
    // }
    int i=0;
    while(i<=1){
        i++;
        read(fileDescriptor,&course,sizeof(struct course));
        //strcpy(course.name,"ALGORITHMS");
        printf("course:%d\n",course.id);
        printf("course_name:%s\n",course.name);
        printf("faculty:%s\n",course.faculty_name);
        printf("seats:%d\n",course.seats);
        printf("Code:%s\n",course.code);
    }
    close(fileDescriptor);
    //int br =0;
    //br = searchFacultyByID("iiitb@2","murli@123",br);
   // printf("br = %d\n",br);
    return 0;
}
