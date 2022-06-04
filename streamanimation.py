#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jun  4 12:50:08 2022

@author: lars
"""

# importing libraries
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.patches import FancyArrowPatch
from matplotlib.collections import LineCollection
from matplotlib.patches import Rectangle
from load_cfg import load_cfg
import os

# loading parameter file
cfg = load_cfg('../RL_NSE/config.cfg')
a = cfg.a
b = cfg.b
i_max = cfg.i_max
j_max = cfg.j_max

counter_max = len(os.listdir('../RL_NSE/outputs/'))/3 - 1

# initializing the grid
X, Y = np.meshgrid(np.linspace(0, a, i_max), np.linspace(0, b, j_max))
U = np.empty((i_max, j_max))
V = np.empty((i_max, j_max))
P = np.empty((i_max, j_max))

def load_and_adjust(counter, U, V, P):
    # loading arrays
    counter = int(counter)
    u = np.genfromtxt (f'../RL_NSE/outputs/u{counter}.csv', delimiter=",")
    v = np.genfromtxt (f'../RL_NSE/outputs/v{counter}.csv', delimiter=",")
    p = np.genfromtxt (f'../RL_NSE/outputs/p{counter}.csv', delimiter=",")
    
    # adjusting stagered grid with averaging
    for i in range(i_max):
        for j in range(j_max):
            U[i][j] = (u[i+1][j] + u[i+1][j+1])/2
            V[i][j] = (v[i][j+1] + v[i+1][j+1])/2
    P = p[1:-1, 1:-1]
    return U, V, P
    
U, V, P = load_and_adjust(1, U, V, P)

# plotting
fig, ax = plt.subplots()
stream = ax.streamplot(X, Y, U, V, color=P, density=2)
cbar = fig.colorbar(stream.lines, ax=ax, label=r'$p$', orientation='vertical')
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
ax.set_ylim(b,0)
ax.xaxis.tick_top()
ax.xaxis.set_label_position('top')
fig.tight_layout()

def animation_frame(frame, X, Y, U, V, P):
    # Clear lines, arrowheads and colorbar
    global cbar
    cbar.remove()
    for artist in ax.get_children():
        if isinstance(artist, FancyArrowPatch):
            artist.remove()
        if isinstance(artist, LineCollection):
            artist.remove()
    # update frame
    U, V, P = load_and_adjust(frame, U, V, P)
    stream = ax.streamplot(X, Y, U, V, color=P, density=2)
    cbar = fig.colorbar(stream.lines, ax=ax, label=r'$p$', orientation='vertical')
    return stream, cbar

animation = FuncAnimation(fig, func=animation_frame, frames=np.arange(1,counter_max+1,1), interval=200, fargs=(X, Y, U, V, P)) # interval=2*dt*1000
animation.save('../RL_NSE/plots/anim.mp4', dpi=200)
plt.show()

