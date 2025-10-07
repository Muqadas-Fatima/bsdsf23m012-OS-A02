Absolutely! Here’s a **precise, ready-to-paste version** for your `REPORT.md` (or `README.md`) explaining both points clearly and concisely:

---

### **1. Difference between `stat()` and `lstat()`**

* `stat()` → returns info about the **target file**. Follows symbolic links.
* `lstat()` → returns info about the **link itself**. Does not follow symbolic links.
* **Use in `ls -l`**: `lstat()` is preferred so symbolic links are displayed correctly.

---

### **2. Using `st_mode` to get file type and permissions**

* `st_mode` contains **file type** and **permission bits**.
* **File type** (example):

```c
if (info.st_mode & S_IFDIR) { /* directory */ }
if (info.st_mode & S_IFREG) { /* regular file */ }
if (info.st_mode & S_IFLNK) { /* symbolic link */ }
```

* **Permissions** (user/group/others):

```c
if (info.st_mode & S_IRUSR) printf("r"); // user read
if (info.st_mode & S_IWUSR) printf("w"); // user write
if (info.st_mode & S_IXUSR) printf("x"); // user execute
```

Here’s a concise and clear way to write the answers for your `REPORT.md` file:

---

## **Report – Feature 3: Column Display (v1.2.0)**

### 1. Down-then-across columnar format

The "down then across" format prints files in columns starting **from top to bottom**, then moves **left to right** across columns.

**Logic:**

1. Calculate the number of columns that can fit in the terminal based on the **longest filename** and **terminal width**.
2. Determine the number of rows needed:

   ```
   rows = ceil(total_files / columns)
   ```
3. Iterate **row by row**, printing the item for each column in that row. For example:

   ```
   for row in 0..rows-1:
       for col in 0..columns-1:
           index = col * rows + row
           print(files[index])
   ```
4. Pad each column so that all filenames are properly aligned.

**Why a simple single loop is insufficient:**

* A single loop prints files linearly, **left to right**, which does not maintain the “down then across” order.
* To achieve correct column alignment, we need to **jump indices** so that each row receives the correct items from each column.

---

### 2. Purpose of `ioctl` system call

* The `ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)` call is used to **detect the current terminal width**.
* This allows the program to dynamically adjust the **number of columns** so that the output fits neatly in the terminal.

**Limitation of using a fixed width (e.g., 80 columns):**

* If the terminal is wider than 80 characters, columns will not use the full space, leaving extra gaps.
* If the terminal is narrower, columns may overflow or wrap incorrectly.
* Dynamic detection ensures the output **adapts** to different terminal sizes, improving usability.

---




