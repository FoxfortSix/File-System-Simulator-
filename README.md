# 🗂️ Dynamic File System Replica

This project is a simple simulation of a **file system** implemented in **C language**, using **dynamic data structures** such as an **N-ary tree** and **queue**, with **level-order (BFS) traversal**, **pre-order traversal**, and custom command parsing.

---

## 📌 Overview

The program simulates basic operations found in a real file system:
- Create folders and files (`tambah`)
- Delete files or folders (`hapus`)
- List the directory tree (`list`)
- Move between directories (`pindah_ke`)
- Search for files/directories (`cari`)
- Reset the entire tree structure (`reset`)

All operations are managed through **dynamic memory allocation** and custom data structures.

---

## 📂 Data Structures Used

### 1️⃣ N-ary Tree (`simpul`)

- Each node (`simpul`) stores:
  - `type` — file or directory.
  - `name` — name of the file/directory.
  - `size` — file size in kB (directories store cumulative size).

- Each node can have:
  - `child` — pointer to its first child.
  - `sibling` — pointer to next sibling in a **circular linked list**.

The **N-ary tree** represents the hierarchy of folders and files.

---

### 2️⃣ Queue

- A linked-list-based queue (`queue`) is used to implement **level-order traversal** (Breadth-First Search).
- Each queue element stores a pointer to a tree node.
- Operations:
  - `createEmpty` — initialize queue.
  - `add` — enqueue.
  - `del` — dequeue.
  - `countElement` — count elements.

The queue helps perform **BFS** to:
- Find nodes by name.
- Find a directory containing a target child.
- Count directory depth.
- Update folder sizes efficiently.

---

### 3️⃣ Custom Word Machine

A simple **custom tokenizer** (`MESIN KATA`) splits user input into commands and arguments. This works like a scanner for parsing user instructions.

---

## 🔍 Algorithms

### ✅ **Adding a Node**
- `addChild` adds a new file or directory as a child of the current working directory (`toMove`).
- If there are multiple children, it maintains the **circular linked list** structure.

### ✅ **Deleting a Node**
- `delChild` locates the target child node by name and deletes it.
- Uses recursive `delAll` to free the subtree memory (post-order deletion).

### ✅ **Searching**
- `find_levelOrderTraversal` performs **BFS** to find a node by name.
- `find_directory_that_contains_target_as_a_child_levelOrderTraversal` finds the parent directory of a node.

### ✅ **Traversal**
- `printTreePreOrder` shows the entire file system in a pretty tree format.
- Uses **pre-order traversal** to print folders and files in a tree structure with proper indentation.
- Uses `directoryCounter` with BFS to calculate node depth for indentation.

### ✅ **Size Calculation**
- When a file is added or removed, `updateSeluruhUkuranDirektori` re-calculates all parent directory sizes using **BFS**.
- `hitungTotalUkuran` sums up all sizes recursively.

### ✅ **Command Execution**
- The main loop reads user input and calls `modify_data`:
  - Parses input command: `tambah`, `hapus`, `list`, `pindah_ke`, `cari`, `reset`, `exit`.
  - Validates end of input with `EOPCHECCKER` (semicolon).
  - Handles all operations with proper updates.

---

## ⚙️ Example Commands

- `tambah file report.txt 20;` — Adds a file named `report.txt` with size 20 kB.
- `tambah directory docs 0;` — Creates a new directory.
- `hapus report.txt;` — Deletes `report.txt`.
- `list;` — Shows tree structure starting from current directory.
- `pindah_ke docs;` — Changes working directory to `docs`.
- `cari report.txt;` — Searches for `report.txt`.
- `reset;` — Deletes all children under root.
- `exit;` — Exit program.

---

## 📌 How It Works Internally

- **Circular Sibling Links**:
  Each node’s siblings are linked in a **circular linked list**, allowing constant-time insert/delete operations.

- **Traversal & Update**:
  Uses **BFS** for search and size updates, and **pre-order traversal** for printing the tree.

- **Memory Safety**:
  Every `malloc` is paired with proper `free` calls (`delAll` and `delChild`).

- **Custom Command Parser**:
  `MESIN KATA` is a mini parser that splits commands by space until `;`.

---

## 🧩 Main Files

| File | Description |
|------|--------------|
| `header.h` | Data structure definitions, function prototypes |
| `machine.c` | Core logic: tree/queue operations, word machine, algorithms |
| `main.c` | Main loop: user input, calls parser, runs file system |

---

## 📝 Author

- **Mochammad Azka Basria** — TP5 Data Structure Assignment

---

✨ *This project is a study exercise for practicing dynamic data structures, memory management, BFS, and custom parsers in C.*  
