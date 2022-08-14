#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 20:09:54 2022

@author: lars
"""

# importing libraries
import numpy as np
from localreg import localreg

# initializing parameters
a = 1
b = 1
degree = 1
radius = 0.01

# choosing u output file to analyze
path_to_file = '../RL_NSE/results/lid_driven_cavity_257_Re1000/outputs0/u_final.csv'

# loading u array from file
u = np.genfromtxt(path_to_file, delimiter=',')

# determining i_max and j_max from u array
i_max = np.shape(u)[0] - 2
j_max = np.shape(u)[1] - 1

# calculatung spatial discretization
dx = a/i_max
dy = b/j_max

# creating array for independet variables (x,y) in correct shape
x = np.arange(0, 1+dx, dx)
y = np.arange(0, 1+2*dy, dy) - dy/2
xy = np.zeros(((i_max+1)*(j_max+2),2))
j = -1
for i in range((i_max+1)*(j_max+2)):
    if i%(j_max+2) == 0:
        j += 1
    xy[i,0] = x[j]
    xy[i,1] = y[i%(j_max+2)]
    
# reshaping u array
u_r = np.array([])
for i in range(i_max+1):
    u_r = np.hstack((u_r, u[:,i]))
    
# initializing points of interest from Ghia et al. and preparing them in the correct shape
y0 = 1 - np.array([1.00000, 0.9766, 0.9688, 0.9609, 0.9531, 0.8516, 0.7344, 0.6172, 0.5000, 0.4531, 0.2813, 0.1719, 0.1016, 0.0703, 0.0625, 0.0547, 0.0000])
x0 = np.ones(np.shape(y0))*0.5
xy0 = np.vstack((x0, y0)).T

# local regression
z = localreg(xy, u_r, xy0, degree=degree, radius=radius)

# output
for arg, val in enumerate(z):
    print('%.5f' % val)
