#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>   // for ioctl() and terminal size
#include <unistd.h>      // for STDOUT_FILENO

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Step 1: store file names in an array
    char **files = NULL;
    int count = 0;
    int maxlen = 0;   // store longest file name length

    while ((entry = readdir(dir)) != NULL) {
        // skip hidden files (starting with .)
        if (entry->d_name[0] == '.')
            continue;

        // add new file name to list
        files = realloc(files, (count + 1) * sizeof(char *));
        files[count] = strdup(entry->d_name);

        // check if it's the longest name
        int len = strlen(entry->d_name);
        if (len > maxlen)
            maxlen = len;

        count++;
    }
    closedir(dir);

    // Step 2: if no files found
    if (count == 0) {
        printf("No files found.\n");
        return 0;
    }

    // Step 3: find terminal width (how wide the screen is)
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    // Step 4: calculate how many columns fit on screen
    int col_width = maxlen + 2;   // add space between columns
    int cols = width / col_width;
    if (cols < 1) cols = 1;       // at least 1 column

    // Step 5: how many rows we need
    int rows = (count + cols - 1) / cols;

    // Step 6: print files "down then across"
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i = c * rows + r;   // find correct file index
            if (i < count)
                printf("%-*s", col_width, files[i]);
        }
        printf("\n");
    }

    // Step 7: free memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    free(files);

    return 0;
}






