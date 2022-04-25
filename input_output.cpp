#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
using namespace std;
using namespace libconfig;

int load_config(int *a, int *b, int *i_max, int *j_max, int *boundary_condition)
{   
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("../RL_NSE/config.cfg");
    }
    catch(const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    // Getting parameters from file
    try
    {
        *a = cfg.lookup("a");
        *b = cfg. lookup("b");
        *i_max = cfg. lookup("i_max");
        *j_max = cfg. lookup("j_max");
        *boundary_condition = cfg. lookup("boundary_condition");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "One or more settings are missing in the configuration file." << endl;
    }

    return(EXIT_SUCCESS);
}
