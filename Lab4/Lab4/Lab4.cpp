#include "Interface.h"
#include <ctime>
using namespace std;
int main()
{
    srand(time(NULL));
    Interface iface;
    iface.console_interface();

    return 0;
}
