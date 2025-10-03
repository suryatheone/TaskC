#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTask(Task **tasks, int *task_count, char task_name[],
             char task_description[], int *capacity, int *next_id) {
  if (*task_count == *capacity) {
    int new_capacity = (*capacity) * 2;
    Task *temp = realloc(*tasks, new_capacity * sizeof(Task));
    if (temp == NULL) {
      perror("Error reallocating memory");
      return;
    }
    *tasks = temp;
    *capacity = new_capacity;
  }

  (*tasks)[*task_count].id = (*next_id)++;
  strncpy((*tasks)[*task_count].name, task_name,
          sizeof((*tasks)[*task_count].name) - 1);
  (*tasks)[*task_count].name[sizeof((*tasks)[*task_count].name) - 1] = '\0';
  strncpy((*tasks)[*task_count].description, task_description,
          sizeof((*tasks)[*task_count].description) - 1);
  (*tasks)[*task_count]
      .description[sizeof((*tasks)[*task_count].description) - 1] = '\0';

  (*task_count)++;
}

void deleteTask(Task **tasks, int task_id, int *task_count) {
  int task_index = -1;

  for (int i = 0; i < *task_count; i++) {
    if ((*tasks)[i].id == task_id) {
      task_index = i;
      break;
    }
  }

  if (task_index != -1) {
    for (int i = task_index; i < *task_count - 1; i++) {
      (*tasks)[i] = (*tasks)[i + 1];
    }
    (*task_count)--;
    printf("\nTask with ID %d deleted successfully.\n", task_id);
  } else {
    printf("\nTask with ID %d not found.\n", task_id);
  }
}

void showTasks(Task *tasks, int task_count) {
  printf("\n--- Task List ---\n");
  if (task_count == 0) {
    printf("  (No tasks to show)\n");
  } else {
    for (int i = 0; i < task_count; i++) {
      printf("  [%d] %s\n", tasks[i].id, tasks[i].name);
      printf("      Description: %s\n", tasks[i].description);
    }
  }
  printf("------------------\n");
}

void saveTasks(Task *tasks, int task_count, int next_id) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("\nError opening file for writing");
    return;
  }
  char buffer[1024];

  snprintf(buffer, sizeof(buffer), "%d\n", next_id);
  fputs(buffer, file);

  for (int i = 0; i < task_count; i++) {
    snprintf(buffer, sizeof(buffer), "%d,%s,%s\n", tasks[i].id, tasks[i].name,
             tasks[i].description);
    fputs(buffer, file);
  }
  fclose(file);
  printf("\nTasks saved successfully.\n");
}



int loadTasks(Task **tasks, int *task_count, int *capacity) {
  FILE *file = fopen(filename, "r");
  char buffer[512];
  int next_id = 1;

  if (file == NULL) {
    perror("Error opening file");
    return next_id;
  }
  if (fgets(buffer, sizeof(buffer), file) != NULL) {
    sscanf(buffer, "%d", &next_id);
  }

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    if (*task_count >= *capacity) {
      *capacity *= 2;
      Task *temp = realloc(*tasks, *capacity * sizeof(Task));
      if (temp == NULL) {
        perror("Error reallocating memory");
        fclose(file);
        return next_id;
      }
      *tasks = temp;
    }

    sscanf(buffer, "%d,%255[^,],%511[^\n]", &(*tasks)[*task_count].id,
           (*tasks)[*task_count].name, (*tasks)[*task_count].description);

    (*task_count)++;
  }

  fclose(file);
  return next_id;
}
