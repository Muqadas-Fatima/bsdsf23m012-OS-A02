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

* Repeat for group (`S_IRGRP`, `S_IWGRP`, `S_IXGRP`) and others (`S_IROTH`, `S_IWOTH`, `S_IXOTH`).
* Use **bitwise AND `&`** with predefined macros to check the bits.


Do you want me to do that?
