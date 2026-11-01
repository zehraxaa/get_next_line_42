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
| `get_next_line_bonus.h` | Bonus header — same as the mandatory one, plus the `MAX_FD` definition |
| `get_next_line_bonus.c` | Bonus core logic: same functions, but the stash is selected per file descriptor |
| `get_next_line_utils_bonus.c` | Bonus helper functions (identical to the mandatory ones) |

### Bonus compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c
```

---

## Bonus

The bonus version can read from **several file descriptors at the same time**, using **only one static variable**. You can call `get_next_line()` on fd 3, then fd 4, then fd 5, then fd 3 again, and each call returns the next line of the correct file without losing its reading state.

**What changes compared to the mandatory part:** the mandatory version keeps a single `static t_list *stash`, which only remembers the leftover data of one file. In the bonus, that variable becomes a static array, `static t_list *stash[MAX_FD]`. It is still a single static variable, but each file descriptor owns its own slot: `stash[fd]`. Since `&stash[fd]` has exactly the same type as the old `&stash`, the helper functions (`read_stash`, `extract_line`, `clean_stash`, `lst_*`) did not need to change; only `get_next_line()` now chooses which slot to work on. An error on one fd only frees that fd's slot and never affects the others.

**Why an array?** It keeps the lookup trivial (direct indexing, no search) and respects the one-static-variable rule without a second layer of lists.

**Limits of this design:**

- `MAX_FD` is fixed at compile time (1024). File descriptors that are negative or greater than or equal to `MAX_FD` make the function return `NULL`.
- If a descriptor is closed before its file was read until EOF, its leftover data stays in `stash[fd]` until it is read to the end; if the same number is reused for another file, that old data would be mixed in. The function cannot know that a descriptor was closed.

**Testing:** `main_bonus.c` takes several file names as arguments and reads them in round-robin (one line from each file per round), so it is easy to check that the lines never get mixed up between files:

```bash
./a.out file1.txt file2.txt file3.txt
valgrind --leak-check=full ./a.out file1.txt file2.txt file3.txt
```

---

## Resources

- [read() man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Linked lists in C](https://www.w3schools.com/dsa/dsa_theory_linkedlists.php)

### AI Usage

- **Planning and design:** I used Claude to understand the overall
  approach: why a static variable is needed, how a linked list of raw
  `BUFFER_SIZE` chunks avoids repeated reallocation, and how to split the
  work between `get_next_line.c` and `get_next_line_utils.c`.
- **Concept refreshers:** Claude re-explained linked lists, double
  pointers (`t_list **`), `read()` return values and the lifetime of
  static variables.
