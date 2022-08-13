#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May  6 12:55:45 2022

@author: Lars Maiwald
"""

# importing libraries
import io, libconf

# function for libconfig configuration loading from file
def load_cfg(path):
    with io.open(path) as f:
        cfg = libconf.load(f)
    return cfg