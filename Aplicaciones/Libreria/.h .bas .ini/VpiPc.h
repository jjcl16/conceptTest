#pragma once

#ifndef _VPIPC_H_
#define _VPIPC_H_
/**
* VpiPc.h
* Contiene la declaración de la sunciones que implementan la comunicación
* utilizando el protocolo IngStore, entre una PC y un POS Ingenico con la
* aplicación de VISA con POS Integrado.
*/

#include "ClassicCommandCodes.h"
#include "../IngStoreStaticLib/POSResponseCodes.h"

/*------------------------------CONSTANTES------------------------------*/

/**
* Codigos de retorno de las funciones
*/
#define VPI_OK				0	// Operacion exitosa
#define VPI_MORE_REC		1	// Operacion exitosa, pero faltan registros

#define VPI_FAIL			11	// El comando no pudo ser enviado
#define VPI_TIMEOUT_EXP		12	// Tiempo de espera agotado.

#define VPI_INVALID_ISSUER	101	// El código de tarjeta no existe.
#define VPI_INVALID_TICKET  102 // El número de cupón no existe.
#define VPI_INVALID_PLAN	103 // El código de plan no existe.
#define VPI_INVALID_INDEX	104	// No existe el indice
#define VPI_EMPTY_BATCH		105	// El lote del POS se encuentra vacío.

#define VPI_TRX_CANCELED	201 // Transacción cancelada por el usuario.
#define VPI_DIF_CARD		202 // La tarjeta deslizada por el usuario no coincide con la pedida.
#define VPI_INVALID_CARD	203 // La tarjeta deslizada no es válida.
#define VPI_EXPIRED_CARD	204 // La tarjeta deslizada está vencida.
#define VPI_INVALID_TRX		205 // La transacción original no existe. 

#define VPI_ERR_COM			301 // El POS no pudo comunicarse con el host.
#define VPI_ERR_PRINT		302 // El POS no pudo imprimir el ticket.

#define VPI_INVALID_IN_CMD		901 // Nombre del comando inexistente.
#define VPI_INVALID_IN_PARAM	902 // Formato de algún parámetro de entrada no es correcto.
#define VPI_INVALID_OUT_CMD		903 // El comando enviado por 

#define VPI_GENERAL_FAIL		909 // Error general en la operación.

/**
* Codigos de las operaciones (LEGACY)
*/
#define VPI_PURCHASE		1	// Venta
#define VPI_VOID			2	// Anulación de venta
#define VPI_REFUND			3	// Devolución
#define VPI_REFUND_VOID		4	// Anulación de devolución

/**
* Timeouts
*/
#define VPI_TIMEOUT_STD		3000	// Timeout mínimo 3 segundos
#define VPI_TIMEOUT_HIG		60000	// Timeout alto 60 segundos
#define VPI_TIMEOUT_MED		30000	// Timeout medio 30 segundos
#define VPI_TIMEOUT_LOW		10000	// Timeout bajo 10 segundos

/*------------------------------STRUCTS------------------------------*/

/**
* Parámetros de configuración del puerto serial.
*/
typedef struct COM_PARAMS{

	LPSTR com;			// Nombre del puerto. Ej: "COM1", "COM2", etc.
	WORD  baudRate;		// Velocidad de transmición: Ej: 19200
	WORD byteSize;		// Largo del byte. Ej: 7, 8
	char  parity;		// Paridad. Ej: 'N' ninguna, 'E' par, 'O' impar
	WORD  stopBits;		// Bits de parada. Ej: 1, 2
	
}comParams_t;

/**
* Parametros de entrada para la funcion de Venta
*/
typedef struct PURCHASE_IN{

	LPSTR amount;			// Monto *100  
	LPSTR receiptNumber;	// Número de factura  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// Código de tarjeta  
	LPSTR planCode;			// Código de plan  
	LPSTR tip;				// Propina *100
	LPSTR merchantCode;		// Código de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 

}vpiPurchaseIn_t;

/**
* Parametros de entrada para la funcion de Eliminar Reverso
*/
typedef struct DELETEREV_IN {

	LPSTR amount;			// Monto *100  	
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// Código de tarjeta  
	LPSTR planCode;			// Código de plan  
	LPSTR tip;				// Propina *100
	LPSTR merchantCode;		// Código de comercio a utilizar
	LPSTR panFirst6;		// Primeros 6
	LPSTR panLast4;			// Ultimos 4
	LPSTR issuerCodeVRE;	// Código de tarjeta VRE

}vpiRevDeleteIn_t;

/**
* Parametros de entrada para la funcion de Venta con nombre grupo
*/
typedef struct PURCHASEGROUP_IN {

	LPSTR amount;			// Monto *100  
	LPSTR receiptNumber;	// Número de factura  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// Código de tarjeta  
	LPSTR planCode;			// Código de plan  
	LPSTR tip;				// Propina *100
	LPSTR groupName;		// Nombre del Grupo a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 

}vpiPurchaseGroupIn_t;


