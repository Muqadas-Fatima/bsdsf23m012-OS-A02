#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Define color codes (ANSI escape sequences)
#define COLOR_RESET  "\033[0m"
#define COLOR_DIR    "\033[1;34m"   // blue
#define COLOR_EXEC   "\033[1;32m"   // green
#define COLOR_ARCH   "\033[1;31m"   // red
#define COLOR_LINK   "\033[1;35m"   // pink (magenta)
#define COLOR_SPEC   "\033[7m"      // reverse video

// Function to detect if file is an archive
int is_archive(const char *name) {
    const char *ext[] = {".tar", ".gz", ".zip", ".tgz", ".bz2", ".xz"};
    for (int i = 0; i < 6; i++) {
        if (strstr(name, ext[i])) {
            return 1;  // found a matching extension
        }
    }
    return 0;
}

// Function to choose color based on file type
const char* get_color(const char *name, struct stat info) {
    if (S_ISDIR(info.st_mode)) {
        return COLOR_DIR;       // Directory
    } else if (S_ISLNK(info.st_mode)) {
        return COLOR_LINK;      // Symbolic link
    } else if (S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode) ||
               S_ISSOCK(info.st_mode) || S_ISFIFO(info.st_mode)) {
        return COLOR_SPEC;      // Special files
    } else if (info.st_mode & S_IXUSR) {
        return COLOR_EXEC;      // Executable file
    } else if (is_archive(name)) {
        return COLOR_ARCH;      // Archive (by name)
    } else {
        return COLOR_RESET;     // Normal file
    }
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat info;

    dir = opendir(".");  // open current directory
    if (dir == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    // Step 1: Read all filenames
    char **files = NULL;
    int count = 0;
    int maxlen = 0;

    while ((entry = readdir(dir)) != NULL) {
        // skip hidden files (starting with .)
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

    // Step 2: Get terminal width to calculate columns
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    int col_width = maxlen + 2;
    int cols = width / col_width;
    if (cols < 1) cols = 1;
    int rows = (count + cols - 1) / cols;

    // Step 3: Print files in columns with color
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int i = c * rows + r;
            if (i < count) {
                // Get info about file
                if (lstat(files[i], &info) == -1)
                    continue;

                // Get color based on type
                const char *color = get_color(files[i], info);

                // Print with color
                printf("%s%-*s%s", color, col_width, files[i], COLOR_RESET);
            }
        }
        printf("\n");
    }

    // Step 4: Free memory
    for (int i = 0; i < count; i++)
        free(files[i]);
    free(files);

    return 0;
}
