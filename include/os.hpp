#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#define MAX_TASKS (int)32
#define MAX_RESOURCES (int)16

struct SimpleSemaphore
{
    string SemaphoreName;
	int UserCounter;
	string ReourceName;
};

struct MyTask
{
	int Prior;
	std::function<void(void)>action;
	std::string TaskName;
};

typedef std::list<MyTask> QueueofTasks;


class OS_MODEL
{
    public:
   	int Start_OS(MyTask &Task);
	static bool Schedule ();
	static void Disptatch (std::string TaskName);
	static void ActivateTask (std::string Name);
	static void TerminateTask(); // feature under pre investigation control
	void DeclareTask(std::string TaskName, int Priority, void(*fun)(void)); // later reflect on the implementation of bool
	// some debug stuff in next verison it will be private(for ut)
	void PringQueue(void);
	private:
	MyTask OsTask;
};

