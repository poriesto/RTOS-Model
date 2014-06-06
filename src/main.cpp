#include "../include/os.hpp"
using namespace std;

void act(void)
{
	cout << "Task1" <<endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask1"));
	OS_MODEL::ActivateTask("sometask2");
}

void act4(void)
{
	cout << "Task4" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask4"));
}

void act1(void)
{
	cout << "Task3" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask3"));
}

void act2(void)
{
	cout << "Task2" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask2"));
	OS_MODEL::ActivateTask("sometask1");
	
}

int main(int argc, char *argv[])
{
	OS_MODEL *OS = new OS_MODEL();
	SimpleSemaphore smp;
	/*smp.ResourceName = "Resource1";
	smp.SemaphoreName = "Sem1";
	smp.Aviavable = true;
	smp.Counter = -1;*/
	OS -> DeclareTask("sometask1", 2, act);
	OS -> DeclareTask("sometask2", 5, act2);
	OS -> DeclareTask("sometask3", 7, act1);
	OS -> DeclareTask("sometask4", 12, act4);
	OS -> DeclareResource("Resource1", smp);
	smp = OS -> setSemaphore("Sem1", -1, true, "Resource1");

	OS->Schedule();
	OS->PringQueue();
	cout << endl;
	OS->ActivateTask("sometask2");
	cout << "ResQu" << endl;
	OS -> PringQueueRsc();
	cout << smp;
	cout << "\nCompletedTask" << endl;
	OS -> PringComp();
	cout << "\nAfterTerminate" << endl;
	OS -> PringQueue();
	return 0;
}
