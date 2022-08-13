# Research Lab: Numerical Solution of the Navier-Stokes Equations (NSE)

## The program

This is a numerical solver for the Navier stokes equation in a rectangular domain [0,a]x[0,b]. The numerical solver uses staggered grids and the SOR-relaxation scheme.

## Requirements

	- python with matplotlib and numpy module installed
	- a c++ compiler and cmake

## Usage

	- choose required parameters in config.cfg
		- simulation domain
			- a // length of domain edge in x-direction
			- b // length of domain edge y-direction 
			- i_max // number of cells in x-direction
			- j_max // number of cells in y-direction

		- boundary conditions (0 --> No-Slip condition, 1 --> Outflow condition, 2 --> Inflow condition)
			- bc0 // bc for north edge
			- bc1 // bc for west edge
			- bc2 // bc for south edge
			- bc3 // bc for east edge

		// boundary condition parameters
		u_in = 1.0; // inflow velocity in x-direction (i-axis)
		v_in = 0.0; // inflow velocitiy in y-direction (j-axis)

		// additional parameters
		Re = 7500.0; // Reynolds number
		tau = 0.1; // safety factor for time stepping
		g_x = 0.0; // acceleration in x-direction due to gravitiy
		g_y = 0.0; // acceleration in y-direction due to gravitiy
		w = 1.2; // SOR relaxation factor (w \in (1,2])
		eps = 0.5; // error tolerance factor
		norm = 0; // error tolerence norm, 0 --> max_norm, 1 --> L2_norm
		pre = 0.1; // (1 + pre) is the prefactor when computing gamma
		t_final = 100.0; // time for the system to evolve
		chi = 0.3; // error tolerance shift from 0 (higher value needed when working with orthogonal inflow --> 0.15, otherwise 0.05 should work)
		save_step = 1200; // step between saved files
		shape_in_box = 0; // 0 --> no shape in box, 1 --> shape 1, 2 --> shape 2, …
		in_c = 0; // periodically change inflow velocity using cosine factor
		lsl = 0.1; // lower speed limit in plotting lsl*speed_mean (all smaller velocities are set to zero)
		SOR_max_iter = 1e1; // code exits when SOR takes longer than SOR_iter/(i_max*j_max) iterations
		fix_color = 0; // 1 --> keep colorbars fixed, 0 --> adjust colorbars with every frame
		output_num=0; // add number to folder (standard is 0 and this folder will be created by ./run if other ouput folder are required please make the directory before running)

	- run ./run in a terminal or try to run the file as administrator from your GUI
