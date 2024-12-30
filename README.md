# Student Information Management System

## Project Overview
This project is a simple Student Information Management System that includes basic mathematical operations and string manipulation functionalities. It demonstrates the use of Software Configuration Management (SCM) principles and effective Git practices.

---

## Directory Structure
```
Software-Configuration-Management/
├── src/               # Contains source files (e.g., math_functions.cpp, string_functions.cpp)
├── include/           # Header files for the source code
├── Makefile           # Build automation file
└── .gitignore         # Specifies files to exclude from Git tracking
```

---

## Features

### Math Functions:
- **`add(int a, int b)`**: Adds two integers.
- **`subtract(int a, int b)`**: Subtracts the second integer from the first.
- **`multiply(int a, int b)`**: Multiplies two integers.
- **`divide(int a, int b)`**: Divides two integers. Handles division by zero with exception handling.

### String Functions:
- **`reverseString(const std::string& input)`**: Reverses the given string.
- **`concatenateStrings(const std::string& str1, const std::string& str2)`**: Concatenates two strings.
- **`toUpperCase(const std::string& input)`**: Converts all characters in the string to uppercase.
- **`toLowerCase(const std::string& input)`**: Converts all characters in the string to lowercase.

### Student Information Management System:
The Student Information Management System provides the following features:

1. **Add Record**: Allows users to add new student records, including details such as name, ID, and grades.
2. **Display Record**: Displays all stored student records in a user-friendly format.
3. **Modify Record**: Enables users to update existing student information.
4. **Delete Record**: Facilitates the removal of student records from the system.
5. **Search Record (Modified Feature)**: Allows users to search for specific student records using filters like ID or name.
6. **Rank of Students**: Automatically calculates and displays the ranking of students based on their grades.
7. **Statistics**: Provides statistical insights, such as average grades, top-performing students, and grade distribution.
8. **Generate CSV File (New Feature)**: Exports student records to a CSV file for easy sharing and external use.
9. **Course Details**: Displays detailed information about the courses offered, including descriptions and credits.
10. **About Us**: Provides an overview of the system developers and project goals.
11. **Contact Us**: Displays contact details for support or inquiries.

---

## Build and Run Instructions

### Prerequisites
- Ensure you have `g++` installed on your system.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/rahelabera/Software-Configuration-Management.git
   cd Software-Configuration-Management
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run the executable:
   ```bash
   ./src
   ```
4. Clean the build:
   ```bash
   make clean
   ```

---

## Git Practices

- **Version Control**:
  - Regular commits with descriptive messages.
  - Example: `git commit -m "Added divide function to math module"`

- **Branching**:
  - New features are developed on separate branches.
  - Example:
    ```bash
    git checkout -b feature/string_modification
    ```

- **Merging**:
  - Features are merged into the main branch after testing.
  - Example:
    ```bash
    git checkout main
    git merge feature/string_modification
    ```

- **`.gitignore`**:
  - Excludes unnecessary files like object files and executables.

---

