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
from matplotlib.colors import Normalize
from load_cfg import load_cfg
import os
import matplotlib.image as mpimg

# loading parameter file
cfg = load_cfg('../RL_NSE/config.cfg')
a = cfg.a
b = cfg.b
i_max = cfg.i_max
j_max = cfg.j_max
m = cfg.shape_in_box

counter_max = int((len(os.listdir('../RL_NSE/outputs/')) - 1)/3 - 1)
t = np.genfromtxt ('../RL_NSE/outputs/t_final.csv', delimiter=",")
s = str(t[-1])
t_dec = len(s[s.rfind('.'):]) - 1

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

# finding pressure and velocity min and max
P_min = 0
P_max = 0
speed_min = 0
speed_max = 0
for i in range(1, counter_max+1):
    U, V, P = load_and_adjust(i, U, V, P)
    speed = np.sqrt(U**2 + V**2)
    P_min = np.min([P_min, np.min(P)])
    P_max = np.max([P_max, np.max(P)])
    speed_min = np.min([speed_min, np.min(speed)])
    speed_max = np.max([speed_max, np.max(speed)])
norm_s = Normalize(speed_min, speed_max)
norm_b = Normalize(P_min, P_max)
    
U, V, P = load_and_adjust(1, U, V, P)

speed = np.sqrt(U**2 + V**2)
# lw = 5*speed/np.max(speed)

# plotting
fig, ax = plt.subplots(figsize=(6,4))
stream = ax.streamplot(X, Y, U, V, color=speed, density=2, cmap='gray', norm=norm_s)
background = ax.imshow(P, extent=[0,a,0,b], origin='lower', norm=norm_b)
if m != 0:
    mask = ax.imshow(mpimg.imread(f'../RL_NSE/shapes/{m}.png'), extent=[0,a,0,b], origin='lower', cmap='gray')
cbar_s = fig.colorbar(stream.lines, ax=ax, label=r'$\sqrt{u^2 + v^2}$', orientation='vertical', pad=-0.05)
cbar_b = fig.colorbar(background, ax=ax, label=r'$p$', orientation='vertical', pad=0.13)
cbar_b.ax.yaxis.set_ticks_position("left")
cbar_b.ax.yaxis.set_label_position("left")
cbar_s.formatter.set_powerlimits((0, 0))
cbar_b.formatter.set_powerlimits((0, 0))
text = ax.text(1.0, 1.1, f't: {t[0]}/{t[-1]}', transform=ax.transAxes)
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
ax.set_xlim(0,a)
ax.set_ylim(b,0)
ax.xaxis.tick_top()
ax.xaxis.set_label_position('top')
fig.tight_layout()

def animation_frame(frame, X, Y, U, V, P, t, a, b, m):
    # Clear lines, arrowheads and colorbar
    global cbar_s, cbar_b, background, mask
    cbar_s.remove()
    cbar_b.remove()
    background.remove()
    if m != 0:
        mask.remove()
    for artist in ax.get_children():
        if isinstance(artist, FancyArrowPatch):
            artist.remove()
        if isinstance(artist, LineCollection):
            artist.remove()
    # update frame
    U, V, P = load_and_adjust(frame, U, V, P)
    speed = np.sqrt(U**2 + V**2)
    # lw = 5*speed/np.max(speed)
    stream = ax.streamplot(X, Y, U, V, color=speed, density=2, cmap='gray', norm=norm_s)
    background = ax.imshow(P, extent=[0,a,0,b], origin='lower', norm=norm_b)
    if m != 0:
        mask = ax.imshow(mpimg.imread(f'../RL_NSE/shapes/{m}.png'), extent=[0,a,0,b], origin='lower', cmap='gray')
    cbar_s = fig.colorbar(stream.lines, ax=ax, label=r'$\sqrt{u^2 + v^2}$', orientation='vertical', pad=-0.001)
    cbar_b = fig.colorbar(background, ax=ax, label=r'$p$', orientation='vertical', pad=0.13)
    cbar_b.ax.yaxis.set_ticks_position("left")
    cbar_b.ax.yaxis.set_label_position("left")
    cbar_s.formatter.set_powerlimits((0, 0))
    cbar_b.formatter.set_powerlimits((0, 0))
    text.set_text(f'time: {t[int(frame-1)]:.{t_dec}f} / {t[-1]}')
    return stream, cbar_s, cbar_b, background

animation = FuncAnimation(fig, func=animation_frame, frames=np.arange(1,counter_max+1,1), interval=int(1000*t[-1]/counter_max), fargs=(X, Y, U, V, P, t, a, b, m)) # interval=2*dt*1000
animation.save('../RL_NSE/plots/anim.mp4', dpi=200)
plt.show()

