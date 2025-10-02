#ifndef TASK_H
#define TASK_H

#define filename "data/tasks.txt"

typedef struct {
  int id;
  char name[256];
  char description[512];
} Task;

void addTask(Task **tasks, int *n, char name[], char desc[], int *capacity);
void deleteTask(Task **tasks, int id, int *n);
void showTasks(Task *tasks, int n);
void saveTasks(Task *tasks, int n);
void loadTasks(Task **tasks, int *n, int *capacity);

#endif
