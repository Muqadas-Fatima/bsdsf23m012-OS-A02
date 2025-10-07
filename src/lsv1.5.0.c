#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Color codes
#define COLOR_RESET  "\033[0m"
#define COLOR_DIR    "\033[1;34m"   // blue
#define COLOR_EXEC   "\033[1;32m"   // green
#define COLOR_LINK   "\033[1;36m"   // cyan
#define COLOR_FILE   "\033[0m"      // default color

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat info;

    dir = opendir(".");   // open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Step 1: read all file names
    char **files = NULL;
    int count = 0;
    int maxlen = 0;

    while ((entry = readdir(dir)) != NULL) {
        // skip hidden files (starting with '.')
        if (entry->d_name[0] == '.')
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

    // Step 2: get terminal width for columns
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    int col_width = maxlen + 2;
    int cols = width / col_width;
    if (cols < 1) cols = 1;
    int rows = (count + cols - 1) / cols;

    // Step 3: print files in color (down then across)
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i = c * rows + r;
            if (i < count) {
                // get file info to check type
                if (stat(files[i], &info) == -1) {
                    perror("stat");
                    continue;
                }

                // choose color based on file type
                if (S_ISDIR(info.st_mode))
                    printf(COLOR_DIR);
                else if (S_ISLNK(info.st_mode))
                    printf(COLOR_LINK);
                else if (info.st_mode & S_IXUSR)
                    printf(COLOR_EXEC);
                else
                    printf(COLOR_FILE);

                // print filename
                printf("%-*s", col_width, files[i]);

                // reset color
                printf(COLOR_RESET);
            }
        }
        printf("\n");
    }

    // Step 4: free memory
    for (int i = 0; i < count; i++)
        free(files[i]);
    free(files);

    return 0;
}
