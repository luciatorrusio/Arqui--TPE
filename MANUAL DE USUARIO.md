## TRABAJO PRACTICO ESPECIAL // Arquitectura de Computadoras
## Manual de Usuario

El kernel implementado cuenta con dos programas principales: un interprete de comandos y un juego de ajedrez.

1. Interprete de comandos:
- game: Lleva al usuario al juego de ajedrez. Tiene un nombre genérico ya que, si en algún futuro se decidiera cambiar el ajedrez por otro juego, el usuario pueda entender igual a que refiere el comando.
- exit: Sale del kernel.
- time: Muestra el día y hora del sistema. Para mayor entendimiento y comodidad de los usuarios, se empleó el formato DD/MM/YYYY para la fecha, ya que es el formato usado en Argentina. Para la hora se usa el formato HH:MM:SS.
- man ‘function name’: Otra semejanza a Linux que se implementó. Si el usuario desea conocer qué hace un determinado comando, puede consultar su manual.
- invalidOpcode: Es una función de prueba de la excepción del mismo nombre. Al correr este comando se genera la excepción, mostrando el valor de cada registro.
- infoReg: Muestra el estado de los registros. Para implementar este comando se almacenan los registros en un vector para luego imprimirlos con más facilidad.
- divZero: Realiza la operación 2/0 de manera automática. Su objetivo es el de generar una excepción de división por cero. Se le muestra al usuario un mensaje de excepción junto con los registros.
printMem ‘position’: Realiza un volcado de memoria de 32 bytes a partir de la dirección recibida como argumento.
- clear: Limpia la pantalla.

2. Ajedrez:
- Se pueden usar las teclas ‘w’, ‘a’, ‘s’, ‘d’ para moverse hacia arriba, izquierda, abajo y derecha respectivamente.
- Para seleccionar una pieza y mostrar los movimientos válidos se pulsa ENTER estando posicionado en la pieza deseada. Luego de elegir el movimiento deseado el mismo se puede llevar a cabo pulsando ENTER nuevamente.
- Para retornar a la terminal se usa la tecla ‘q’.
- Si el usuario desea rotar el tablero, debe presionar la tecla ‘r’.