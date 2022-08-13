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

# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re100_done/outputs*/u_final.csv'
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re400_done/outputs*/u_final.csv'
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re1000_done/outputs*/u_final.csv'
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re3200_done/outputs*/u_final.csv'
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re5000_done/outputs*/u_final.csv'
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re7500_done/outputs*/u_final.csv' # 50
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re7500_again/outputs0/u_final.csv' # 100
# path_to_file = '../RL_NSE/result_folder_rudi/2022_08_08_01-13_varyingRe/Re10000_done/outputs*/u_final.csv'

path_to_file = '../RL_NSE/results/2022_08_08-16_08-lid_driven_cavity_257_Re100/outputs0/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_09-13_00-lid_driven_cavity_257_Re400/outputs0/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_07-13_48-lid_driven_cavity_257_Re1000/outputs/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_09-13_58-lid_driven_cavity_257_Re3200/outputs0/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_09-14_22-lid_driven_cavity_257_Re5000/outputs1/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_09-16_03-lid_driven_cavity_257_Re7500/outputs0/u_final.csv'
# path_to_file = '../RL_NSE/results/2022_08_09-10_24-lid_driven_cavity_257_Re10000/outputs1/u_final.csv' # 100
# path_to_file = '../RL_NSE/results/2022_08_11-20_04-lid_driven_cavity_257_Re10000/outputs1/u_final.csv' # 150
# path_to_file = '../RL_NSE/results/2022_08_12-14_09-lid_driven_cavity_257_Re10000/outputs0/u_final.csv' # 300

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
