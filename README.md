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
		u_in = 1.0; // inflow velocity in x-direction (i-axis) // float
		v_in = 0.0; // inflow velocitiy in y-direction (j-axis) // float

		// additional parameters
		Re = 1e3; // Reynolds number // float
		tau = 0.5; // safety factor for time stepping (in 0 to 1) // float
		g_x = 0.0; // acceleration in x-direction due to gravitiy // float
		g_y = 9.801; // acceleration in y-direction due to gravitiy // float
		w = 1.2; // SOR relaxation factor (w \in (1,2]) // flaot
		eps = 0.1; // error tolerance factor // float
		norm = 0; // error tolerence norm, 0 --> max_norm, 1 --> L2_norm // int
		pre = 0.1; // (1 + pre) is the prefactor when computing gamma // float
		t_final = 50.0; // time for the system to evolve // float
		chi = 0.08; // error tolerance shift from 0 // flaot
		save_step = 200; // step between saved files // int
		shape_in_box = 0; // 0 --> no shape in box, 1 --> sphere, 2 --> airfoil // int
		in_c = 0; // periodically change inflow velocity using cosine factor (0 --> False, 1 --> True) // int
		lsl = 0; // lower speed limit in plotting lsl*speed_mean (all velocities closer to zero are set to zero) // float
		SOR_max_iter = 1e1; // code exits when SOR takes longer than int(SOR_iter*i_max*j_max) iterations // float
		fix_color = 0; // 1 --> keep colorbars fixed, 0 --> adjust colorbars with every frame // int
		output_num = 0; // number added to the output folder and streamplot/streamanimation (Attention: If output_num is not 0 the folder needs to be created manually.) // int

	- run ./run in a terminal or try to run the file as administrator from your GUI
