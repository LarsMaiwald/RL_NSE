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

# loading parameter file
cfg = load_cfg('../RL_NSE/config.cfg')
a = cfg.a
b = cfg.b
i_max = cfg.i_max
j_max = cfg.j_max
m = cfg.shape_in_box

t = np.genfromtxt('../RL_NSE/outputs/t_final.csv', delimiter=',')

# loading arrays
u = np.genfromtxt('../RL_NSE/outputs/u_final.csv', delimiter=',')
v = np.genfromtxt('../RL_NSE/outputs/v_final.csv', delimiter=',')
p = np.genfromtxt('../RL_NSE/outputs/p_final.csv', delimiter=',')

# initializing the grid and adjusting stagered grid with averaging
X, Y = np.meshgrid(np.linspace(0, a, i_max), np.linspace(0, b, j_max))
# the order of indexing is swapped here in comparison to the c++ code!!!
U = np.empty((j_max, i_max))
V = np.empty((j_max, i_max))
for i in range(i_max):
    for j in range(j_max):
        U[j][i] = (u[j+1][i] + u[j+1][i+1])/2
        V[j][i] = (v[j][i+1] + v[j+1][i+1])/2
P = p[1:-1, 1:-1]

speed = np.sqrt(U**2 + V**2)
# lw = 5*speed/np.max(speed) # remove that line

# plotting
fig, ax = plt.subplots(figsize=(a*6/b,4))
stream = ax.streamplot(X, Y, U, V, color=speed, density=2, cmap='gray')
background = ax.imshow(P, extent=[0,a,0,b], origin='lower')
if m != 0:
    mask = ax.imshow(mpimg.imread(f'../RL_NSE/shapes/{m}.png'), extent=[0,a,0,b], origin='lower', cmap='gray')
cbar_s = fig.colorbar(stream.lines, ax=ax, label=r'$\sqrt{u^2 + v^2}$', orientation='vertical', pad=0.15**(a/b), fraction=0.047*a/b)
cbar_b = fig.colorbar(background, ax=ax, label=r'$p$', orientation='vertical', pad=0.1*b/a, fraction=0.047*a/b)
# cbar_b.ax.yaxis.set_ticks_position("left")
# cbar_b.ax.yaxis.set_label_position("left")
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
fig.savefig('../RL_NSE/plots/streamplot.png', dpi=200)
plt.show()