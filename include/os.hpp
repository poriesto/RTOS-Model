#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#define MAX_TASKS 32
#define MAX_RESOURCES 16

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
typedef QueueofTasks::iterator _iterator;

std::ostream& operator <<(std::ostream& os, const SimpleSemaphore smp);
std::ostream& operator <<(std::ostream& os, const Resource rsc);
std::ostream& operator <<(std::ostream& os, const MyTask& task);

//actions for OS task
void act(void);
void act1(void);
void act2(void);
void act4(void);
void idealTask1(void);
void idealTask2(void);

class OS_MODEL
{
    public:
 	  	int Start_OS(void);
		static bool Schedule ();
		static void Disptatch (std::string TaskName);
		static void ActivateTask (std::string Name);
		static _iterator FindTask(std::string TaskName);
		static void TerminateTask(_iterator it); // feature under pre investigation control delete from list and push to completed task
		void DeclareTask(std::string TaskName, int Priority, void(*fun)(void), SimpleSemaphore smp);
		void DeclareSemaphore(std::string SemaphoreName, int Counter, bool Aviavable, std::string ReourceName);
		// some debug stuff in next verison it will be private(for ut)
		void DebugPring(std::string list);
		void PringQueueRsc(void);
		//some for resources
		void DeclareResource(std::string ReourceName, SimpleSemaphore &smp);
		static bool GetReosurce(std::string ResourceName, std::string TaskName);
		static bool ReleaseResource(std::string ResourceName);
	private:
		MyTask OsTask;
		Resource OsResource;
		SimpleSemaphore smp;
};
