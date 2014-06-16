#include "../include/os.hpp"

QueueofTasks OsQueue;
QueueofTasks CompletedTask;
QueueofTasks WaitingTask;
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
	for(auto value : OsQueue)
	{
		cout << value << endl;
	}
}
void OS_MODEL::PringComp(void)
{
	for(auto value : CompletedTask)
	{
		cout << value << endl;
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
void OS_MODEL::TerminateTask(_iterator it)
{
	cout << "Terminate Task " << it->TaskName << endl;
	CompletedTask.push_front(*it);
	OsQueue.erase(it);
	cout << "End of Terminate Task " << CompletedTask.begin() ->TaskName << endl;
}
_iterator OS_MODEL::FindTask(string TaskName)
{
	_iterator it = OsQueue.begin();
	while(it != OsQueue.end())
	{
		if(it -> TaskName == TaskName)
		{
			return it;
		}
		else
		{
			it++;
		}
	}
	return OsQueue.end();
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
SimpleSemaphore OS_MODEL::setSemaphore(string SemaphoreName, int Counter,
		bool Aviavable, string ResourceName)
{
	SimpleSemaphore smp;
	smp.SemaphoreName = SemaphoreName;
	smp.Counter = Counter;
	smp.Aviavable = Aviavable;
	smp.ResourceName = ResourceName;
	return smp;
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
	cout << "@Disptatch " << TaskName << endl;
	_iterator it = OsQueue.begin();
	_iterator end = OsQueue.end();
	while(it != end)
	{
		cout << "\tCurrent Task on execute " << it->TaskName << endl;
		it->action();
		end = OsQueue.end();
		it = OsQueue.begin();
	}
	cout << "@End of Disptatch " << TaskName << endl;
}
