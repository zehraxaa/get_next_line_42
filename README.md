*This project has been created as part of the 42 curriculum by aaydogdu.*

---

## Description

**get_next_line** is a C function that reads a single line from a file descriptor each time it is called. When called repeatedly — typically in a loop — it allows you to read an entire file line by line, returning each line including its terminating `\n` character. When there is nothing left to read or an error occurs, it returns `NULL`.

The function works with any valid file descriptor: regular files, standard input, and more. It is designed to handle varying buffer sizes at compile time via the `-D BUFFER_SIZE=n` flag, and must behave correctly regardless of whether that size is 1, 42, or 10,000,000.

---

## Algorithm

The implementation uses a **linked-list stash** as its internal buffer. A `static` pointer to this list persists between calls, storing any data that was read beyond the current line.

The logic follows three steps on each call:

1. **`read_stash`** — Reads from the file descriptor in chunks of `BUFFER_SIZE` bytes, appending each chunk as a new node to the stash list. Reading stops as soon as a `\n` is found in the most recently added node.

2. **`extract_line`** — Traverses the stash list from the beginning, copying characters into a freshly allocated string until `\n` is reached (inclusive). This is the string that gets returned to the caller.

3. **`clean_stash`** — Frees the entire stash, but first saves any leftover content after the `\n` in the last node into a brand-new single-node list. This new list becomes the stash for the next call.

**Why a linked list?**  
Because each `read()` call may produce data that spans multiple lines — or none at all. Appending raw buffers as nodes avoids costly string concatenation on every read and keeps ownership of each chunk clear: a node's content is freed only when the whole stash is cleaned, which happens exactly once per line returned.

---

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

You can replace `42` with any positive integer as the buffer size. The project also compiles without the flag if a default is defined in the header.

### Usage

Include the header in your source file and link the two `.c` files:

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

### Files

| File | Description |
|---|---|
| `get_next_line.h` | Header — struct definition, prototype, and includes |
| `get_next_line.c` | Core logic: `read_stash`, `extract_line`, `copy_rest`, `clean_stash`, `get_next_line` |
| `get_next_line_utils.c` | Helper functions: `lst_last`, `lst_add_back`, `has_new_line`, `line_len`, `free_list` |

---

## Resources

- [read() man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Linked lists in C — Tutorialspoint](https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm)
- [open(), read(), close() — The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I_002fO.html)

### AI Usage

bu benim arama geçmişimi nerden biliyo? teknoloji çok gelişti...
