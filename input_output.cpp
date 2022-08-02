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
int load_config(float &a, float &b, int &i_max, int &j_max, float &u_in, float &v_in, float &Re, float &tau, float &g_x, float &g_y, float &w, float &eps, int &norm, float &pre, float &t_final, float &chi, int &save_step, int &shape_in_box, int bc[4], bool &in_c)
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
        u_in = cfg.lookup("u_in");
        v_in = cfg.lookup("v_in");
        Re = cfg.lookup("Re");
        tau = cfg.lookup("tau");
        g_x = cfg.lookup("g_x");
        g_y = cfg.lookup("g_y");
        w = cfg.lookup("w");
        eps = cfg.lookup("eps");
        norm = cfg.lookup("norm");
        pre = cfg.lookup("pre");
        t_final = cfg.lookup("t_final");
        chi = cfg.lookup("chi");
        save_step = cfg.lookup("save_step");
        shape_in_box = cfg.lookup("shape_in_box");
        bc[0] = cfg.lookup("bc0");
        bc[1] = cfg.lookup("bc1");
        bc[2] = cfg.lookup("bc2");
        bc[3] = cfg.lookup("bc3");
        in_c = cfg.lookup("in_c");
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
        for (int j = 0; j < u.j_max + u.j_g; j++) {
            for (int i = 0; i < u.i_max + u.i_g; i++) {
                file << u.grid[i][j];
                if (i < u.i_max + u.i_g - 1)
                {
                     file << ",";
                }
            }
            file << "\n";
        }
        file.close();
    }
    else cout << "Unable to open file " << filename << "\n";
    // to import the generated file in python use:
    // csv = np.genfromtxt ('u.csv', delimiter=",")
}

void time2file(float t, string filename)
{
    ofstream file (filename, std::ios_base::app);
    if (file.is_open())
    {
        file << t << "\n";
        file.close();
    }
    else cout << "Unable to open file" << filename << "\n";
}

void file2grid(Grid &u, string filename)
{
    int c_i = 0;
    int c_j = 0;
    ifstream file;
    file.open(filename);
    while(file.good())
    {
        string line;
        getline(file, line, ',');
        u.grid[c_i][c_j] = stoi(line);
        c_i += 1;
        if(c_i == u.i_max-1)
        {
            c_i = 0;
            c_j += 1;
        }
    }
    file.close();
}
