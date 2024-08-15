# Venta

La venta es la principal transacción a realizar con la terminal, existen la posibilidad de llevarla a cabo de dos formas:

- Realizar la transacción con cualquier marca de tarjeta.
- Realizar la transacción con una marca de tarjeta en especifico.

En ambas formas se utiliza el método **vpiPurchaseMark** de la libreria de integración.

````c 
Int vpiPurchaseMark(vpiPurchaseIn_t* input, vpiTrxMarkOut1_t* output, LONG timeout)
````

Este método cuenta con dos estructuras como parámetros:

La información que se envia a la terminal con los datos de la transacción, la estructura de entrada, vpiPurchaseIn_t:  
````c
typedef struct PURCHASE_IN{
	LPSTR amount;           // Monto x100  
	LPSTR receiptNumber;    // Número de factura  
	LPSTR instalmentCount;  // Cant. de cuotas  
	LPSTR issuerCode;       // Código de tarjeta  
	LPSTR planCode;         // Código de plan  
	LPSTR tip;              // Propina x100
	LPSTR merchantCode;     // Código de comercio a utilizar
	LPSTR merchantName;     // Razón social del comercio
	LPSTR cuit;             // CUIT del comercio
	char  linemode;         // transaccion Online (1)
}vpiPurchaseIn_t;  
````
Cumpliendo con las siguientes caracteristicas:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   amount          |       12          |
|   receiptNumber   |       12          |  
|   instalmentCount |       2           |
|   issuerCode      |       3           |
|   planCode        |       1           |
|   tip             |       12          |
|   merchantCode    |       15          |
|   merchantName    |       23          |
|   cuit            |       23          |
|   linemode        |       1           |

Estructura de salida, vpiTrxMarkOut1_t:
````c
typedef struct TRXMARK1_OUT {    
    LPSTR hostRespCode;     // Código de respuesta del host   
    LPSTR hostMessage;      // Mensaje de respuesta del host   
    LPSTR authCode;         // Número de autorización   
    LPSTR ticketNumber;     // Número de cupón   
    LPSTR batchNumber;      // Número de lote   
    LPSTR customerName;     // Nombre del tarjeta-habiente   
    LPSTR panLast4;         // Ultimo 4 digitos de la tarjeta   
    LPSTR panFirst6;        // Primeros 6 digitos de la tarjeta	
    LPSTR date;             // Fecha de la transacción (DD/MM/AAAA)  
    LPSTR time;             // Hora de la transaccion (HH:MM:SS)
    LPSTR terminalID;       // Número de Terminal
    LPSTR issuerCode;       // Código de tarjeta
    LPSTR merchantCode;	    // Código de comercio
    LPSTR aipEmv;           // Aip para EMV
    LPSTR appEmv;           // App para EMV
    LPSTR promoMsg;         // Mensaje promocional
}vpiTrxMarkOut1_t;
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
|   panLast4        |        4          |
|   panFirst6       |        6          |
|   date            |        10         |
|   time            |        8          |
|   terminalID      |        8          |
|   issuerCode      |        3          |
|   merchantCode    |        15         |
|   aipEmv          |        15         |
|   appEmv          |        15         |
|   promoMsg        |        200        |

## Transacción sin restricción de marca de tarjeta 
Para realizar una transacción con cualquier marca de tarjeta, siempre y cuando sea una marca que este dada de alta en la terminal, se debe indicar en el parámetro **issuerCode** el código **"VVI"** del vpiPurchaseIn_t. 

## Transacción con una marca de tarjeta en especifico 
Para realizar una transacción con una marca de tarjeta en especifico, se debe indicar en el parámetro **issuerCode** del vpiPurchaseIn_t el código correspondiente.

Para conocer los issuerCode o códigos de tarjetas disponibles para transaccionar en la terminal, se puede realizar la [consulta de tarjetas](./consultaTarjetas.md)

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
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas.

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