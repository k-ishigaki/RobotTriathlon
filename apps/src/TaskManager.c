#include "TaskManager.h"

#define USING_TASK_MANAGER_SUBSTANCE

#define NAMESPACE(name) TaskManager1_##name
#define TaskManager1_getter getTaskManger1
#include "TaskManager.substance.c"

#define NAMESPACE(name) TaskManager2_##name
#define TaskManager2_getter getTaskManger2
#include "TaskManager.substance.c"
