#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NEXT_ID;

void addTask(Task **tasks, int *n, char name[], char desc[], int *capacity) {
  if (*n == *capacity) {
    *tasks = (Task *)realloc(*tasks, ((*capacity) * 2) * sizeof(Task));
    *capacity *= 2;
  }

  (*tasks)[*n].id = NEXT_ID + 1;
  strcpy((*tasks)[*n].name, name);
  strcpy((*tasks)[*n].description, desc);

  (*n)++;
  NEXT_ID++;
}

void deleteTask(Task **tasks, int id, int *n) {
  int indexTask;

  for (int i = 0; i < *n; i++) {
    if ((*tasks)[i].id == id) {
      indexTask = i;
      break;
    }
  }

  for (int i = indexTask; i < *n - 1; i++) {
    (*tasks)[i] = (*tasks)[i + 1];
  }

  (*n)--;
}

void showTasks(Task *tasks, int n) {
  for (int i = 0; i < n; i++) {
    printf("[%-2d] %s\n", tasks[i].id, tasks[i].name);
  }
}

void saveTasks(Task *tasks, int n) {
  FILE *file = fopen(filename, "w");
  char buffer[1024];

  snprintf(buffer, sizeof(buffer), "%d\n", NEXT_ID);
  fputs(buffer, file);

  for (int i = 0; i < n; i++) {
    snprintf(buffer, sizeof(buffer), "%d,%s,%s\n", tasks[i].id, tasks[i].name,
             tasks[i].description);
    fputs(buffer, file);
  }
  fclose(file);
  printf("Save task succesfull\n");
}

void loadTasks(Task **tasks, int *n, int *capacity) {
  FILE *file = fopen(filename, "r");
  char buffer[512];

  if (file == NULL) {
    perror("Error opening file");
    return;
  }
  if (fgets(buffer, sizeof(buffer), file) != NULL) {
    sscanf(buffer, "%d", &NEXT_ID);
  }

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    if (*n >= *capacity) {
      *capacity *= 2;
      *tasks = (Task *)realloc(*tasks, *capacity * sizeof(Task));
    }

    sscanf(buffer, "%d,%49[^,],%99[^\n]", &(*tasks)[*n].id, (*tasks)[*n].name,
           (*tasks)[*n].description);

    (*n)++;
  }

  fclose(file);
}
