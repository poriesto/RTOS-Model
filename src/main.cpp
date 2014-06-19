#include "../include/os.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	OS_MODEL *OS = new OS_MODEL();
	
	OS -> Start_OS();
	
	OS -> DebugPring("OsQueue");
	cout << endl;
	OS->ActivateTask("sometask1");
	
	cout << "ResQu" << endl;
	OS -> DebugPring("ResQueue");

	cout << "\nCompletedTask" << endl;
	OS -> DebugPring("CompletedTask");
	cout << "\nOsQueue after terminate" << endl;
	OS -> DebugPring("OsQueue");
	return 0;
}
