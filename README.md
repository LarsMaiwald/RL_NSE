# Research Lab: Numerical Solution of the Navier-Stokes Equations

The following lists all necessary steps for solving the Navier-Stokes equations in the correct order:
- [ ] Read in parameters and initialize all variables.
- [ ] Allocate memory for all fields and initialize all fields.
- [ ] Start of the time evolution loop.
- [ ] Choose time step δt according to stability condition (26).
- [ ] Fill ghost cells according to boundary conditions.
- [ ] Compute F(n) and G(n) according to (29) and (30).
- [ ] Calculate the RHS of the pressure equation (40).
- [ ] Start of the SOR iteration loop.
  - [ ] Calculate the pressure for all cells according to (42).
  - [ ] Compute the residual (43) and its norm.
  - [ ] If the norm of the residual is small enough, stop the iteration.
- [ ] Compute the new velocity components u(n+1) and v(n+1) according to (21) and (22).
- [ ] Output the relevant fields.
