# Cierre de lote
El lote es el registro de las operaciones que se han realizado en el PoS. 

El cierre de lote permite la presentación del mismo, para la posterior liquidación de las transacciones que incluye.

Como aclaración al cerrar un lote, se abre automáticamente un nuevo lote donde estarán las transacciones realizadas a partir de ese momento.

El mismo se realiza con el método **vpiBatchClose** de la librería de integración.

````c
Int vpiBatchClose(vpiBatchCloseOut_t* output, LONG timeout)
````

Recibiendo como parámetro la estructura de salida, vpiBatchCloseOut_t:

````c
typedef struct BATCHCLOSE_OUT{
	LPSTR hostRespCode; // Código de respuesta del host  
	LPSTR date;         // Fecha ("DD/MM/AAAA")  
	LPSTR time;         // Hora ("HH:MM:SS")
	LPSTR terminalID;   // Terminal id
}vpiBatchCloseOut_t;
````
### Aclaración Transferencias 3.0
Para las transferencias no existe una liquidación, ya que son inmediatas, por lo que no existe un cierre de lote que haya que presentar. Sin embargo, la terminal al momento de realizar el cierre incluirá en el cupón un totalizador de las operaciones realizadas con transferencias bajo la leyenda "Pagos Inmediatos".

## Posibles Retorno del Método
Los posibles valores de retorno del método son los siguientes:
````
VPI_OK
VPI_FAIL
VPI_TIMEOUT_EXP
VPI_INVALID_IN_CMD
VPI_INVALID_IN_PARAM
VPI_INVALID_OUT_CMD
VPI_GENERAL_FAIL
VPI_TRX_CANCELED
VPI_ERR_COM
VPI_ERR_PRINT
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