##Imanol García Mendoza
import random
tablero= [[" ","1","2","3","4","5","6"],
          ["1","","","","","",""],
          ["2","","","","","",""],
          ["3","","","","","",""],
          ["4","","","","","",""],
          ["5","","","","","",""],
          ["6","","","","","",""]]

lista=[1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18]
random.shuffle(lista)#numeros al azar de mi lista
encontrados_jugador1=[]#contadores
encontrados_jugador2=[]

while True:
    def imprimir_tablero(tablero):
        for i in range (len(tablero)):
            for j in range (len(tablero)):
                if i==0:
                    print (j, end= "\t")
                elif j==0:
                    print (i, end= "\t")
                elif tablero[i][j] in encontrados_jugador1 or tablero[i][j] in encontrados_jugador2:
                    print (tablero[i][j], end= "\t")
                elif tablero[i][j] not in encontrados_jugador1 or tablero[i][j] in encontrados_jugador2:
                    print ("_", end= "\t")
            print()

    def acomodar(lista,tablero):
        s=0
        for i in range (1,(len(tablero))):
            for j in range (1,(len(tablero))):
                tablero[i][j]=lista[s]
                s+=1
        imprimir_tablero(tablero)
    acomodar(lista,tablero)

    def adivinar(lista,tablero):
        d=int(input("desea seguir jugando? 1.si/2.no"))
        if d == 1:
            print ("Jugador 1 turno")
            a=int(input("ingrese la fila de su carta 1"))
            if a > 6:
                print('ERROR')
                adivinar(lista,tablero)
            a2=int(input("ingrese la columna de su carta 1"))
            if a2 > 6:
                print('ERROR')
                adivinar(lista,tablero)
            else:
                print("Elegiste: ",tablero[a][a2])
            b=int(input("ingrese la fila de su carta 2"))
            if b > 6:
                print('ERROR')
                adivinar(lista,tablero)
            b2=int(input("ingrese la columna de su carta 2"))
            if b2 > 6:
                print('ERROR')
                adivinar(lista,tablero)
            else:
                print("Elegiste: ",tablero[b][b2])
            if tablero[a][a2]==tablero[b][b2]:
                encontrados_jugador1.append(tablero[a][a2],tablero[b][b2])
            else :
                print("no son iguales")
        if d==2:
            print('El jugador tiene',encontrados_jugador1,'pares')
            print('El jugador tiene',encontrados_jugador2,'pares')
            if len(encontrados_jugador1)> len(encontrados_jugador2):
                print('El ganador fue el jugador 1')
            elif len(encontrados_jugador1)< len(encontrados_jugador2):
                print('El ganador fue el jugador 2')
            elif len (encontrados_jugador1)==0 and len(encontrados_jugador2)==0:
                print("No encontraron nada")
            else:
                print('Fue un empate!')
            exit()
        if tablero[a][a2] in encontrados_jugador1 or tablero[a][a2] in encontrados_jugador2 or tablero[b][b2] in encontrados_jugador1 or tablero[b][b2] in encontrados_jugador2:
            print ("ya esta encontrada esa carta")
    adivinar(lista,tablero)
    

    def adivinar2(lista,tablero):
        d=int(input("desea seguir jugando? 1.si/2.no"))
        if d==1:
            print ("Jugador 2 turno")
            a=int(input("ingrese la fila de su carta 1"))
            if a > 6:
                print('ERROR')
                adivinar(lista,tablero)
            a2=int(input("ingrese la columna de su carta 1"))
            if a2 > 6:
                print('ERROR')
                adivinar(lista,tablero)
            else:
                print("Elegiste: ",tablero[a][a2])
            b=int(input("ingrese la fila de su carta 2"))
            if b > 6:
                print('ERROR')
                adivinar(lista,tablero)
            b2=int(input("ingrese la columna de su carta 2"))
            if b2 > 6:
                print('ERROR')
                adivinar(lista,tablero)
            else:
                print("Elegiste: ",tablero[b][b2])
            if tablero[a][a2]==tablero[b][b2]:
                encontrados_jugador2.append(tablero[a][a2],tablero[b][b2])
            else :
                print("no son iguales")
        if d==2 :
            print('El jugador tiene',encontrados_jugador1,'pares')
            print('El jugador tiene',encontrados_jugador2,'pares')
            if len(encontrados_jugador1)> len(encontrados_jugador2):
                print('El ganador fue el jugador 1')
            elif len(encontrados_jugador1)< len(encontrados_jugador2):
                print('El ganador fue el jugador 2')
            elif len (encontrados_jugador1)==0 and len(encontrados_jugador2)==0:
                print("No encontraron nada")
            else:
                print('Fue un empate!')
            exit()
        if tablero[a][a2] in encontrados_jugador1 or tablero[a][a2] in encontrados_jugador2 or tablero[b][b2] in encontrados_jugador1 or tablero[b][b2] in encontrados_jugador2:
            print ("ya esta encontrada esa carta")
    adivinar2(lista,tablero)
    
    if len(encontrados_jugador1)> len(encontrados_jugador2):
        print ("jugador 1 ganando")
    elif len(encontrados_jugador1)< len(encontrados_jugador2):
        print ("jugador 2 ganando")
    else :
        print ("jugador 1 y 2 empatados")

    if len(encontrados_jugador1)+len(encontrados_jugador2)==36:
        print('El jugador tiene',encontrados_jugador1,'pares')
        print('El jugador tiene',encontrados_jugador2,'pares')
        if len(encontrados_jugador1)> len(encontrados_jugador2):
            print('El ganador fue el jugador 1')
        elif len(encontrados_jugador1)< len(encontrados_jugador2):
            print('El ganador fue el jugador 2')
        else:
            print('Fue un empate!')
        exit()
