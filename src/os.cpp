#include "../include/os.hpp"

static QueueofTasks OsQueue;
static QueueofResources ResQueue;
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

void OS_MODEL::DeclareResource(string ResourceName, SimpleSemaphore &smp)
{
	if(ResQueue.size() < MAX_RESOURCES)
	{
		OsResource.ResourceName = ResourceName;
		OsResource.smp = smp;
		ResQueue.insert(begin(ResQueue), OsResource);
	}
}

bool OS_MODEL::GetReosurce(string ResourceName)
{
	for(auto value : ResQueue)
	{
		if(value.ResourceName == ResourceName)
		{
			if(value.smp.Aviavable)
			{
				value.smp.Aviavable = false;
				value.smp.Counter += 1;
				value.TaskNameOwner = "NULL";
			}
		}
	}
	return true;
}

void OS_MODEL::PringQueueRsc(void)
{
	for(auto value : ResQueue){
		cout << value.ResourceName;
	}
}

bool OS_MODEL::Schedule(void)
{
	OsQueue.sort([](MyTask a, MyTask b)
			{
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


