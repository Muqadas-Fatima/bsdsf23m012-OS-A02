#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to list files recursively
void list_dir(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    char fullpath[1024];

    // Try to open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("Cannot open directory");
        return;
    }

    // Print current directory name
    printf("\n%s:\n", path);

    // Step 1: List all files in the current directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files and "." / ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s  ", entry->d_name);
    }
    printf("\n");

    // Step 2: Go through again and enter each subdirectory
    rewinddir(dir);  // reset to start
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." again
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Create full path (e.g., "./folder/subfolder")
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // Get file info
        if (stat(fullpath, &info) == -1)
            continue;

        // If it's a directory, call list_dir() again
        if (S_ISDIR(info.st_mode)) {
            list_dir(fullpath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *start_path = ".";  // Default: current directory

    // If user gave another path
    if (argc > 1) {
        start_path = argv[1];
    }

    // Start recursive listing
    list_dir(start_path);

    return 0;
}

