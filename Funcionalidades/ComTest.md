# Prueba de comunicación
Esta funcionalidad tiene como objetivo dos fines. Principalmente, verificar que la comunicación entre la terminal y la caja este establecida de manera correcta. Como segundo objetivo, podemos identificar que tipo de PoS está conectada a la caja.

El método a utilizar seria el **vpiGetVersion** de la librería de integración.

````c
Int vpiGetVersion(vpiVersionOut_t* output)
````

Este recibe una estructura de salida, vpiVersionOut_t:
````c
typedef struct GETVERSION_OUT {
	LPSTR versionMessage;  // Mensaje de respuesta de version 
} vpiVersionOut_t;
````

Para indentificar el PoS, lo hacemos dependiendo del parametro **versionMessage** de la estrutura de retorno.
````c
    Version         -----  versionMessage 
    Legacy          -----       001
    Interprete      -----       002
````
## Posibles Retorno del Método
Los posibles valores de retorno del método son los siguientes:
````c
VPI_OK
VPI_FAIL 
VPI_TIMEOUT_EXP
````
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas