# 🧾 get_next_line

**get_next_line** is a function that reads from a file descriptor **one line at a time**.  
It remembers where it left off between calls — meaning you can read files, input streams, or even pipes **seamlessly, line by line**.

This project is part of the **42 curriculum**, and its goal is to make you understand:
- How file descriptors and buffers actually work  
- How to manage static variables and memory carefully  
- And how to write efficient, leak-free code that handles multiple edge cases (yes, even those pesky newlines 😅)

---

## 🧠 What It Does

`get_next_line()` reads from any valid file descriptor until it finds a newline (`\n`) or reaches EOF.

Every call returns:
- The **next line** (including `\n` if present)
- Or **NULL** if there’s nothing left to read or an error occurs

### Example:
```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```
The output will be : 
- Line 1
- Line 2
- Line 3

---

### 🧩 Key Features

- ✅ Reads line by line (not character-by-character)
- ✅ Handles multiple file descriptors (each has its own static buffer)
- ✅ Works with any BUFFER_SIZE you define at compile time
- ✅ Memory-safe — each line is dynamically allocated and freed after us

### 🖋️ Author

Balica Virgil Eduard | Intra: bavirgil
42 Student | C Developer in Progress
