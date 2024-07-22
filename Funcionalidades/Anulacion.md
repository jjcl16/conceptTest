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

### Anulaciones Transferencias 3.0  
Como aclaración, las anulaciones y devoluciones de T3.0 se denominan como "forzadas", es decir, se realizan sin intervención del "billeterahabiente". Al enviar el comando de anulación de una venta QR que fue pagada con T3.0, la terminal va a iniciar y finalizar el proceso por si misma (comunicandose con los servicios de T3.0).