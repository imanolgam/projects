# Iniciativa para automatizar mas la fase 3 del programa de campos magneticos.
# Importar librerias
import numpy as np
import matplotlib.pyplot as plt
import math
plt.style.use("bmh")

# Funcion Importante, ajuste componente Ey


def ajustar_msin(msin, Y):
    for i in range(len(msin)):
        for j in range(len(msin[i])):
            if(Y[i][j] < 0):
                msin[i] = msin[i]*(-1)
    return msin

# funcion para campo electrico


def campo_electrico(X, Y, q, q_loc):
    # Actualizar matrices de coordenadas
    X_new = X-q_loc[0]
    Y_new = Y-q_loc[1]
    # Constante de Coulomb
    k_e = 8987539422

    # Matrices de radio cuadrado y radio
    r_2 = X_new*2+Y_new*2
    r = r_2**(1/2)

    # Matriz 1/r para los componentes
    r_1_2 = r_2**-1

    # Relacion Trigonometrica para angles
    rel = np.divide(X_new, r)
    angles = np.arccos(rel)

    mcos = np.cos(angles)
    msin = np.sin(angles)
    msin = ajustar_msin(msin, Y_new)

    # Componentes del campo electrico
    Ex = k_e*q*r_1_2*mcos
    Ey = k_e*q*r_1_2*msin

    return Ex, Ey


# Esto no sirve; preguntar a edu de los linspace
"""
def parametros_init():
    # Parametros Iniciales
    N = int(input("Ingrese el numero de intervalos"))
    grid_min = int(input("Ingrese el limite inferior"))
    grid_max = int(input("Ingrese el limite superior"))
    return N, grid_min, grid_max
"""


def coordenadas_carga(grid_min, grid_max):
    x = int(input("x:"))
    y = int(input("y:"))
    q_loc = [x, y]

    return q_loc


def carga_valor():
    c = float(input("Ingrese la carga (solo el valor sin elevar)"))
    x = float(
        input("Ingrese el orden de magnitud al que quiera elevar el exponencial"))
    q = c*math.exp(x)
    return q


def main():
    print("Campos electricos")
    #N, grid_min, grid_max = parametros_init()
    N = 21
    grid_min = -10
    grid_max = 10

    # Incializar espacios lineales

    x = np.linspace(grid_min, grid_max, N)
    y = np.linspace(grid_min, grid_max, N)

    # Crear Matrices de coordenadas vectoriales
    X, Y = np.meshgrid(x, y)

    # Cargas Experimentales
    q = carga_valor()
    q_loc = coordenadas_carga(grid_min, grid_max)

    q2 = carga_valor()
    q2_loc = coordenadas_carga(grid_min, grid_max)

    # Componentes de la Carga
    Ex, Ey = campo_electrico(X, Y, q, q_loc)
    Ex2, Ey2 = campo_electrico(X, Y, q2, q2_loc)

    Ex_def = Ex+Ex2
    Ey_def = Ey+Ey2

    # A partir de aqui, he creado una nueva figura en la que se mostraran los vectores unitarios
    # Crear Matriz con magnitudes de vectores
    mags = (Ex_def**2+Ey_def**2)**(1/2)

    # Vectores Unitarios
    Ex_unit = np.divide(Ex_def, mags)
    Ey_unit = np.divide(Ey_def, mags)

    # Crear ejes y Figura
    fig, ax = plt.subplots(figsize=(7, 7))
    # Crear Campo Vectorial
    ax.quiver(X, Y, Ex_unit, Ey_unit)

    # Dibujar Carga puntual
    if q > 0:
        ax.scatter(q_loc[0], q_loc[1], c='red', s=1000)
    elif q < 0:
        ax.scatter(q_loc[0], q_loc[1], c='blue', s=1000)
    if q2 > 0:
        ax.scatter(q2_loc[0], q2_loc[1], c='red', s=1000)
    elif q2 < 0:
        ax.scatter(q2_loc[0], q2_loc[1], c='blue', s=1000)
    # Configuramos las dimensiones del eje y el aspecto
    ax.axis([grid_min, grid_max, grid_min, grid_max])
    ax.set_aspect('equal', 'box')

    plt.show()


main()
