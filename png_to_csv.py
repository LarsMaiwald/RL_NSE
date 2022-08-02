#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul 28 14:53:56 2022

@author: lars
"""

import imageio as iio
import numpy as np
from load_cfg import load_cfg

cfg = load_cfg('../RL_NSE/config.cfg')
filename = cfg.shape_in_box
if filename != 0:
    img = iio.v2.imread(f'shapes/{filename}.png')[:,:,3]
    np.savetxt(f'shapes/{filename}.csv', img, delimiter=',', fmt='%.d')
    print(f'Converted shape {filename} from .png to .csv.')
else:
    print('No shape selected in parameter file.')