/**
* Parametros de entrada para la funcion de Anulacion y Anulacion de Devolucion
*/
typedef struct VOID_IN{  
	
	LPSTR originalTicket;   // Número de cupón de trx. original  
	LPSTR issuerCode;       // Código de tarjeta
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio

}vpiVoidIn_t;

/**
* Parametros de entrada para la funcion de Devolucion
*/
typedef struct REFUND_IN{  
	
	LPSTR amount;			// Monto *100  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// Código de tarjeta  
	LPSTR planCode;			// Código de plan  
	LPSTR originalTicket;	// Nro. ticket de la trx. original  
	LPSTR originalDate;		// Fecha de la trx. original
    LPSTR receiptNumber;	// Número de factura 
	LPSTR merchantCode;		// Código de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 
}vpiRefundIn_t;

/**
* Parametros de salida para las funciones de Venta, Anulacion y Devolucion
*/
typedef struct TRX_OUT{   
	
	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	/* Eldar MOD ---> */
  	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta
  	/* <--- Eldar MOD */
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;

}vpiTrxOut_t;


/**
* Parametros de salida para las funciones de Venta con marca de retorno cons codigo de comercio
*/
typedef struct TRXMARK1_OUT {

	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// Código de tarjeta
	LPSTR merchantCode;	// Código de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxMarkOut1_t;

/**
* Parametros de salida para las funciones de Venta con marca de retorno sin codigo de comercio
*/
typedef struct TRXMARK_OUT {

	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// Código de tarjeta
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxMarkOut_t;

/**
* Parametros de salida para las funciones de Venta sin borrar reverso
*/
typedef struct TRXREV_OUT {

	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// Código de tarjeta
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxRevOut_t;

/**
* Parametros de salida para las funciones de Venta con multiples establecimientos
*/
typedef struct TRXGROUP_OUT {

	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// Código de tarjeta
	LPSTR merchantCode;	// Código de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxGroupOut_t;

/**
* Parametros de salida para las funciones de consulta de credito directo (CCD)
*/
typedef struct CCDMARK_OUT {

	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// Código de tarjeta
	LPSTR merchantCode;	// Código de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR instCount1;	// Cantidad de cuotas
	LPSTR valueCount1;	// Valor de la Cuota
	LPSTR TNA1;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount2;	// Cantidad de cuotas
	LPSTR valueCount2;	// Valor de la Cuota
	LPSTR TNA2;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount3;	// Cantidad de cuotas
	LPSTR valueCount3;	// Valor de la Cuota
	LPSTR TNA3;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount4;	// Cantidad de cuotas
	LPSTR valueCount4;	// Valor de la Cuota
	LPSTR TNA4;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount5;	// Cantidad de cuotas
	LPSTR valueCount5;	// Valor de la Cuota
	LPSTR TNA5;			// TNA (3 enteros y 2 decimales)
	LPSTR emisorName;	// Nombre del Banco emisor
	LPSTR promoMsg;		// Mensaje promocional

}vpiCcdMarkOut_t;

/**
* Parametros de salida de la funcion de Cierre de lote.
*/
typedef struct BATCHCLOSE_OUT{  

	LPSTR hostRespCode;	// Codigo de respuesta del host  
	LPSTR date;			// Fecha ("DD/MM/AAAA")  
	LPSTR time;			// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseOut_t;

/**
* Registro con los totales por tarjeta del Cierre de lote.
*/
typedef struct BATCHCLOSEDATA_OUT{   
	
	WORD index;				// Índice del registro.   
	LPSTR acquirerCode;		// Código de procesador.   
	LPSTR batchNumber;		// Número de lote.   
	LPSTR issuerCode;		// Código de tarjeta   
	LPSTR purchaseCount;	// Cantidad de ventas.   
	LPSTR purchaseAmount;	// Monto total de ventas.   
	LPSTR voidCount;		// Cantidad anulaciones de venta.   
	LPSTR voidAmount;		// Monto total de anulaciones.   
	LPSTR refundCount;		// Cantidad de devoluciones venta.   
	LPSTR refundAmount;		// Monto total de devoluciones.   
	LPSTR refvoidCount;		// Cantidad anulaciones devolución.   
	LPSTR refvoidAmount;	// Monto total anul. devolución.
	LPSTR date;				// Fecha ("DD/MM/AAAA")  
	LPSTR time;				// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseDataOut_t;

/**
* Registro con los totales por tarjeta del Cierre de lote con grupo.
*/
typedef struct BATCHCLOSEDATAGROUP_OUT {

	WORD index;				// Índice del registro.   
	LPSTR acquirerCode;		// Código de procesador.   
	LPSTR batchNumber;		// Número de lote.   
	LPSTR groupName;		// Nombre del grupo.
	LPSTR issuerCode;		// Código de tarjeta   
	LPSTR purchaseCount;	// Cantidad de ventas.   
	LPSTR purchaseAmount;	// Monto total de ventas.   
	LPSTR voidCount;		// Cantidad anulaciones de venta.   
	LPSTR voidAmount;		// Monto total de anulaciones.   
	LPSTR refundCount;		// Cantidad de devoluciones venta.   
	LPSTR refundAmount;		// Monto total de devoluciones.   
	LPSTR refvoidCount;		// Cantidad anulaciones devolución.   
	LPSTR refvoidAmount;	// Monto total anul. devolución.
	LPSTR date;				// Fecha ("DD/MM/AAAA")  
	LPSTR time;				// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseDataGroupOut_t;

/**
* Entrada para IES
*/
typedef struct IES_IN {

	LPSTR issuerCode;     //Código de tarjeta   
	LPSTR newReg;	      //Ultimo registro
	LPSTR nameGroup;	  //Nombre del Grupo.
	LPSTR merchant;		  //Numero de establecimiento.

}vpiIesIn_t;

/**
* Retorno para IES
*/
typedef struct IES_OUT {

	WORD index;           //Índice del registro.
	LPSTR respcode;		  //Codigo de respuesta. 
	LPSTR issuerCode;     //Código de tarjeta   
	LPSTR issuerName;     //Nombre de la tarjeta
	LPSTR merchant;		  //Numero de establecimiento.
	LPSTR nameGroup;	  //Nombre del Grupo.
	LPSTR terminalID;	  //Terminal ID.

}vpiIesOut_t;

//ADD 1.18 Marzo 2020
/**
* Entrada para QRC
*/
typedef struct QRC_IN {
	LPSTR idQR;     //Id del QR consultado   
}vpiQrcIn_t;

/**
* Retorno para QRC
*/
typedef struct QRC_OUT {
	LPSTR respcode;           //Código de respuesta del host.
	LPSTR respMsg;		  //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR trxDate;	  //Fecha de la transacción(“DD / MM / AAAA”).
	LPSTR trxHr;	  //Hora de la transacción(“HH:MM:SS”).
	LPSTR terminalID;	  //Terminal id.
	LPSTR medioPago;	  //Medio de Pago.
	LPSTR cardCod;	  //Código de Tarjeta.
	LPSTR idUnico;	  //ID Unico.
	LPSTR idBanco;	  //ID Banco.
	LPSTR emisorDscr;	  //Descripción de emisor.
	//ADD clarin 365
	LPSTR impTotal;	  //Importe Total
	LPSTR impCobrado;	  //Importe cobrado
	LPSTR codTarjBenef;	  //Código de Tarjeta Beneficio.
	LPSTR impDescuento;	  //Importe descontado
	//ADD clarin 365 FIN
}vpiQrcOut_t;

/**
* Entrada para QRT
*/
typedef struct QRT_IN {
	LPSTR ammount; //Monto
	LPSTR ticketNmb;	//Número de factura.
	LPSTR cantCoutas;	//Cantidad de cuotas.
	LPSTR planCod;	//Código de plan.
	LPSTR voidId;	//QR ID utilizado para anulación
	LPSTR refundId;	//ID Para devoluciones
	LPSTR trxDate;	//Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR imprimeTckt;	//Imprime ticket.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
	LPSTR tipoQR;	//Tipo de QR
	LPSTR merchants;	//Merchants
}vpiQrtIn_t;

/**
* Retorno para QRT
*/
typedef struct QRT_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR idQR; //QR ID.  
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id	
}vpiQrtOut_t;
//ADD 1.18 Marzo 2020 FIN



/**
* Entrada para QRZ
*/
typedef struct QRZ_IN {
	LPSTR ammount; //Monto
	LPSTR cantCoutas;	//Cantidad de cuotas.
	LPSTR planCod;	//Código de plan.	
}vpiQrzIn_t;

typedef struct QRZ_OUT {
	LPSTR respcode;           //Código de respuesta del host.
	LPSTR respMsg;		  //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR trxDate;	  //Fecha de la transacción(“DD / MM / AAAA”).
	LPSTR trxHr;	  //Hora de la transacción(“HH:MM:SS”).
	LPSTR terminalID;	  //Terminal id.
	LPSTR cardCod;	  //Código de Tarjeta.
	LPSTR impTotal;	  //Importe Total
	LPSTR impCobrado;	  //Importe cobrado	
}vpiQrzOut_t;



/**
* Entrada para FLUCAS
*/
typedef struct LUCAS_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiLUCASIn_t;

/**
* Retorno para LUCAS
*/
typedef struct LUCAS_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR uniAcumm; //Unidades acumuladas
}vpiLUCASOut_t;

//ADD 

/**
* Entrada para FCO
*/
typedef struct FCO_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFcoIn_t;

/**
* Retorno para FCO
*/
typedef struct FCO_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR uniAcumm; //Unidades acumuladas
}vpiFcoOut_t;
/**
* Entrada para FRE
*/
typedef struct FRE_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR uniRed; //Unidades a redimir
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFreIn_t;

/**
* Retorno para FRE
*/
typedef struct FRE_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
}vpiFreOut_t;

/**
* Entrada para FCA
*/
typedef struct FCA_IN {
	LPSTR prodCod; //Codigo de producto 20
	LPSTR uniRed; //Unidades a redimir 
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFcaIn_t;

/**
* Retorno para FCA
*/
typedef struct FCA_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFcaOut_t;
/**
* Entrada para FAC
*/
typedef struct FAC_IN {
	LPSTR prodCod; //Codigo de producto 20
	LPSTR uniAcum; //Unidades a acumular 
}vpiFacIn_t;

/**
* Retorno para FAC
*/
typedef struct FAC_OUT {
	LPSTR respcode; //Código de  respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFacOut_t;

/**
* Entrada para FAN
*/
typedef struct FAN_IN {
	LPSTR cuponNmb;     //Número de cupón	
}vpiFanIn_t;

/**
* Retorno para FAN
*/
typedef struct FAN_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFanOut_t;
/**
* Entrada para FAR
*/
typedef struct FAR_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR cuponNum;	//Numero de cupon
}vpiFarIn_t;

/**
* Retorno para FAR
*/
typedef struct FAR_OUT {
	LPSTR respcode; //Código de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //Código de autorización   
	LPSTR cuponNmb;     //Número de cupón
	LPSTR loteNmb;		  //Número de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 dígitos de la tarjeta.
	LPSTR lastFour;	  //Últimos 4 dígitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacción(“DD / MM / AAAA”)
	LPSTR trxHr;	//Hora de la transacción(“HH:MM:SS”)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
}vpiFarOut_t;

//ADD compativilidad VPI viejo
/*
	Entrada para FCO compatible con VPI viejo
*/
typedef struct LOYALTY_BALANCE_IN {

	LPSTR productCode;
	//LPSTR amount;
	LPSTR issuerCode;		// Código de tarjeta 
	LPSTR merchantCode;		// Código de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio

} vpiLoyaltyBalanceIn_t;

/*
	Entrada para FRE compatible con VPI viejo
*/
typedef struct LOYALTY_REDEEM_IN {

	LPSTR productCode;
	LPSTR amount;
	LPSTR issuerCode;		// Código de tarjeta 
	LPSTR merchantCode;		// Código de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio


} vpiLoyaltyRedeemIn_t;


/*
	Entrada para FAR compatible con VPI viejo
*/
typedef struct LOYALTY_VOID_IN {

	LPSTR amount;			// Monto *100  

} vpiLoyaltyVoidIn_t;



typedef struct GETVERSION_OUT {

	LPSTR versionMessage;  // Mensaje de respuesta de version 

} vpiGetVersion_t;
/*
	Salida para FAR, FCO y FRE compatible con VPI viejo
*/
typedef struct LOYALTY_OUT {
	LPSTR hostRespCode;	// Código de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // Número de autorización   
	LPSTR ticketNumber; // Número de cupón   
	LPSTR batchNumber;  // Número de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	/* Eldar MOD ---> */

	//------------ 2091202 fix ?
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;      	// Primeros 6 digitos de la tarjeta
	//--------------

	/* <--- Eldar MOD */

	LPSTR date;         // Fecha de la transacción   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;
	LPSTR amount;			// Monto de unidades
} vpiLoyaltyOut_t;
//ADD compativilidad VPI viejo FIN
//ADD Fidelidad FIN

/**
* Retorno de OTE
*/
typedef struct OTE_OUT {

	WORD index;        //Índice del registro.
	LPSTR codProc;	   //Codigo de procesador.
	LPSTR issuerCode;  //Código de tarjeta   
	LPSTR cardName;	   //Nombre de la tarjeta.
	LPSTR merchant;    //Numero de establecimiento
	LPSTR groupName;   //Nombre del Grupo
	LPSTR terminalID;  //Terminal ID

}vpiOteOut_t;

/**
* Retorno de REV
*/
typedef struct REV_OUT {

	LPSTR respCode;	   //Codigo de respuesta.
	LPSTR respMsg;     //Mensaje de respuesta.   
	LPSTR date;		   // Fecha ("DD/MM/AAAA")  
	LPSTR time;		   // Hora ("HH:MM:SS")
	LPSTR terminalID;  //Terminal ID

}vpiRevOut_t;

/**
*/
typedef struct ISSUER_OUT{   

	WORD index;           //Índice del registro.		//LFT 
	LPSTR acquirerCode;   //Código de procesador.   
	LPSTR issuerCode;     //Código de tarjeta   
	LPSTR issuerName;     //Nombre de la tarjeta   
	LPSTR maxInstCount;   //Maxima cantidad de cuotas
	LPSTR terminalID;

}vpiIssuerOut_t;

/**
*/
typedef struct PLAN_OUT{   
	
	WORD index;        //Índice del registro.   		//LFT  
	LPSTR issuerCode;  //Código de tarjeta   
	LPSTR planCode;    //Código de plan   
	LPSTR planLabel;   //Nombre del plan
	LPSTR terminalID;

}vpiPlanOut_t;

/**
*/
typedef struct VERSION_OUT{   
	
	WORD version;            //Version del VPI.   		//LFT  

}vpiVersionOut_t;

/**
*/
typedef struct CLASSIC_MESSAGE_ARRAY {

	BYTE* msg;
	int msgLen;

}vpiClsMessageArray_t;

/**
*/
typedef struct CLASSIC_MESSAGE {

	BYTE header[2]; //CLA_INS
	BYTE modoIntegracion;
	BYTE versionMensaje;
	BYTE p2;
	BYTE LC[2];
	BYTE* data;
	BYTE TOU[2];

}vpiClsMessage_t;

/**
*/
typedef struct PRI_OUT {

//	WORD index;           //Índice del registro.
	LPSTR issuerCode;	  //Código de tarjeta   
	LPSTR panFirst6;	  //BIN de la tarjeta.   
	LPSTR panLast4;    //Ultimos cuatro digitos de la tarjeta   
	LPSTR terminalID;	  //Numero de la terminal

}vpiPriOut;

/*--------------------------METODOS LEGACY --------------------------*/

/**
* Abre el puerto serial de comunicaciones para poder enviar y recibir
* los comandos.El puerto debe estar cerrado para que la ejecución sea 
* exitosa.Es necesario para ejecutar el resto de los comandos.
* @param params Parámetros de configuracion del puerto serial.
*
* @return VPI_OK Puerto abierto exitosamente	
* @return VPI_FAIL El puerto se encontraba abierto o no se pudo abrir.
*/
WORD __stdcall vpiOpenPort (comParams_t* params);

/**
* Cierra el puerto serial de comunicaciones y lo deja libre para otras
* aplicaciones. El puerto debe estar abierto para que la ejecución sea 
* exitosa.Luego de ejecutar este comando, no se puede ejecutar ningun 
* otro comando.
* @return VPI_OK Puerto cerrado exitosamente
* @return VPI_FAIL El puerto no se encontraba abierto o no se pudo cerrar.
*/
WORD __stdcall vpiClosePort(void);

/**
* Envía un mensaje por el puerto y espera la respuesta al mismo en forma 
* sincrónica, para verificar que la conexión con el POS esté OK.La 
* aplicación queda esperando hasta tenga la respuesta o bien expire el
* timeout default.El puerto debe estar abierto para que la ejecución sea exitosa.
* @return VPI_OK Conexión exitosa.
* @return VPI_FAIL No se pudo enviar el comando posiblemente el puerto esté cerrado.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
*/
WORD __stdcall vpiTestConnection(void);

/**
* Envía la orden de realizar una venta y espera la respuesta de la misma en forma
* sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea 
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. 
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchase(vpiPurchaseIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta con credito directo 
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseCreditoDirecto(vpiPurchaseIn_t* input, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Envía la orden de realizar una consulta de credito directo
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiConsultaCreditoDirecto(vpiPurchaseIn_t* input, vpiCcdMarkOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta con extra cash 
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseExtraCash(vpiPurchaseIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta con retorno de marca
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseMark(vpiPurchaseIn_t* intput, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta extra cash con retorno de marca
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseExtraCashMark(vpiPurchaseIn_t* intput, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta que no elimina el reverso
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa. No borra reverso
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseRev(vpiPurchaseIn_t* intput, vpiTrxMarkOut_t* output, LONG timeout);

/**
* Envía la orden de eliminar reverso si existe
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiDeleteRev(vpiRevDeleteIn_t* intput, vpiRevOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta con multiples establecimientos
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseGroup(vpiPurchaseGroupIn_t* intput, vpiTrxGroupOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una venta extra cash con multiples establecimientos
* y espera la respuesta de la misma en forma sincrónica.
* La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseGroupExtraCash(vpiPurchaseGroupIn_t* intput, vpiTrxGroupOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una anulación de venta y espera la respuesta de la misma
* en forma sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien 
* expire el timeout especificado.El puerto debe estar abierto para que la ejecución 
* sea exitosa.
* @param input Estructura con los datos de entrada de la anulación.
* @param output Estructura con los datos de respuesta de la anulación. 
*               Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX 
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT

*/
WORD __stdcall vpiVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una devolución y espera la respuesta de la misma en 
* forma sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien
* expire el timeout especificado.El puerto debe estar abierto para que la ejecución
* sea exitosa.
* @param input Estructura con los datos de entrada de la devolución.
* @param output Estructura con los datos de respuesta de la devolución. 
*               Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexión exitosa.
* @return VPI_FAIL No se pudo enviar el comando.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_ISSUER El código de tarjeta no existe.
* @return VPI_INVALID_PLAN El código de plan no existe.
* @return VPI_TRX_CANCELED Transacción cancelada por el usuario.
* @return VPI_DIF_CARD La tarjeta deslizada por el usuario no coincide con la pedida.
* @return VPI_INVALID_CARD La tarjeta deslizada no es válida.
* @return VPI_EXPIRED_CARD La tarjeta deslizada está vencida.
* @return VPI_ERR_COM El POS no pudo comunicarse con el host.
* @return VPI_ERR_PRINT El POS no pudo imprimir el ticket.
* @return VPI_INVALID_IN_CMD Nombre del comando inexistente.
* @return VPI_INVALID_IN_LEN Largo de los parámetros inválido para este comando.
* @return VPI_INVALID_IN_PARAM Formato de algún parámetro no es correcto.
* @return VPI_INVALID_OUT_CMD Nombre del comando devuelto no coincide con el enviado.
* @return VPI_INVALID_OUT_LEN Largo de los parámetros devueltos inválido para este comando.
* @return VPI_INVALID_OUT_PARAM Formato de algún parámetro devuelto no es correcto.
* @return VPI_GENERAL_FAIL Error general en la operación.
*/
WORD __stdcall vpiRefund (vpiRefundIn_t* input, vpiTrxOut_t* output, LONG timeout);

/**
* Envía la orden de realizar una anulación de devolución y espera la respuesta
* de la misma en forma sincrónica.La aplicación queda esperando hasta tenga la 
* respuesta o bien expire el timeout especificado.El puerto debe estar abierto 
* para que la ejecución sea exitosa.
* @param input Estructura con los datos de entrada de la anulación.
* @param output Estructura con los datos de respuesta de la anulación. 
*               Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX 
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiRefundVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, LONG timeout); 

/**
* Envía la orden de realizar un cierre de lote. La aplicación queda esperando hasta
* tenga la respuesta o bien expire el timeout especificado. El puerto debe estar 
* abierto para que la ejecución sea exitosa.
* @param output Estructura con el resultado de la operación contra el host. 
*               Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
* 
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_TRX_CANCELED
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiBatchClose(vpiBatchCloseOut_t* output, LONG timeout);

/**
* Envía la orden de obtener la información de la última transacción realizada 
* y espera la respuesta de la misma en forma sincrónica.La aplicación queda 
* esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecución sea exitosa.
* @param trxCode Código del tipo de transacción: VPI_PURCHASE, VPI_VOID, 
                                                 VPI_REFUND, VPI_REFUND_VOID
*
* @param output Estructura con los datos de respuesta de la última transacción realizada. 
*               Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_INVALID_PLAN
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiGetLastTrxData(WORD* trxCode, vpiTrxOut_t* output);


/**
* Envía la orden de obtener un determinado registro, con los totales por tarjeta 
* del último cierre realizado y espera la respuesta de la misma en forma 
* sincrónica.Para obtener todos los registros se debe hacer un ciclo desde 0  
* hasta que el código de respuesta sea distinto de VPI_MORE_REC. La aplicación queda esperando 
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe 
* estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la información del registro que quiero.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe. 
* @return VPI_TRX_CANCELED Transacción cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD 
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetBatchCloseData(WORD index, vpiBatchCloseDataOut_t* output);

/**
* Envía la orden de re-imprimir el ticket de la última transacción.La aplicación queda 
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe 
* estar abierto para que la ejecución sea exitosa.
*
* @param Ninguno
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPrintTicket(void);

/**
* Envía la orden de re-imprimir el ticket del último cierre de lote. La aplicación queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe estar
* abierto para que la ejecución sea exitosa.
* 
* @param Ninguno
* 
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPrintBatchClose(void);

/**
* Envía el comando para obtener un registro de la tabla de tarjetas del POS y espera 
* la respuesta de la misma en forma sincrónica. Para obtener todos los registros se 
* debe hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda  esperando hasta tenga la respuesta o bien expire el timeout especificado. 
* El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos de la tarjeta. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetIssuer(WORD index, vpiIssuerOut_t* output);

/**
* Envía el comando para obtener un registro de la tabla de planes del POS y espera la 
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout 
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetPlan(WORD index, vpiPlanOut_t* output);

/**
* Envía el comando para obtener un registro de la tabla de grupos del POS y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetOTE(WORD index, vpiOteOut_t* output);

/**
* Envía el comando para registrar un nuevo grupo y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetIES(vpiIesIn_t* input, vpiIesOut_t* output, LONG timeout);

//ADD 1.18 Marzo 2020
/**
* Envía el comando para consultar el estado de un QR y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetQRC(vpiQrcIn_t* input, vpiQrcOut_t* output, LONG timeout);

/**
* Envía el comando para la generación de un QR y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetQRT(vpiQrtIn_t* input, vpiQrtOut_t* output, LONG timeout);
//ADD 1.18 Marzo 2020 FIN
//ADD Fidelidad
/**
* Envía el comando para consultar el estado de un QR y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFCO(vpiFcoIn_t* input, vpiFcoOut_t* output, LONG timeout);

/**
* Envía el comando para la generación de un QR y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFRE(vpiFreIn_t* input, vpiFreOut_t* output, LONG timeout);

/**
* Envía el comando para la generación de un QR y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFAR(vpiFarIn_t* input, vpiFarOut_t* output, LONG timeout);

//ADD compativilidad VPI viejo
/*
	Procesamiento FCO vpi viejo
*/
WORD __stdcall vpiLoyaltyBalance(vpiLoyaltyBalanceIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);
WORD UnMountLoyaltyResp(vpiLoyaltyOut_t* data, char* buffer);
WORD MountLoyaltyBalance(char* buffer, vpiLoyaltyBalanceIn_t* data);

/*
	Procesamiento FRE vpi viejo
*/
WORD __stdcall vpiLoyaltyRedeem(vpiLoyaltyRedeemIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);
WORD MountLoyaltyRedeem(char* buffer, vpiLoyaltyRedeemIn_t* data);

/*
	Procesamiento FAR vpi viejo
*/
WORD __stdcall vpiLoyaltyVoid(vpiLoyaltyVoidIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);

//ADD compativilidad VPI viejo FIN
//ADD Fidelidad FIN

/**
* Envía el comando para obtener un registro de la tabla de planes del POS y espera la 
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout 
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetVersion(vpiVersionOut_t* output);

/**
* Envía el comando para obtener el PAN y los ultimos 4 digitos de la tarjeta.
* El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param ninguno.
* @param output Estructura con los datos del PAN, los ultimos 4 digitos de la tarjeta
* y el numero de terminal. Se completa dentro de la función.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetPANData(vpiPriOut* output);

/**
* Envía la orden de obtener un determinado registro, con los totales por tarjeta
* del último cierre realizado con grupo y espera la respuesta de la misma en forma
* sincrónica.Para obtener todos los registros se debe hacer un ciclo desde 0
* hasta que el código de respuesta sea distinto de VPI_MORE_REC. La aplicación queda esperando
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe
* estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la información del registro que quiero.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe.
* @return VPI_TRX_CANCELED Transacción cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetBatchCloseDataGroup(WORD index, vpiBatchCloseDataGroupOut_t* output);

/*--------------------------(NUEVOS) METODOS CLASICOS --------------------------*/

/**
* Abre el puerto serial de comunicaciones para poder enviar y recibir
* los comandos.El puerto debe estar cerrado para que la ejecución sea
* exitosa.Es necesario para ejecutar el resto de los comandos.
* @param params Parámetros de configuracion del puerto serial.
*
* @return VPI_OK Puerto abierto exitosamente
* @return VPI_FAIL El puerto se encontraba abierto o no se pudo abrir.
*/
WORD __stdcall cmdOpenPort(comParams_t* params);

/**
* Cierra el puerto serial de comunicaciones y lo deja libre para otras
* aplicaciones. El puerto debe estar abierto para que la ejecución sea
* exitosa.Luego de ejecutar este comando, no se puede ejecutar ningun
* otro comando.
* @return VPI_OK Puerto cerrado exitosamente
* @return VPI_FAIL El puerto no se encontraba abierto o no se pudo cerrar.
*/
WORD __stdcall cmdClosePort(void);

/**
* Envía un mensaje por el puerto y espera la respuesta al mismo en forma
* sincrónica, para verificar que la conexión con el POS esté OK.La
* aplicación queda esperando hasta tenga la respuesta o bien expire el
* timeout default. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexión exitosa.
* @return VPI_FAIL No se pudo enviar el comando posiblemente el puerto esté cerrado.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
*/
WORD __stdcall cmdTestConnection(SHORT timeout);

/**
* Envía la orden de realizar una venta y espera la respuesta de la misma en forma
* sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
*
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPurchase(vpiPurchaseIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Envía la orden de realizar una venta y espera la respuesta de la misma en forma
* sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecución sea
* exitosa.
*
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. Se completa dentro de la función
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdVoid(vpiVoidIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Envía la orden de realizar una devolución y espera la respuesta de la misma en
* forma sincrónica.La aplicación queda esperando hasta tenga la respuesta o bien
* expire el timeout especificado.El puerto debe estar abierto para que la ejecución
* sea exitosa.
*
* @param input Estructura con los datos de entrada de la devolución.
* @param output Estructura con los datos de respuesta de la devolución. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexión exitosa.
* @return VPI_FAIL No se pudo enviar el comando.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_ISSUER El código de tarjeta no existe.
* @return VPI_INVALID_PLAN El código de plan no existe.
* @return VPI_TRX_CANCELED Transacción cancelada por el usuario.
* @return VPI_DIF_CARD La tarjeta deslizada por el usuario no coincide con la pedida.
* @return VPI_INVALID_CARD La tarjeta deslizada no es válida.
* @return VPI_EXPIRED_CARD La tarjeta deslizada está vencida.
* @return VPI_ERR_COM El POS no pudo comunicarse con el host.
* @return VPI_ERR_PRINT El POS no pudo imprimir el ticket.
* @return VPI_INVALID_IN_CMD Nombre del comando inexistente.
* @return VPI_INVALID_IN_LEN Largo de los parámetros inválido para este comando.
* @return VPI_INVALID_IN_PARAM Formato de algún parámetro no es correcto.
* @return VPI_INVALID_OUT_CMD Nombre del comando devuelto no coincide con el enviado.
* @return VPI_INVALID_OUT_LEN Largo de los parámetros devueltos inválido para este comando.
* @return VPI_INVALID_OUT_PARAM Formato de algún parámetro devuelto no es correcto.
* @return VPI_GENERAL_FAIL Error general en la operación.
*/
WORD __stdcall cmdRefund(vpiRefundIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Envía la orden de realizar una anulación de devolución y espera la respuesta
* de la misma en forma sincrónica.La aplicación queda esperando hasta tenga la
* respuesta o bien expire el timeout especificado.El puerto debe estar abierto
* para que la ejecución sea exitosa.
*
* @param input Estructura con los datos de entrada de la anulación.
* @param output Estructura con los datos de respuesta de la anulación. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdRefundVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, SHORT timeout);

/**
* Envía la orden de realizar un cierre de lote. La aplicación queda esperando hasta
* tenga la respuesta o bien expire el timeout especificado. El puerto debe estar
* abierto para que la ejecución sea exitosa.
*
* @param output Estructura con el resultado de la operación contra el host. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_TRX_CANCELED
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdBatchClose(vpiBatchCloseOut_t* output, SHORT timeout);

/**
* Envía la orden de obtener la información de la última transacción realizada
* y espera la respuesta de la misma en forma sincrónica.La aplicación queda
* esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecución sea exitosa.
* @param trxCode Código del tipo de transacción: VPI_PURCHASE, VPI_VOID,
VPI_REFUND, VPI_REFUND_VOID
*
* @param output  Estructura con los datos de respuesta de la última transacción realizada.
*				 Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_INVALID_PLAN
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdGetLastTrxData(WORD* trxCode, vpiTrxOut_t* output, SHORT timeout);

/**
* Envía la orden de obtener un determinado registro, con los totales por tarjeta
* del último cierre realizado y espera la respuesta de la misma en forma
* sincrónica.Para obtener todos los registros se debe hacer un ciclo desde 0
* hasta que el código de respuesta sea distinto de VPI_MORE_REC. La aplicación queda esperando
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe
* estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la información del registro que quiero.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe.
* @return VPI_TRX_CANCELED Transacción cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdGetBatchCloseData(WORD index, vpiBatchCloseDataOut_t* output, SHORT timeout);

/**
* Envía la orden de re-imprimir el ticket de la última transacción.La aplicación queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe
* estar abierto para que la ejecución sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPrintTicket(SHORT timeout);

/**
* Envía la orden de re-imprimir el ticket del último cierre de lote. La aplicación queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe estar
* abierto para que la ejecución sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPrintBatchClose(SHORT timeout);

/**
* Envía el comando para obtener un registro de la tabla de tarjetas del POS y espera
* la respuesta de la misma en forma sincrónica. Para obtener todos los registros se
* debe hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda  esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos de la tarjeta. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall cmdGetIssuer(WORD index, vpiIssuerOut_t* output, SHORT timeout);

/**
* Envía el comando para obtener un registro de la tabla de planes del POS y espera la
* respuesta de la misma en forma sincrónica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el código de respuesta sea distinto de VPI_MORE_REC.
* La aplicación queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecución sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la función.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall cmdGetPlan(WORD index, vpiPlanOut_t* output, SHORT timeout);

/**
* Envía el comando para setear un timeout global de respuesta al POS; permitiendo de esta 
* forma ajustar el valor del timeout de respuesta por defecto del POS según las necesidades 
* y características tanto del POS como la aplicación del integrador.
*
* @param timeout Tiempo de espera por defecto de las futuras respuestas, en segundos.
*/
WORD __stdcall cmdSetTimeout(SHORT timeout);

#endif //_VPIPC_H_