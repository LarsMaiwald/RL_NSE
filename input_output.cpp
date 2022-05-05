#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
using namespace std;
using namespace libconfig;

int load_config(float &a, float &b, int &i_max, int &j_max, int &boundary_condition, float &u_in, float &v_in, float &Re, float &tau, float &g_x, float &g_y)
{   
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("../RL_NSE/config.cfg");
    }
    catch(const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << "\n";
        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << "\n";
        return(EXIT_FAILURE);
    }

    // Getting parameters from file
    try
    {
        a = cfg.lookup("a");
        b = cfg. lookup("b");
        i_max = cfg. lookup("i_max");
        j_max = cfg. lookup("j_max");
        boundary_condition = cfg. lookup("boundary_condition");
        u_in = cfg.lookup("u_in");
        v_in = cfg.lookup("v_in");
        Re = cfg.lookup("Re");
        tau = cfg.lookup("tau");
        g_x = cfg.lookup("g_x");
        g_y = cfg.lookup("g_y");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "One or more settings are missing in the configuration file." << "\n";
    }

    return(EXIT_SUCCESS);
}
