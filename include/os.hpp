#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#define MAX_TASKS (int)32
#define MAX_RESOURCES (int)16

struct MyTask
{
	int Prior;
	std::function<void(void)>action;
	std::string TaskName;
};
struct SimpleSemaphore
{
	std::string SemaphoreName;
	int Counter;
	bool Aviavable;
	std::string ResourceName;
};
struct Resource
{
	std::string ResourceName;
	std::string TaskNameOwner;
	SimpleSemaphore smp;	
};

typedef std::list<MyTask> QueueofTasks;
typedef std::list<Resource> QueueofResources; 

std::ostream& operator <<(std::ostream& os, const SimpleSemaphore smp);
std::ostream& operator <<(std::ostream& os, const Resource rsc);
std::ostream& operator <<(std::ostream& os, const MyTask& task);

class OS_MODEL
{
    public:
 	  	int Start_OS(MyTask &Task);
		static bool Schedule ();
		static void Disptatch (std::string TaskName);
		static void ActivateTask (std::string Name);
		void TerminateTask(); // feature under pre investigation control delete from list and push to completed task
		void DeclareTask(std::string TaskName, int Priority, void(*fun)(void)); // later reflect on the implementation of bool
		// some debug stuff in next verison it will be private(for ut)
		void PringQueue(void);
		void PringQueueRsc(void);
		//some for resources
		void DeclareResource(std::string ReourceName, SimpleSemaphore &smp);
		static bool GetReosurce(std::string ResourceName);
		static bool ReleaseResource(std::string ResourceName);
	private:
		MyTask OsTask;
		Resource OsResource;
};
