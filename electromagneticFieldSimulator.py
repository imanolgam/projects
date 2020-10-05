import numpy as np
import matplotlib.pyplot as plt
import math
plt.style.use("bmh")
# function for magnetic field


def campo_electrico(X, Y, q, q_loc):
    # Update coordinate arrays
    X_new = X-q_loc[0]
    Y_new = Y-q_loc[1]
    #Coulomb
    k_e = 8987539422

    # Square radius and radius matrices
    r_2 = X_new**2+Y_new**2
    r = r_2**(1/2)

    # Matrix 1/r for the components
    r_1_2 = r_2**-1

    # Trigonometric relation for angles
    rel = np.divide(X_new, r)
    angles = np.angle(X_new+Y_new*1j) 
    mcos = np.cos(angles)
    msin = np.sin(angles)
    # Electric field components
    Ex = k_e*q*r_1_2*mcos
    Ey = k_e*q*r_1_2*msin

    return Ex, Ey

def Barra_electrica(X, Y, q, minX, maxX, y, N):
    q = q

    # Define coordinates, x is a line space with all the coordinates
    qloc_x_range = np.linspace(minX, maxX, N)
    qloc_y = y

    # Inicializar campo electrico
    Ex = np.zeros((len(X), len(X[0])))
    Ey = np.zeros((len(X), len(X[0])))

    for i, qloc_x in enumerate(qloc_x_range):

        this_Ex, this_Ey = campo_electrico(X, Y, q, [qloc_x, qloc_y])

        # Update Ex and Ey values
        Ex = Ex + this_Ex
        Ey = Ey + this_Ey

    return Ex, Ey
def main():
    # Initial parameters
    #N = 20
    grid_min = -10
    grid_max = 10
    
    N = abs(grid_min)+ abs(grid_max)

    x = np.linspace(grid_min, grid_max, N)
    y = np.linspace(grid_min, grid_max, N)

    # Create matrices of vectorial coordinates
    X, Y = np.meshgrid(x, y)
    
    minX = -5
    maxX = 5

    # charge 1
    q = -10*math.exp(-6)
    qloc_y = 5
    # charge 2
    q2 = 15*math.exp(-6)
    qloc_y2 = -5

    # Parameters
    total_unidades = abs(minX) + abs(maxX)
    carga_por_unidad = 30

    Nb = carga_por_unidad * total_unidades

    Ex1, Ey1 = Barra_electrica(X, Y, q, minX, maxX, qloc_y, Nb)
    Ex2, Ey2 = Barra_electrica(X, Y, q2, minX, maxX, qloc_y2, Nb)

    Ex = Ex1 + Ex2
    Ey = Ey1 + Ey2
    mags = (Ex**2+Ey**2)**(1/2)

    # Unitary vectors
    Ex_unit = np.divide(Ex, mags)
    Ey_unit = np.divide(Ey, mags)

    fig, ax = plt.subplots(figsize=(7, 7))
    # Create vectorial field
    ax.quiver(X, Y, Ex_unit, Ey_unit)

    # Draw point charge
    for i, qloc_x in enumerate(np.linspace(minX, maxX, 1000)):
        ax.scatter(qloc_x, qloc_y, c='blue', s=1000)
        ax.scatter(qloc_x, qloc_y2, c='red', s=1000)

    ax.axis([grid_min, grid_max, grid_min, grid_max])
    ax.set_aspect('equal', 'box')

    plt.show()


main()
