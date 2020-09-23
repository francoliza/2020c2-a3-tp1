En el archivo npm.cpp se encuentran los algoritmos que resulven el problema.
Para que resuelva alguna instacia se debe realizar los siguientes pasos:

	1-Compilar con la instruccion "make" en la consola.

	2-Se debe elegir algun algoritmo para que resuelva la instancia, y escribir sus iniciales.
	A continuacion, los algoritmos disponibles con sus respectivas iniciales para referenciar: 
		Fuerza Bruta - "FB"
		Backtracking - "BT"
		Programacion Dinamica - "PD"
	3-Una vez hecho esto, y teniendo una instancia preparada, como se detalla en el Enunciado/Parametros de entrada y salida, 
	se debe correr el algoritmo con la siguiente nomeclatura:
	'instancia.txt' | ./npm 'iniciales'. 

Para que quede mas claro, para correr el ejemplo1.txt, que es el ejemplo que da el enunciado,
debería: 
	1- Compilar con "make".
	2- Correr el siguiente comando: "ej1.txt | ./solucion FB".

Luego por la pantalla de la consola se obtiene el resultado de la instancia ejmplo1.txt resuelto por el 
algoritmo de Fuerza Bruta.

Para borrar el ejecutable se debe correr el comando "make clean".
