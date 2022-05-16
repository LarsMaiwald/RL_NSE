# Research Lab: Numerical Solution of the Navier-Stokes Equations

## Implementation
Implement the algorithm in the following steps:
- [x] Write the skeleton of the program, which allocates all needed variables and fields, and initializes the fields to zero.
- [x] Implement an output routine for the fields. Initialize u and v with a known function (e.g. u = cos(x) cos(y)) and test the output routine by outputting and plotting the fields.
- [ ] Write the function that computes F and G. To do this, you must implement the derivative stencils (32) through (37). Test the derivative stencils by using them to calculate the derivative of a known function.
- [ ] Implement the pressure calculation using the SOR method. Test this by solving an elliptic equation to which you know the analytic solution. Output your numerical solution and compare it to the analytic solution. Test the method, its convergence and convergence speed for different grid resolutions and relaxation parameters ω.
- [ ] Implement a function to compute the RHS of (41).
- [ ] Lastly, write the time evolution loop. For this, you need a function to set the time step according to the stability criterion. Be careful to potentially absorb a division by zero. You also need to implement the function which computes the new velocity from the new values of F and G and from the new pressure values.

## Algorithm
The following lists all necessary steps for solving the Navier-Stokes equations in the correct order:
- [x] Read in parameters and initialize all variables.
- [ ] Allocate memory for all fields and initialize all fields.
- [ ] Start of the time evolution loop.
- [x] Choose time step δt according to stability condition (26).
- [ ] Fill ghost cells according to boundary conditions.
- [ ] Compute F(n) and G(n) according to (29) and (30).
- [ ] Calculate the RHS of the pressure equation (40).
- [ ] Start of the SOR iteration loop.
  - [ ] Calculate the pressure for all cells according to (42).
  - [ ] Compute the residual (43) and its norm.
  - [ ] If the norm of the residual is small enough, stop the iteration.
- [ ] Compute the new velocity components u(n+1) and v(n+1) according to (21) and (22).
- [ ] Output the relevant fields.

## Questions
- [x] Which are the lowest and highest value for the indices i and j of u and v?
    - u: (i_max+1)x(j_max+2)
    - v: (i_max+2)x(j_max+1)
    - p: (i_max+2)x(j_max+2)
- [ ] Aren't there ghost cells missing for u in x direction and for v in y direction?
- [ ] Does |u_max| really mean abs(max(u))?
