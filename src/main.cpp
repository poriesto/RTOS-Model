#include "../include/os.hpp"
using namespace std;

void act(void)
{
	cout << "Task1" <<endl ;
}

void act4(void)
{
	cout << "Task4" << endl;
}

void act1(void)
{
	cout << "Task3" << endl;
}

void act2(void)
{
	cout << "Task2" << endl;
}

int main(int argc, char *argv[])
{
	OS_MODEL *OS = new OS_MODEL();
	SimpleSemaphore smp;
	smp.ResourceName = "Resource1";
	smp.SemaphoreName = "Sem1";
	smp.Aviavable = true;
	smp.Counter = -1;
	OS -> DeclareTask("sometask1", 2, act);
	OS -> DeclareTask("sometask2", 5, act2);
	OS -> DeclareTask("sometask3", 7, act1);
	OS -> DeclareTask("sometask4", 12, act4);
	OS -> DeclareResource("Resource1", smp);

	OS->Schedule();
	OS->PringQueue();
	cout << endl;
	OS->ActivateTask("sometask1");
	cout << "ResQu" << endl;
	OS -> PringQueueRsc();
	cout << smp;

	return 0;
}
