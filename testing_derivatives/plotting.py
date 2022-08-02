import numpy as np
import matplotlib.pyplot as plt
from load_cfg import load_cfg
import sympy as sy
import os

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

#put into Array for Plotting
numRes_Arr = [u, v, d2udx2, d2udy2, d2vdx2, d2vdy2, du2dx, dv2dy, duvdx, duvdy]

#calculate analytical derivative using sympy
X = sy.symbols('X')
Y = sy.symbols('Y')
U = 2*sy.cos(X)+ 3*sy.sin(Y)
V = (X**2) * (Y**2)
D2UDX2 = sy.diff(U, X, X)
D2UDY2 = sy.diff(U, Y, Y)
DU2DX = sy.diff(U**2, X)
DUVDY = sy.diff(U*V, Y)
D2VDX2 = sy.diff(V, X, X)
D2VDY2 = sy.diff(V, Y, Y)
DUVDX = sy.diff(U*V, X)
DV2DY = sy.diff(V**2, Y)

#put into Array for Plotting
analytRes_Arr_temp = [U, V, D2UDX2, D2UDY2, D2VDX2, D2VDY2, DU2DX, DV2DY, DUVDX, DUVDY]
analytRes_Arr = []
strRes_Arr = [r'$u$', r'$v$', r'$\frac{\partial^2 u}{\partial x^2}$', r'$\frac{\partial^2 u}{\partial y^2}$', r'$\frac{\partial^2 v}{\partial x^2}$', r'$\frac{\partial^2 v}{\partial y^2}$', r'$\frac{\partial u^2}{\partial x}$', r'$\frac{\partial v^2}{\partial y}$', r'$\frac{\partial uv}{\partial x}$', r'$\frac{\partial uv}{\partial y}$']
#turn sympy expressions into callable functions
for k in range(len(analytRes_Arr_temp)):
    analytRes_Arr_temp[k] = sy.lambdify([X,Y], analytRes_Arr_temp[k], "numpy")
    temp = np.zeros((len(x), len(y)))
    for i in range(len(x)):
        for j in range(len(y)):
            temp[i,j] = analytRes_Arr_temp[k](x[i], y[j])
    analytRes_Arr.append(temp)


outpath = "../testing_derivatives/plots"

fig, ax = plt.subplots(1, 2, figsize= (7, 3.5))        # generate figure with axes
ax[0].pcolormesh(x, y, numRes_Arr[0])    # initialize plot
ax[1].pcolormesh(x, y, analytRes_Arr[0])
for i in range(2):
    ax[i].set_xlabel('x')
    ax[i].set_ylabel('y')
fig.suptitle(strRes_Arr[0], fontsize=14)
fig.tight_layout()
plt.draw()
fig.savefig(os.path.join(outpath,"comparison_0.png"))

for i in range(1, len(numRes_Arr)):
    ax[0].pcolormesh(x, y, numRes_Arr[i])
    ax[1].pcolormesh(x, y, analytRes_Arr[i])
    fig.suptitle(strRes_Arr[i], fontsize=14)
    fig.tight_layout()
    plt.draw()
    fig.savefig(os.path.join(outpath,"comparison_{0}.png".format(i)), dpi=200)
