# Devolución


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

Devoluciones QR