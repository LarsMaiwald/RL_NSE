#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May  6 12:31:23 2022

@author: Lars Maiwald
"""

# importing libraries
import numpy as np
import matplotlib.pyplot as plt
from load_cfg import load_cfg
import matplotlib.image as mpimg
from mpl_toolkits.axes_grid1 import make_axes_locatable

# loading parameter file
cfg = load_cfg('../RL_NSE/config.cfg')
a = cfg.a
b = cfg.b
i_max = cfg.i_max
j_max = cfg.j_max
m = cfg.shape_in_box
lsl = cfg.lsl
output_num = cfg.output_num

t = np.genfromtxt(f'../RL_NSE/outputs{output_num}/t_final.csv', delimiter=',')

# loading arrays
u = np.genfromtxt(f'../RL_NSE/outputs{output_num}/u_final.csv', delimiter=',')
v = np.genfromtxt(f'../RL_NSE/outputs{output_num}/v_final.csv', delimiter=',')
p = np.genfromtxt(f'../RL_NSE/outputs{output_num}/p_final.csv', delimiter=',')

# initializing the grid and adjusting stagered grid with averaging
X, Y = np.meshgrid(np.linspace(0, a, i_max), np.linspace(0, b, j_max))
# the order of indexing is swapped here in comparison to the c++ code!!!
U = np.empty((j_max, i_max))
V = np.empty((j_max, i_max))
for i in range(i_max):
    for j in range(j_max):
        U[j][i] = (u[j+1][i] + u[j+1][i+1])/2
        V[j][i] = (v[j][i+1] + v[j+1][i+1])/2
        if lsl != 0 and np.sqrt(U[j][i]**2 + V[j][i]**2) < lsl*np.sqrt(np.mean(U)**2 + np.mean(V)**2):
            U[j][i] = 0
            V[j][i] = 0
P = p[1:-1, 1:-1]

speed = np.sqrt(U**2 + V**2)
# lw = 5*speed/np.max(speed) # remove that line

# plotting
fig, ax = plt.subplots(figsize=(6*(a/b)**0.6,4))
divider = make_axes_locatable(ax)
cax_b = divider.append_axes("right", size=0.2, pad=0.4)
cax_s = divider.append_axes("right", size=0.2, pad=0.7)
stream = ax.streamplot(X, Y, U, V, color=speed, density=2, cmap='gray')
background = ax.imshow(P, extent=[0,a,0,b], origin='lower')
if m != 0:
    mask = ax.imshow(mpimg.imread(f'../RL_NSE/shapes/{m}.png'), extent=[0,a,0,b], origin='lower', cmap='gray')
cbar_s = fig.colorbar(stream.lines, cax=cax_s, label=r'$\sqrt{u^2 + v^2}$', orientation='vertical')
cbar_b = fig.colorbar(background, cax=cax_b, label=r'$p$', orientation='vertical')
cbar_s.formatter.set_powerlimits((0, 0))
cbar_b.formatter.set_powerlimits((0, 0))
text = ax.text(1.1, 1.1, f'time: {t[-1]}', transform=ax.transAxes)
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
ax.set_xlim(0,a)
ax.set_ylim(b,0)
ax.xaxis.tick_top()
ax.xaxis.set_label_position('top')
fig.tight_layout()
fig.savefig(f'../RL_NSE/plots/streamplot{output_num}.png', dpi=200)
plt.show()
