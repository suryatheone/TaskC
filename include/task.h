#ifndef TASK_H
#define TASK_H

#define filename "data/tasks.txt"

typedef struct {
  int id;
  char name[256];
  char description[512];
} Task;

void addTask(Task **tasks, int *task_count, char task_name[],
             char task_description[], int *capacity, int *next_id);
void deleteTask(Task **tasks, int task_id, int *task_count);
void showTasks(Task *tasks, int task_count);
void saveTasks(Task *tasks, int task_count, int next_id);
int loadTasks(Task **tasks, int *task_count, int *capacity);

#endif
