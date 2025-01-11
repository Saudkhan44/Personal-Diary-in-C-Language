Personal Diary Project in C

This is a simple Personal Diary Project built in C. The application allows users to store and
manage their daily memories, tasks, and expenditures.
The data is stored in three binary files: *memory, *tasks*, and *expenditure*.

Files:
- main.c: The main source code that integrates the modules and manages user input.
- memory.bin: A binary file that stores memory-related data.
- tasks.bin: A binary file that stores task-related data.
- expenditure.bin: A binary file that stores expenditure-related data.

Features:
- Add new entries: Users can add new memories, tasks, and expenditures.
- View stored entries: View all the stored memory, tasks, and expenditure entries.
- Edit and delete entries: Modify or remove existing entries.
- Search: User can search any Entery and task by status and title.

How to Compile and Run in Dev C++:
1. Open Dev C++.
2. Open the *main.c* file.
3. Click on Execute > Compile and Run* or press *F11* to compile and run the program.

Example in Dev C++:
1. Open the project in Dev C++.
2. Click *Execute > Compile and Run* (or press *F11*).

How the Binary Files are Used:
- *memory.bin* stores memory-related data (e.g., diary entries, personal notes).
- *tasks.bin* stores task data (e.g., to-do lists, scheduled tasks).
- *expenditure.bin* stores financial data (e.g., spending, budgeting entries).

These binary files are read at the start of the program and written back to when the user adds, 
edits, or deletes entries. The files allow persistent storage of data even after the program is closed.
