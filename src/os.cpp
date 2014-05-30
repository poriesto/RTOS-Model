#include "../include/os.hpp"

static QueueofTasks OsQueue;
using namespace std;

void OS_MODEL::PringQueue(void)
{
	for(auto val : OsQueue)
	{
		cout << " " << val.TaskName;
	}
}
void OS_MODEL::DeclareTask(string TaskName, int Priority, void(*fun)(void))
{
	if (OsQueue.size() <= MAX_TASKS )
	{
	OsTask.TaskName = TaskName;
	OsTask.Prior = Priority;
	OsTask.action = fun;
	OsQueue.insert (OsQueue.begin(), OsTask);
	};
}
void OS_MODEL::ActivateTask(string Name)
{
	bool IsScheduled = Schedule();
	if (IsScheduled) Disptatch(Name);

}

bool OS_MODEL::Schedule(void)
{
	OsQueue.sort([](MyTask a, MyTask b){
				return a.Prior > b.Prior;
			});
	return true;
}

void OS_MODEL::Disptatch(string TaskName)
{
	for(auto value : OsQueue)
	{
		value.action();
		if(value.TaskName == TaskName)
		{
			break;
		}
	}
}


