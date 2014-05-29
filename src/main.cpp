#include "../include/os.hpp"
using namespace std;

void act(void)
{
	cout << "LAX" <<endl ;
}

void act4(void)
{
	cout << "Task3" << endl;
}

void act1(void)
{
	cout << "\nTest Ended" << endl;
}

void act2(void)
{
	cout << "\nLALA" << endl;
}

int main(int argc, char *argv[])
{
	OS_MODEL *OS = new OS_MODEL();
	OS -> DeclareTask("sometask1", 2, act);
	OS -> DeclareTask("sometask2", 5, act2);
	OS -> DeclareTask("sometask3", 7, act1);
	OS -> DeclareTask("sometask4", 12, act4);
	OS->Schedule();
	OS->PringQueue();
	cout << endl;
	OS->ActivateTask("sometask1");

	return 0;
}
