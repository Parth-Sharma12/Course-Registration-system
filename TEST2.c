#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Structures.c"
int main()
{
    int targetID;
    printf("Enter the ID : ");
    scanf("%d", &targetID);

    int fd = open("course.txt", O_RDWR);
    struct course course;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = (targetID - 1) * sizeof(course);
    lock.l_len = sizeof(course);
    lock.l_whence = SEEK_SET;
    lock.l_pid = getpid();

    printf("Before entering the critical section:\n");
    sleep(1);
    fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (targetID- 1) * sizeof(course), SEEK_SET);
    read(fd, &course, sizeof(course));
    printf("Current seats: %d\n", course.seats);

    lock.l_type = F_WRLCK;
    course.seats++;
    lseek(fd, -1 * sizeof(course), SEEK_CUR);
    write(fd, &course, sizeof(course));
    sleep(1);
    printf("Updated seats: %d\n", course.seats);

    getchar();
    getchar();
    printf("Seats updated.\n");

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    return 0;
}