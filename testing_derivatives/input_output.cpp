#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <fstream>
#include <string>
#include "Grid.h"
using namespace std;
using namespace libconfig;


// Loading parameter file using libconfig
int load_config(int i_max, int j_max, float x_min, float x_max, float y_min, float y_max)
{
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("../testing_derivatives/config.cfg");
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
        i_max = cfg. lookup("i_max");
        j_max = cfg. lookup("j_max");
        x_min = cfg. lookup("x_min");
        x_max = cfg.lookup("x_max");
        y_min = cfg. lookup("y_min");
        y_max = cfg.lookup("y_max");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "One or more settings are missing in the configuration file." << "\n";
    }

    return(EXIT_SUCCESS);
}

// Writing grid to file
void grid2file(Grid &u, string filename)
{
    ofstream file (filename);
    if (file.is_open())
    {
        for (int i = 0; i < u.i_max + u.i_g; i++) {
            for (int j = 0; j < u.j_max + u.j_g; j++) {
                file << u.grid[i][j];
                if (j < u.j_max + u.j_g - 1)
                {
                     file << ",";
                }
            }
            file << "\n";
        }
        file.close();
    }
    else cout << "Unable to open file";
    // to import the generated file in python use:
    // csv = np.genfromtxt ('u.csv', delimiter=",")
}

void array2file(float u[], int i_max, string filename)
{
    ofstream file (filename);
    if (file.is_open())
    {
        for (int i = 0; i < i_max + 2; i++) {
          file << u[i];
          file << ",";
        }
        file.close();
    }
    else cout << "Unable to open file";
    // to import the generated file in python use:
    // csv = np.genfromtxt ('u.csv', delimiter=",")
}
