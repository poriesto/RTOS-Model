#include "../include/os.hpp"

QueueofTasks OsQueue;
QueueofTasks CompletedTask;
QueueofTasks WaitingTask;
QueueofResources ResQueue;

using namespace std;

//some overloads
ostream& operator <<(ostream& os, const MyTask& task)
{
	os << "Task name: " << task.TaskName << ", Task Priority: " << task.Prior;
	return os;
}
ostream& operator <<(ostream& os, const Resource rsc)
{
	os << "Resource name: " << rsc.ResourceName << ", Resource TaskNameOwner: " << rsc.TaskNameOwner
		<< "\nSemaphore status: " << rsc.smp;
	return os;
}
ostream& operator <<(ostream& os, const SimpleSemaphore smp)
{
	os << "Semaphore name: " << smp.SemaphoreName << ", Counter: " << smp.Counter <<
		", Aviavable: " << smp.Aviavable << ", Resource: " << smp.ResourceName;
	return os;
}
//implemets class methods
int OS_MODEL::Start_OS(void)
{
	DeclareTask("sometask1", 2, act);
	DeclareTask("sometask2", 5, act2);
	DeclareTask("sometask3", 7, act1);
	DeclareTask("sometask4", 12, act4);
	SimpleSemaphore sm = DeclareSemaphore("Sem1", -1, true, "Resource1");
	SimpleSemaphore sm1 = DeclareSemaphore("Sem2", -1, true, "Resource2");
	DeclareResource("Resource1", sm);
	DeclareResource("Resource2", sm1);
	return 0;
}
void OS_MODEL::DebugPring(string list)
{
	if (list == "OsQueue")
	{
		for (auto value : OsQueue)
		{
			cout << value << endl;
		}
	}
	else if (list == "CompletedTask")
	{
		for (auto value : CompletedTask)
		{
			cout << value << endl;
		}
	}
	else
	{
		for (auto value : ResQueue)
		{
			cout << value << endl;
		}
	}
}
void OS_MODEL::DeclareTask(string TaskName, int Priority, void(*fun)(void))
{
	if (OsQueue.size() <= MAX_TASKS)
	{
		OsTask.TaskName = TaskName;
		OsTask.Prior = Priority;
		OsTask.action = fun;
		OsQueue.insert(begin(OsQueue), OsTask);
	};
}
SimpleSemaphore OS_MODEL::DeclareSemaphore(string SemaphoreName, int Counter, bool Aviavable, string ResourceName)
{
	smp.SemaphoreName = SemaphoreName;
	smp.Counter = Counter;
	smp.Aviavable = Aviavable;
	smp.ResourceName = ResourceName;
	return smp;
}
void OS_MODEL::ActivateTask(string Name)
{
	bool IsScheduled = Schedule();
	if (IsScheduled) Disptatch(Name);
}
void OS_MODEL::TerminateTask(_iterator it)
{
	cout << "\t\tTerminate Task " << it->TaskName << endl;
	CompletedTask.push_front(*it);
	OsQueue.erase(it);
	cout << "\t\tEnd of Terminate Task " << CompletedTask.begin()->TaskName << endl;
}
_iterator OS_MODEL::FindTask(string TaskName)
{
	_iterator it = begin(OsQueue);
	while (it != end(OsQueue))
	{
		if (it->TaskName == TaskName)
		{
			return it;
		}
		else
		{
			it++;
		}
	}
	return it;
}
resiter OS_MODEL::FindResource(string ResourceName)
{
	resiter it = begin(ResQueue);
	while (it != end(ResQueue))
	{
		if (it->ResourceName == ResourceName)
		{
			return it;
		}
		else
		{
			it++;
		}
	}
	return it;
}
void OS_MODEL::DeclareResource(string ResourceName, SimpleSemaphore &smp)
{
	if (ResQueue.size() < MAX_RESOURCES)
	{
		OsResource.ResourceName = ResourceName;
		OsResource.smp = smp;
		ResQueue.insert(begin(ResQueue), OsResource);
	}
}
bool OS_MODEL::GetReosurce(string ResourceName, string TaskName)
{
	for(auto& value : ResQueue)
	{
		if(value.ResourceName == ResourceName)
		{
			if(value.smp.Aviavable)
			{
				value.smp.Aviavable = false;
				value.smp.Counter += 1;
				value.TaskNameOwner = TaskName;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
bool OS_MODEL::ReleaseResource(string ResourceName)
{
	cout << "Begin Release resource" << endl;
	for(auto& value : ResQueue)
	{
		if(value.ResourceName == ResourceName)
		{
			if(!value.smp.Aviavable)
			{
				value.smp.Aviavable = true;
				value.smp.Counter -= 1;
				value.TaskNameOwner = "";
				cout << value << endl;
				cout << "End of Release Resource" << endl;
				return true;
			}
			else
			{
				cout << endl << "End of Release Resource" << endl;
				return false;
			}
		}
	}
	return false;
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
	while (it != end)
	{
		cout << "\tCurrent Task on execute " << it->TaskName << endl;
		it->action();
		end = OsQueue.end();
		it = OsQueue.begin();
	}
	cout << "@End of Disptatch " << TaskName << endl;
}

void act(void)
{
	cout << "\t!Begin Task1" << endl;
	cout << "\t\tWorking Task1" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask1"));
	cout << "\t\t_Jump to Task2" << endl;
	OS_MODEL::ActivateTask("sometask2");
	cout << "\t\t_Drop from Task2" << endl;
	cout << "\t!End Task1" << endl;
}
void act1(void)
{
	cout << "\tBegin Task3" << endl;
	cout << "\t\tWorking Task3" << endl;
	if (OS_MODEL::GetReosurce("Resource1", "sometask3"))
	{
		cout << "\t\tResource1 taked by sometask3\n";
		cout << "\t\t"  << *OS_MODEL::FindResource("Resource1") << endl;
	}
	else
	{
		cout << "\t\tReosurce1 cant taked by sometask3\n";
	}
	if(OS_MODEL::ReleaseResource("Resource1"))
	{
		cout << "\t\tResource1 released by sometask3\n";
	}
	else
	{
		cout << "\t\tResource1 cant released by sometask3\n";
	}
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask3"));
	cout << "\tEnd Task3" << endl;
}
void act2(void)
{
	cout << "\t!Begin Task2" << endl;
	cout << "\t\tWorking Task2" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask2"));
	cout << "\t\t_Jump to Task1" << endl;
	OS_MODEL::ActivateTask("sometask1");
	cout << "\t\t_Drop from Task1" << endl;
	cout << "\t!End Task2" << endl;
}
void act4(void)
{
	cout << "\tBegin Task4" << endl;
	cout << "\t\tWorking Task4" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask4"));
	cout << "\tEnd Task4" << endl;
}
//DONT USE THIS. feauture under developmemt
void idealTask1(void)
{
	cout << "\n!Begin Task1" << endl;
	cout << "Working Task1" << endl;
	cout << "_Jump to Task2" << endl;
	OS_MODEL::ActivateTask("sometask2");
	cout << "_Drop from Task2" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask1"));
	cout << "!End Task1\n" << endl;
}
void idealTask2(void)
{
	cout << "\n!Begin Task2" << endl;
	cout << "Working Task2" << endl;
	cout << "_Jump to Task1" << endl;
	OS_MODEL::ActivateTask("sometask1");
	cout << "_Drop from Task1" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask2"));
	cout << "!End Task2\n" << endl;
}
