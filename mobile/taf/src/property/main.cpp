#include "PropertyServer.h"
#include <iostream>

using namespace std;

TC_Config* g_pconf;

/**
 * @param argc
 * @param argv
 *
 * @return int
 */
int main( int argc, char* argv[] )
{
    try
    {
        PropertyServer app;
        g_pconf = &app.getConfig();
        app.main( argc, argv );
        LOG->debug() << "main init succ" << endl;
        app.waitForShutdown();
    }
    catch ( exception& ex )
    {
        cout << ex.what() << endl;
    }

    return 0;
}


