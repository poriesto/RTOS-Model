#include "../include/os.hpp"

static QueueofTasks OsQueue;
static QueueofTasks CompletedTask;
static QueueofTasks WaitingTask;
static QueueofResources ResQueue;
using namespace std;

//some overloads
ostream& operator <<(ostream& os, const MyTask& task)
{
	os << "Task name: " << task.TaskName << ", Task Priority: " << task.Prior;
	return os;
}
ostream& operator <<(ostream& os, const Resource rsc)
{
	os << "Resource name: " << rsc.ResourceName << ", Resource TaskNameOwner: " << rsc.TaskNameOwner;
	return os;
}
ostream& operator <<(ostream& os, const SimpleSemaphore smp)
{
	os << "Semaphore name: " << smp.SemaphoreName << ", Counter: " << smp.Counter <<
		", Aviavable: " << smp.Aviavable << ", Resource: " << smp.ResourceName;
	return os;
}

void OS_MODEL::PringQueue(void)
{
	for(auto val : OsQueue)
	{
		cout << val << endl;
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
void OS_MODEL::TerminateTask()
{
	CompletedTask.push_back(OsTask);
	for(auto value : OsQueue)
	{
		if(value.TaskName == OsTask.TaskName)
		{
			OsQueue.remove(value);
		}
	}
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
		cout << value << endl;
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

