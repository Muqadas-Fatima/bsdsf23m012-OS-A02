#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>   // for terminal size
#include <unistd.h>      // for STDOUT_FILENO

int main(int argc, char *argv[]) {
    int horizontal = 0;  // flag for -x mode

    // Check for -x flag
    if (argc > 1 && strcmp(argv[1], "-x") == 0) {
        horizontal = 1;
    }

    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Step 1: Read filenames
    char **files = NULL;
    int count = 0;
    int maxlen = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')  // skip hidden files
            continue;

        files = realloc(files, (count + 1) * sizeof(char *));
        files[count] = strdup(entry->d_name);

        int len = strlen(entry->d_name);
        if (len > maxlen)
            maxlen = len;

        count++;
    }
    closedir(dir);

    if (count == 0) {
        printf("No files found.\n");
        return 0;
    }

    // Step 2: Get terminal width
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    // Step 3: Calculate columns and rows
    int col_width = maxlen + 2;
    int cols = width / col_width;
    if (cols < 1) cols = 1;

    int rows = (count + cols - 1) / cols;

    // Step 4: Display files
    if (horizontal == 0) {
        // Default: down then across
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int i = c * rows + r;
                if (i < count)
                    printf("%-*s", col_width, files[i]);
            }
            printf("\n");
        }
    } else {
        // -x mode: left to right (across then down)
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int i = r * cols + c;
                if (i < count)
                    printf("%-*s", col_width, files[i]);
            }
            printf("\n");
        }
    }

    // Step 5: Free memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    free(files);

    return 0;
}



