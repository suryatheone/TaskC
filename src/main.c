#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Task inputTask() {
  Task new_task;

  printf("  > Enter task name: ");
  if (fgets(new_task.name, sizeof(new_task.name), stdin)) {
    new_task.name[strcspn(new_task.name, "\n")] = 0;
  }

  printf("  > Enter task description: ");
  if (fgets(new_task.description, sizeof(new_task.description), stdin)) {
    new_task.description[strcspn(new_task.description, "\n")] = 0;
  }

  return new_task;
}

int main() {
  system("clear");
  printf("--- Simple Task Manager ---\n");

  int task_count = 0;
  int capacity = 1;
  int next_id = 1;

  Task *tasks = malloc(capacity * sizeof(Task));

  if (!tasks) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  next_id = loadTasks(&tasks, &task_count, &capacity);

  while (1) {
    char input_buffer[50];
    char command[16];
    int task_id_to_delete = -1;
    int scanned_items = 0;

    printf("\n> Enter command (Add, Del [id], Show, Exit): ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
      printf("\nError reading input.\n");
      break;
    }

    input_buffer[strcspn(input_buffer, "\n")] = 0;

    scanned_items = sscanf(input_buffer, "%15s %d", command, &task_id_to_delete);

    if (scanned_items >= 1) {
      if (strcmp(command, "Add") == 0) {
        Task new_task = inputTask();
        addTask(&tasks, &task_count, new_task.name, new_task.description,
                &capacity, &next_id);
        printf("\nTask added successfully.\n");
      } else if (strcmp(command, "Del") == 0) {
        if (scanned_items == 2) {
          deleteTask(&tasks, task_id_to_delete, &task_count);
        } else {
          printf(
              "\nError: Del command requires a task ID (e.g., Del 5).\n");
        }
      } else if (strcmp(command, "Show") == 0) {
        showTasks(tasks, task_count);
      } else if (strcmp(command, "Exit") == 0) {
        printf("\nExiting program...\n");
        break;
      } else {
        printf("\nUnknown command: %s\n", command);
      }
    } else {
      printf("\nEmpty input.\n");
    }
  }

  saveTasks(tasks, task_count, next_id);
  free(tasks);
  printf("--- Session End ---\n");
  return 0;
}
