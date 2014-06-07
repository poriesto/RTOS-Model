#include "../include/os.hpp"
using namespace std;

void act(void)
{
	cout << "!Begin Task1" <<endl;
	cout << "Working Task1" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask1"));
	cout << "_Jump to Task2" << endl;
	OS_MODEL::ActivateTask("sometask2");
	cout << "_Drop from Task2" << endl;
	cout << "!End Task1" << endl;
}
void act4(void)
{
	cout << "Begin Task4" << endl;
	cout << "Working Task4" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask4"));
	cout << "End Task4" << endl;
}
void act1(void)
{
	cout << "Begin Task3" << endl;
	cout << "Working Task3" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask3"));
	cout << "End Task3" << endl;
}
void act2(void)
{
	cout << "!Begin Task2" << endl;
	cout << "Working Task2" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask2"));
	cout << "_Jump to Task1" << endl;
	OS_MODEL::ActivateTask("sometask1");
	cout << "_Drop from Task1" << endl;
	cout << "!End Task2" << endl;
}
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

int main(int argc, char *argv[])
{
	OS_MODEL *OS = new OS_MODEL();
	SimpleSemaphore smp;

	OS -> DeclareTask("sometask1", 2, act);
	OS -> DeclareTask("sometask2", 5, act2);
	//OS -> DeclareTask("sometask1", 2, idealTask1);
	//OS -> DeclareTask("sometask2", 5, idealTask);
	OS -> DeclareTask("sometask3", 7, act1);
	OS -> DeclareTask("sometask4", 12, act4);
	OS -> DeclareResource("Resource1", smp);
	smp = OS -> setSemaphore("Sem1", -1, true, "Resource1");

	OS->PringQueue();
	cout << endl;
	OS->ActivateTask("sometask2");
	
	/*cout << "ResQu" << endl;
	OS -> PringQueueRsc();
	cout << smp;*/

	cout << "\nCompletedTask" << endl;
	OS -> PringComp();
	cout << "\nAfterTerminate" << endl;
	OS -> PringQueue();
	return 0;
}
