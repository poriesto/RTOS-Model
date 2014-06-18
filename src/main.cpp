#include "../include/os.hpp"
using namespace std;

void act(void)
{
	cout << "\t!Begin Task1" <<endl;
	cout << "\t\tWorking Task1" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask1"));
	cout << "\t\t_Jump to Task2" << endl;
	OS_MODEL::ActivateTask("sometask2");
	cout << "\t\t_Drop from Task2" << endl;
	cout << "\t!End Task1" << endl;
}
void act4(void)
{
	cout << "\tBegin Task4" << endl;
	cout << "\t\tWorking Task4" << endl;
	OS_MODEL::TerminateTask(OS_MODEL::FindTask("sometask4"));
	cout << "\tEnd Task4" << endl;
}
void act1(void)
{
	cout << "\tBegin Task3" << endl;
	cout << "\t\tWorking Task3" << endl;
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
	OS -> DeclareResource("Resource2", smp);
	smp = OS -> setSemaphore("Sem1", -1, true, "Resource1");

	OS -> DebugPring("OsQueue");
	cout << endl;
	OS->ActivateTask("sometask1");
	
	/*cout << "ResQu" << endl;
	OS -> DebugPring("ResQueue");
	cout << smp;
*/
	cout << "\nCompletedTask" << endl;
	OS -> DebugPring("CompletedTask");
	cout << "\nOsQueue after terminate" << endl;
	OS -> DebugPring("OsQueue");
	return 0;
}
