import numpy as np
import matplotlib.pyplot as plt
from load_cfg import load_cfg
import sympy as sy

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
numRes_Arr = [u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy]

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
analytRes_Arr_temp = [U, V, D2UDX2, D2UDY2, DU2DX, DUVDY, D2VDX2, D2VDY2, DUVDX, DV2DY]
analytRes_Arr = []
#turn sympy expressions into callable functions
for k in range(len(analytRes_Arr_temp)):
    analytRes_Arr_temp[k] = sy.lambdify([X,Y], analytRes_Arr_temp[k], "numpy")
    temp = np.zeros((len(x), len(y)))
    for i in range(len(x)):
        for j in range(len(y)):
            temp[i,j] = analytRes_Arr_temp[k](x[i], y[j])
    analytRes_Arr.append(temp)


fig, ax = plt.subplots(len(numRes_Arr), 2, figsize= (7, (len(numRes_Arr)/2) * 7))

for i in range(len(numRes_Arr)):
    ax[i][0].pcolormesh(x, y, numRes_Arr[i])
    ax[i][1].pcolormesh(x, y, analytRes_Arr[i])

#for i in range(len(numRes_Arr)):
#    for j in range(2):\
        #ax[i][j].set(xlabel='x', ylabel='y')

#ax[0][0].set(title = 'Numerical Solution')
#ax[0][1].set(title = 'Analytical Solution')
fig.tight_layout()
fig.savefig('../testing_derivatives/plots/comparison.png', dpi=200)
plt.show()
