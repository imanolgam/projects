import random
import sys

x=0
y=0
x2=0
y2=0
p1 = 0
p2 = 0
cerrada = [['-','-','-','-','-','-'],['-','-','-','-','-','-'],['-','-','-','-','-','-'],['-','-','-','-','-','-'],['-','-','-','-','-','-'],['-','-','-','-','-','-']]
abierta = [[1,2,3,4,5,6],[7,8,9,10,11,12],[13,14,15,16,17,18],[1,2,3,4,5,6],[7,8,9,10,11,12],[13,14,15,16,17,18]]
raiz = 1

def memorama():
    imprimir()
    print('Player 1')

    x = int(input('Enter x of your first card: '))
    if x > 5:
        print('ERROR')
        memorama()

    y = int(input('Enter y of your first card: '))
    if y > 5:
        print('ERROR')
        memorama()

    cerrada[x][y] = abierta[x][y]

    imprimir()

    x2 = int(input('Enter x of your second card: '))
    if x2 > 5:
        print('ERROR')
        cerrada[x][y] = '-'
        memorama()
    else:
        y2 = int(input('Enter y of your second card: '))
        if y2 > 5:
            print('ERROR')
            cerrada[x][y] = '-'
            memorama()

    cerrada[x2][y2] = abierta[x2][y2]

    condiciones(x,y,x2,y2)

    imprimir()

def memorama2():
    imprimir()
    print('Player 2')

    x = int(input('Enter horizontal value: '))
    if x > 5:
        print('ERROR')
        memorama2()

    y = int(input('Enter vertical value: '))
    if y > 5:
        print('ERROR')
        memorama2()

    cerrada[x][y] = abierta[x][y]

    imprimir()

    x2 = int(input('Enter horizontal value: '))
    if x2 > 5:
        print('ERROR')
        cerrada[x][y] = '-'
        memorama2()
    else:
        y2 = int(input('Enter vertical value: '))
        if y2 > 5:
            print('ERROR')
            cerrada[x][y] = '-'
            memorama2()

    cerrada[x2][y2] = abierta[x2][y2]

    condiciones2(x,y,x2,y2)

    imprimir()

def condiciones(x,y,x2,y2):
    global p1
    if cerrada[x][y] != abierta[x2][y2]:##si ya esta abierta
        cerrada[x2][y2] = "-"
        cerrada[x][y] = "-"
        respuesta = str(input('Contnue playing? si/no: '))
        if respuesta == 'si':
            memorama2()
        elif respuesta == 'no':
            print('The player has',p1,'pairs')
            print('The player has',p2,'pairs')
            if p1 > p2:
                print('The winner is player 1')
            elif p2 > p1:
                print('The winner is player 2')
            elif p2 == p1:
                print('Tie!')
            elif p1 == p2:
                print('Tie!')
            sys.exit()    
    else:
        p1 += 1 
        memorama()

def condiciones2(x,y,x2,y2):
    global p2
    if cerrada[x][y] != cerrada[x2][y2]:
        cerrada[x2][y2] = "-"
        cerrada[x][y] = "-"
        respuesta = str(input('Continue playing? si/no: '))
        if respuesta == 'si':
            memorama()

        elif respuesta == 'no':
            print(p1)
            print(p2)
            if p1 > p2:
                print('The player has',p1,'pairs')
            elif p2 > p1:
                print('The player has',p2,'pairs')
            elif p2 == p1:
                print('Tie!')
            elif p1 == p2:
                print('Tie!')
            sys.exit()
    else:
        p2 += 1
        memorama2()

def imprimir():
    contador = 0
    print('  0 1 2 3 4 5 \n')

    for i in range(6):
        print(contador, '', end = '')
        contador += 1
        for j in range(6):
            print((cerrada[i][j]),'', end = '')

        print('\n')

def main():
    while raiz == 1:
        random.shuffle(abierta)
        for i in abierta:
            random.shuffle(i)
        memorama()

main()
