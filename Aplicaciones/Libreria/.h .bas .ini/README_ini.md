# vpiPC.ini

En este archivo solo se utiliza para habilitar o deshabilitar el logueo de la librería. De esta manera poder validar la información que recibe y la que envían los métodos invocados.

El formato seria el siguiente:
````c
[general]
debug_to_file=1  // 1 = Habilitado, 0 = Deshabilitado
````

Se debe ubicar en el mismo fichero que la libreria, que en caso de estar habilitado, generará el archivo vpiPC.log.

