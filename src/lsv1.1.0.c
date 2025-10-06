#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For exit, etc.
#include <dirent.h>     // For opendir, readdir
#include <sys/stat.h>   // For stat, struct stat
#include <pwd.h>        // For getpwuid
#include <grp.h>        // For getgrgid
#include <time.h>       // For time and date functions

// Function to show file type and permissions
void show_permissions(mode_t m) {
    // Show file type
    if (S_ISDIR(m)) {
        printf("d");   // Directory
    } else if (S_ISLNK(m)) {
        printf("l");   // Symbolic link
    } else if (S_ISCHR(m)) {
        printf("c");   // Character device
    } else if (S_ISBLK(m)) {
        printf("b");   // Block device
    } else if (S_ISFIFO(m)) {
        printf("p");   // Named pipe
    } else if (S_ISSOCK(m)) {
        printf("s");   // Socket
    } else {
        printf("-");   // Regular file
    }

    // Owner (user) permissions
    if (m & S_IRUSR) printf("r"); else printf("-");
    if (m & S_IWUSR) printf("w"); else printf("-");
    if (m & S_IXUSR) printf("x"); else printf("-");

    // Group permissions
    if (m & S_IRGRP) printf("r"); else printf("-");
    if (m & S_IWGRP) printf("w"); else printf("-");
    if (m & S_IXGRP) printf("x"); else printf("-");

    // Others permissions
    if (m & S_IROTH) printf("r"); else printf("-");
    if (m & S_IWOTH) printf("w"); else printf("-");
    if (m & S_IXOTH) printf("x"); else printf("-");
}

int main() {
    DIR *dir;                   // Directory pointer
    struct dirent *entry;       // Each file entry
    struct stat info;           // File information

    dir = opendir(".");         // Open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Read each file in the directory one by one
    while ((entry = readdir(dir)) != NULL) {

        // Get information about the file
        if (lstat(entry->d_name, &info) == -1) { // use lstat to handle links properly
            perror("stat failed");
            continue;
        }

        // Get user and group info
        struct passwd *user = getpwuid(info.st_uid);
        struct group  *grp  = getgrgid(info.st_gid);

        // Get last modified time
        char time_str[30];
        struct tm *timeinfo = localtime(&info.st_mtime);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

        // Print permissions and link count
        show_permissions(info.st_mode);
        printf(" %ld ", info.st_nlink);

        // Print user name (owner)
        if (user != NULL) {
            printf("%s ", user->pw_name);
        } else {
            printf("unknown ");
        }

        // Print group name
        if (grp != NULL) {
            printf("%s ", grp->gr_name);
        } else {
            printf("unknown ");
        }

        // Print file size
        printf("%5ld ", info.st_size);

        // Print time and file name
        printf("%s ", time_str);
        printf("%s\n", entry->d_name);
    }

    closedir(dir);  // Close directory
    return 0;
}




