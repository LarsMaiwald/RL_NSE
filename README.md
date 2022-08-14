# Research Lab: Numerical Solution of the Navier-Stokes Equations (NSE)

## The program
This is a numerical solver for the Navier stokes equation in a rectangular domain [0,a]x[0,b]. The numerical solver uses staggered grids and the SOR-relaxation scheme. The program outputs .csv files of the velocity and pressure and is able to create streamplots and animations.
This code was developed as part of the Research Lab module in the M.Sc. Physik at the FSU Jena and is based on a manual by Prof. Bernd Brügmann.

## Requirements
- python 3 with libraries numpy, matplolib, os, io, libconf, imageio, localreg
- c++ compiler and cmake

## Usage
- choose required parameters in config.cfg
	- simulation domain
		- a // length of domain edge in x-direction (a >= b for proper plotting to work)
		- b // length of domain edge y-direction 
		- i_max // number of cells in x-direction
		- j_max // number of cells in y-direction

	- boundary conditions (0 --> No-Slip condition, 1 --> Outflow condition, 2 --> Inflow condition)
		- bc0 // bc for northern edge
		- bc1 // bc for western edge
		- bc2 // bc for southern edge
		- bc3 // bc for eastern edge


	- boundary condition parameters
	    - u_in // inflow velocity in x-direction 
	    - v_in // inflow velocitiy in y-direction

	- additional parameters
	    - Re // Reynolds number
	    - tau // safety factor for time stepping (in 0 to 1)
	    - g_x // acceleration in x-direction due to gravity 
	    - g_y // acceleration in y-direction due to gravity
	    - w // SOR relaxation factor (w \in (1,2])
	    - eps // error tolerance factor 
	    - norm // choose error tolerance norm
	    - pre // (1 + pre) is the prefactor when computing gamma
	    - t_final // time for the system to evolve
	    - chi // error tolerance shift from 0 if norm(p_init) = 0
	    - save_step // step between saved files
	    - shape_in_box // choose a shape as obstacle
	    - in_c // activate periodical changing inflow velocity using cosine factor 
	    - lsl // lower speed limit in plotting
	    - SOR_max_iter = 1e1; // set maximum number of SOR loops before cancellation
	    - fix_color // decide if colorbars in animation should be fixed for the whole animation  
	    - output_num // number added to the output folder and streamplot/streamanimation

- run ./run in a terminal or try to run the file as administrator from your GUI
    - creates make fields and compiles the C++ program using make
    - creates outputs0 and plots folder if non-existent
    - cleans outputs0 folder
    - runs the C++ program
    - runs python programs creating the animation

## Results
The results folder contains simulations for a variety of systems. In each case animations of the time evolution with fixed and dynamic colorbars, a streamplot of the final state, the output files of the final state and the config file for the simulation are available. The output folder does not contain any time-steps beside the final state to reduce the needed storage size.
