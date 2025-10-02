#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

Task inputTask() {
  Task t;

  printf("Enter task name: ");
  if (fgets(t.name, sizeof(t.name), stdin)) {
    t.name[strcspn(t.name, "\n")] = 0;
  }

  printf("Enter task description: ");
  if (fgets(t.description, sizeof(t.description), stdin)) {
    t.description[strcspn(t.description, "\n")] = 0;
  }

  return t;
}

int main() {

  system("clear");
  printf("Simple Task Manager\n\n");

  int n = 0;

  int capacity = 1;

  Task *tasks = malloc(capacity * sizeof(Task));

  if (!tasks) {
    fprintf(stderr, "Memory alocation failed\n");
    return 1;
  }

  loadTasks(&tasks, &n, &capacity);

  while (1) {
    char full_input[50];
    char command_only[16];
    int idTask = -1;
    int items_read = 0;

    printf("Enter command (Add, Del [id], Show, Exit): ");

    if (fgets(full_input, sizeof(full_input), stdin) == NULL) {
      printf("Error reading input.\n");
      break;
    }

    full_input[strcspn(full_input, "\n")] = 0;

    items_read = sscanf(full_input, "%15s %d", command_only, &idTask);

    if (items_read >= 1) {

      if (strcmp(command_only, "Add") == 0) {
        Task t = inputTask();
        addTask(&tasks, &n, t.name, t.description, &capacity);

      } else if (strcmp(command_only, "Del") == 0) {

        if (items_read == 2) {
          deleteTask(&tasks, idTask, &n);
        } else {
          printf("Error: Del command requires task ID (example: Del 5).\n");
        }

      } else if (strcmp(command_only, "Show") == 0) {
        showTasks(tasks, n);

      } else if (strcmp(command_only, "Exit") == 0) {
        printf("Exiting program...\n");
        break;

      } else {
        printf("Unknown command: %s\n", command_only);
      }
    } else {
      printf("Empty input.\n");
    }
  }

  saveTasks(tasks, n);
  return 0;
}
