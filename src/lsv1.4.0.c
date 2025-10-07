#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Simple compare function for qsort
int compare_strings(const void *a, const void *b) {
    // Convert the void pointers back to string pointers
    char *str1 = *(char **)a;
    char *str2 = *(char **)b;
    return strcmp(str1, str2);  // Compare strings alphabetically
}

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");   // Open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Step 1: Store file names
    char **files = NULL;
    int count = 0;
    int maxlen = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files (starting with '.')
        if (entry->d_name[0] == '.')
            continue;

        // Add to array
        files = realloc(files, (count + 1) * sizeof(char *));
        files[count] = strdup(entry->d_name);

        int len = strlen(entry->d_name);
        if (len > maxlen)
            maxlen = len;

        count++;
    }
    closedir(dir);

    // Step 2: If no files found
    if (count == 0) {
        printf("No files found.\n");
        return 0;
    }

    // Step 3: Sort filenames alphabetically
    qsort(files, count, sizeof(char *), compare_strings);

    // Step 4: Get terminal width
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    // Step 5: Calculate column layout
    int col_width = maxlen + 2;
    int cols = width / col_width;
    if (cols < 1) cols = 1;
    int rows = (count + cols - 1) / cols;

    // Step 6: Print in columns (down then across)
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i = c * rows + r;
            if (i < count)
                printf("%-*s", col_width, files[i]);
        }
        printf("\n");
    }

    // Step 7: Free memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    free(files);

    return 0;
}




