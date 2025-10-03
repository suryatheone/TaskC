# Simple Task Manager

This is a simple command-line task manager written in C.

## How to Compile and Run

### Prerequisites

- A C compiler (like `clang` or `gcc`)
- `cmake`

### Steps

1.  **Configure the project:**
    ```sh
    cmake -B build
    ```

2.  **Compile the project:**
    ```sh
    cmake --build build
    ```

3.  **Run the application:**
    ```sh
    ./build/main
    ```

4.  **Clean the build files:**
    ```sh
    rm -rf build
    ```

## Usage

The application supports the following commands:

- `Add`: Add a new task.
- `Del [id]`: Delete a task with the specified ID.
- `Show`: Show the list of all tasks.
- `Exit`: Save tasks and exit the program.