# Simple Task Manager

This is a simple command-line task manager written in C.

## How to Compile and Run

### Prerequisites

- A C compiler (like `clang` or `gcc`)
- `make`

### Steps

1.  **Compile the project:**
    ```sh
    make
    ```

2.  **Run the application:**
    ```sh
    make run
    ```
    or
    ```sh
    ./build/main
    ```

3.  **Clean the build files:**
    ```sh
    make clean
    ```

## Usage

The application supports the following commands:

- `Add`: Add a new task.
- `Del [id]`: Delete a task with the specified ID.
- `Show`: Show the list of all tasks.
- `Exit`: Save tasks and exit the program.
