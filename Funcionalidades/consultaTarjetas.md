# Consulta de Tarjetas
Esta consulta permite obtener las marcas de tarjeta con que sería posible opera en el PoS.

Se realiza con el método **vpiGetIssuer** de la librería de integración.
````c
Int vpiGetIssuer(WORD index, vpiIssuerOut_t* output)
````

Este método recibe como parámetros el indice a consultar:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   index		    |        4          |

La estructura de salida, vpiIssuerOut_t :

````c
typedef struct ISSUER_OUT{   
	WORD index;             // Índice del registro.	 
	LPSTR acquirerCode;     // Código de procesador.   
	LPSTR issuerCode;       // Código de tarjeta   
	LPSTR issuerName;       // Nombre de la tarjeta   
	LPSTR maxInstCount;     // Maxima cantidad de cuotas
	LPSTR terminalID;       // Terminal id
}vpiIssuerOut_t;
````
Teniendo como largo máximo para estos valores:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   index		    |        4          |
|   acquirerCode    |        3          |
|   issuerCode      |        3          |
|   issuerName	    |        16	        |
|	maxInstCount	|		 2			|
|   terminalID	    |        8          |


Al ser un comando indexado, se puede consultar la sección de [comandos indexados](../Libreria/comandosIndexados.md) de la libreria de integración para conocer el funcionamiento de este tipo de comandos.

## Posibles Retorno del Método
Los posibles valores de retorno del método son los siguientes:
````
VPI_OK
VPI_MORE_REC
VPI_FAIL
VPI_TIMEOUT_EXP
VPI_INVALID_IN_CMD 
VPI_INVALID_IN_PARAM
VPI_INVALID_OUT_CMD
VPI_GENERAL_FAIL
VPI_INVALID_INDEX
````
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas

---
#### Otros enlaces
- [Principal](../README.md).
- [Manejo de puertos](./Puertos.md)
- [Prueba de comunicación](./ComTest.md)
- [Venta](./Venta.md).
- [Venta + Extracción](./Venta+Extracción.md).
- [Venta con QR](./VentaQR.md) + pago con transferencias.
- [Anulacion](./Anulacion.md)
- [Cierre de lote](./cierreLote.md).
- [Devolución](./Devolucion.md).
- [Consulta de último cierre de lote](./consultaCierre.md).
- [Consulta de última transacción](./consultaUltTransaccion.md).
- [Consulta de tarjetas](./consultaTarjetas.md) disponibles para operar.
- [Consulta de planes](./consultaPlanes.md) a aplicar por tarjeta.