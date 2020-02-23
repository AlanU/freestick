#include "USB/platform/MacOSX/FSMacUtil.h"
#include <unordered_map>

std::unordered_map<std::string,int> connectedContorllers;
void connectKnownControllers(std::string & name)
{
    connectedContorllers[name]++;
}

void dissconnectKnownControllers(std::string & name)
{
    connectedContorllers[name]-- ;
    if(connectedContorllers[name] <= 0 )
    {
        connectedContorllers.erase(name);
    }
}

bool containsControler(std::string & name)
{
    return connectedContorllers.find(name) != connectedContorllers.end();
}
