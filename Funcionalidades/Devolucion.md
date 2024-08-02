# Devolución de venta
La devolución es una operación que permite revertir una venta que no se encuentra en el lote actual de la terminal.

La devolución se realiza con el método **vpiRefund** de la librería de integración.

````c
Int vpiRefund(vpiRefundIn_t* input, vpiTrxOut_t* output, LONG timeout)
````
Este método cuenta con dos estructuras como parámetros:

La información que se envia a la terminal con los datos de la transacción a devolver, la estructura de entrada, vpiRefundIn_t:
````c
typedef struct REFUND_IN{   
        LPSTR amount;           // Monto *100  
        LPSTR instalmentCount;	// Cant. de cuotas  
    	LPSTR issuerCode;       // Código de tarjeta
    	LPSTR planCode;         // Código de plan
    	LPSTR originalTicket;   // Nro. ticket de la trx. original
    	LPSTR originalDate;     // Fecha de la trx. original
        LPSTR receiptNumber;    // Número de factura 
        LPSTR merchantCode;     // Código de comercio a utilizar
        LPSTR merchantName;     // Razon social del comercio
        LPSTR cuit;             // CUIT del comercio
        char  linemode;         // transaccion Online(1) 
}vpiRefundIn_t;
````
Cumpliendo con las siguientes caracteristicas:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   amount          |       12          | 
|   instalmentCount |       2           |
|   issuerCode      |       3           |
|   planCode        |       1           |
|	originalTicket	|		7			|
|	originalDate	|		10			|
|   receiptNumber   |       12          | 
|   merchantCode    |       15          |
|   merchantName    |       23          |
|   cuit            |       23          |
|   linemode        |       1           |

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


### Aclaración transferencias 3.0  
Las anulaciones y devoluciones de T3.0 se denominan como "forzadas", es decir, se realizan sin intervención del "billeterahabiente". Al enviar el comando de anulación de una venta QR que fue pagada con T3.0, la terminal va a iniciar y finalizar el proceso por si misma (comunicandose con los servicios de T3.0).
De igual manera, los siguientes parámetros vendran preseteados de la siguiente manera, únicamente para el caso de Transferencias 3.0:
- panFirst6: 000000
- panLast4: 0000

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