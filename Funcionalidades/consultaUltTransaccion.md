# Consulta de última transaccion aprobada
Esta consulta permite obtener la última transacción **aprobada** en el PoS.

Se realiza con el método **vpiGetLastTrxData** de la librería de integración.

````c
Int vpiGetLastTrxData(WORD* trxCode, vpiTrxOut_t* output)
````
Este método recibe dos parámetros de retorno.

El trxCode, que puede retornar en uno de los siguientes valores dependiendo del tipo de transacción que sea:
- 1: Venta
- 2: Anulación de venta
- 3: Devolución

Estructura de salida, vpiTrxOut_t, con la información de la transacción:
````c
typedef struct TRX_OUT{   	
	LPSTR hostRespCode; // Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente
  	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta
	LPSTR panLast4;     // Últimos 4 digitos de la tarjeta   
	LPSTR date;         // Fecha de la transacción (DD/MM/AAAA)  
	LPSTR time;         // Hora de la transaccion (HH:MM:SS)
	LPSTR terminalID;   //Terminal id
}vpiTrxOut_t;
````
Teniendo como largo máximo para estos valores:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   hostRespCode    |        2          |
|   hostMessage     |        32         |
|   authCode        |        6          |
|   ticketNumber    |        7          |
|   batchNumber     |        3          |
|   customerName    |        26         |
|   panFirst6       |        6          |
|   panLast4        |        4          |
|   date            |        10         |
|   time            |        8          |
|   terminalID      |        8          |

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
VPI_INVALID_ISSUER
VPI_INVALID_TICKET
VPI_EMPTY_BATCH
VPI_TRX_CANCELED
VPI_DIF_CARD
VPI_INVALID_CARD
VPI_EXPIRED_CARD
VPI_INVALID_TRX 
VPI_ERR_COM
VPI_ERR_PRINT
````
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas

En los comandos transaccionales, se debe tener en cuenta que el código de respuesta de la librería no implica que la transacción esté aprobada. El estado de la transacción se puede validar con el [hostRespCode](../Libreria/codigosRespuestaHost.md) recibido en la estructura de salida del método. 

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