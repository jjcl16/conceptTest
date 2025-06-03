# Anulación de Venta
La anulación es la acción de reversar una venta, por ello, solo se realiza si la venta se encuentra en el mismo lote, dejando sin efecto de forma total a la misma.

La anulación se realiza con el método **vpiVoid** de la librería de integración.

````c
Int vpiVoid(vpiVoidIn_t* input, vpiTrxOut_t* output, LONG timeout)
````
Este método cuenta con dos estructuras como parámetros:

La información que se envia a la terminal con los datos de la transacción a anular, la estructura de entrada, vpiVoidIn_t:

````c
typedef struct VOID_IN{  	
	LPSTR originalTicket;   // Número de cupón de trx. original  
	LPSTR issuerCode;       // Código de tarjeta
	LPSTR merchantName;     // Razón social del comercio
	LPSTR cuit;             // CUIT del comercio
}vpiVoidIn_t;
````
Cumpliendo con las siguientes caracteristicas:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   originalTicket  |       7          	| 
|   issuerCode		|       3	        |
|   merchantName    |       23          |
|   cuit	        |       23          |

Estructura de salida, vpiTrxOut_t:
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
	LPSTR time;         // Hora de la transacción (HH:MM:SS)
	LPSTR terminalID;   // Terminal id
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

### Aclaración anulaciones y devoluciones de transacciones QR.  
Las anulaciones y devoluciones de transacciones QR se denominan como "forzadas", es decir, se realizan sin intervención del "billeterahabiente". Al enviar el comando de anulación de una venta QR, la terminal va a iniciar y finalizar el proceso por si misma.
Para Pagos con T3.0 solo se pueden realizar Devoluciones.

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
- [Anulación](./Anulacion.md)
- [Cierre de lote](./cierreLote.md).
- [Devolución](./Devolucion.md).
- [Consulta de último cierre de lote](./consultaCierre.md).
- [Consulta de última transacción](./consultaUltTransaccion.md).
- [Consulta de tarjetas](./consultaTarjetas.md) disponibles para operar.
- [Consulta de planes](./consultaPlanes.md) a aplicar por tarjeta.