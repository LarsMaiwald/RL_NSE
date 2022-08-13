import numpy as np
import matplotlib.pyplot as plt
from load_cfg import load_cfg
import sympy as sy
import os
from tqdm import tqdm
from matplotlib.colors import Normalize
import matplotlib.cm as cm

# Loading parameter file
cfg = load_cfg('../testing_derivatives/config.cfg')
i_max = cfg.i_max
j_max = cfg.j_max
x_min = cfg.x_min
x_max = cfg.x_max
y_min = cfg.y_min
y_max = cfg.y_max

# Loading arrays calculated in C++
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

# Put into array for plotting
numRes_Arr = [u, v, d2udx2, d2udy2, d2vdx2, d2vdy2, du2dx, dv2dy, duvdx, duvdy]

# Calculate analytical derivative using sympy
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

# Put into array for plotting
analytRes_Arr_temp = [U, V, D2UDX2, D2UDY2, D2VDX2, D2VDY2, DU2DX, DV2DY, DUVDX, DUVDY]
analytRes_Arr = []
strRes_Arr = [r'$u$', r'$v$', r'$\frac{\partial^2 u}{\partial x^2}$', r'$\frac{\partial^2 u}{\partial y^2}$', r'$\frac{\partial^2 v}{\partial x^2}$', r'$\frac{\partial^2 v}{\partial y^2}$', r'$\frac{\partial u^2}{\partial x}$', r'$\frac{\partial v^2}{\partial y}$', r'$\frac{\partial uv}{\partial x}$', r'$\frac{\partial uv}{\partial y}$']

# Turn sympy expressions into callable functions
for k in range(len(analytRes_Arr_temp)):
    analytRes_Arr_temp[k] = sy.lambdify([X,Y], analytRes_Arr_temp[k], "numpy")
    temp = np.zeros((len(x), len(y)))
    for i in range(len(x)):
        for j in range(len(y)):
            temp[i,j] = analytRes_Arr_temp[k](x[i], y[j])
    analytRes_Arr.append(temp)

# Set path for saving plots
outpath = "../testing_derivatives/plots"

# Initialize figure
fig, ax = plt.subplots(1, 2, figsize= (9, 3.5))        # generate figure with axes
bax = ax[0].inset_axes([1.1, 0, 0.05, 1], transform=ax[0].transAxes)
bax.axis('off')
cax = ax[1].inset_axes([1.1, 0, 0.05, 1], transform=ax[1].transAxes) # Colorbar is held by

for i in tqdm(range(0, len(numRes_Arr))):

    # Calculate max and min for colormap nomalization
    cax.clear()
    maxArr = []
    maxArr.append(np.amax(numRes_Arr[i]))
    maxArr.append(np.amax(analytRes_Arr[i]))
    minArr = []
    minArr.append(np.amin(numRes_Arr[i]))
    minArr.append(np.amin(analytRes_Arr[i]))
    cbmax = max(maxArr)
    cbmin = min(minArr)

    normalizer=Normalize(cbmin,cbmax)
    im=cm.ScalarMappable(norm=normalizer)

    # Drawing of colormesh-plots
    ax[0].pcolormesh(x, y, numRes_Arr[i], norm=normalizer)
    ax[1].pcolormesh(x, y, analytRes_Arr[i], norm=normalizer)
    ax[0].set_title('Numerical solution')
    ax[1].set_title('Analytical solution')
    fig.suptitle(strRes_Arr[i], fontsize=14)
    cb = fig.colorbar(im, ax=ax, cax=cax)
    plt.tight_layout()
    plt.draw()

    # Saving the figure as png
    fig.savefig(os.path.join(outpath,"comparison_{0}.png".format(i)), dpi=200)
