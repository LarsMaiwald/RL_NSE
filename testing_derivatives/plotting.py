import numpy as np
import matplotlib.pyplot as plt
from load_cfg import load_cfg

# loading parameter file
cfg = load_cfg('../testing_derivatives/config.cfg')
i_max = cfg.i_max
j_max = cfg.j_max
x_min = cfg.x_min
x_max = cfg.x_max
y_min = cfg.y_min
y_max = cfg.y_max

# loading arrays
u = np.genfromtxt ('../testing_derivatives/outputs/u.csv', delimiter=",")
v = np.genfromtxt ('../testing_derivatives/outputs/v.csv', delimiter=",")
d2udx2 = np.genfromtxt ('../testing_derivatives/outputs/d2udx2.csv', delimiter=",")
d2udy2 = np.genfromtxt ('../testing_derivatives/outputs/d2udy2.csv', delimiter=",")
du2dx = np.genfromtxt ('../testing_derivatives/outputs/du2dx.csv', delimiter=",")
duvdy = np.genfromtxt ('../testing_derivatives/outputs/duvdy.csv', delimiter=",")
d2vdx2 = np.genfromtxt ('../testing_derivatives/outputs/d2vdx2.csv', delimiter=",")
d2vdy2 = np.genfromtxt ('../testing_derivatives/outputs/d2vdy2.csv', delimiter=",")
duvdx = np.genfromtxt ('../testing_derivatives/outputs/duvdx.csv', delimiter=",")
dv2dy = np.genfromtxt ('../testing_derivatives/outputs/dv2dy.csv', delimiter=",")
x = np.genfromtxt ('../testing_derivatives/outputs/x.csv', delimiter=",")
y = np.genfromtxt ('../testing_derivatives/outputs/y.csv', delimiter=",")

print(x)
