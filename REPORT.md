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
# Report

## 1. Comparison of Vertical ("Down Then Across") and Horizontal ("Across") Printing Logic

The **vertical ("down then across")** printing logic is **more complex** because it requires **pre-calculating** the number of rows, columns, and index mapping to correctly print items column by column.  
The **horizontal ("across")** logic prints items sequentially, so it needs **little or no pre-calculation**.

**Conclusion:**  
Vertical mode needs more pre-processing since it rearranges data for column-wise output, while horizontal mode prints directly in sequence.

---

## 2. Strategy for Managing Display Modes (-l, -x, Default)

The program determines the display mode based on **command-line flags**:

| Option | Mode | Function |
|---------|------|-----------|
| `-l` | Long listing | `print_long()` |
| `-x` | Horizontal display | `print_horizontal()` |
| *default* | Vertical (down-then-across) | `print_vertical()` |

The selection logic is implemented using conditional statements:
```c
if (flag_l)
    print_long();
else if (flag_x)
    print_horizontal();
else
    print_vertical();




# Report

## 1. Reading Directory Entries Before Sorting

It is necessary to **read all directory entries into memory** before sorting because sorting algorithms, such as `qsort()`, require **random access to the complete dataset**.  
The program must first collect all filenames or directory entries into an array so that they can be compared and rearranged efficiently.

**Drawbacks:**  
For directories containing **millions of files**, this approach can:
- Consume a large amount of **memory (RAM)**.  
- Lead to **performance degradation** due to swapping or memory exhaustion.  
- Increase **processing time** and **I/O overhead**.

**Conclusion:**  
While reading all entries is required for sorting, it becomes inefficient and memory-intensive for extremely large directories.

---

## 2. Purpose and Signature of the Comparison Function in `qsort()`


The **`qsort()`** function in C is a general-purpose sorting function that requires a **user-defined comparison function** to determine the ordering of elements.

**Function signature:**
```c
int compare(const void *a, const void *b);







# Report

## 1. ANSI Escape Codes and Terminal Colors

**Explanation:**  
ANSI escape codes are **special character sequences** that control formatting, color, and other text attributes in a terminal.  
They start with the **Escape character (ASCII 27 or `\033`)**, followed by `[` and one or more parameters that define the style or color.

When the terminal receives these sequences, it interprets them as commands instead of text, changing the display properties such as foreground color, background color, or text style.

**Example – Printing text in green:**
```c
printf("\033[0;32mThis text is green\033[0m\n");


