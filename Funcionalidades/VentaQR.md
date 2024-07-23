# Venta con QR

Esta funcionalidad permite a la terminal realizar ventas con QR, que al ser escaneado desde una billetera podría realizar el pago ya sea con Tarjetas de débito, crédito o transferencias. 

Para ello lo realizamos por medio del método **vpiGetQRZ** de la librería de integración.

`Int vpiGetQRZ(vpiQrzIn_t* input, vpiQrzOut_t* output, LONG timeout)`

Este método recibe como parametros dos estructuras:

La información que se envia a la terminal con los datos de la transacción, la estructura de entrada, vpiQrzIn_t:

````c
typedef struct QRZ_IN {
	LPSTR ammount;      //Monto
	LPSTR cantCoutas;   //Cantidad de cuotas.
	LPSTR planCod;	    //Código de plan.	
}vpiQrzIn_t;
````

Estructura de salida, vpiQrzOut_t:
````c
typedef struct QRZ_OUT {
	LPSTR respcode;         //Código de respuesta del host.
	LPSTR respMsg;          //Mensaje de respuesta. 
	LPSTR authCod;          //Código de autorización   
	LPSTR cuponNmb;         //Número de cupón
	LPSTR loteNmb;          //Número de lote.
	LPSTR lastFour;         //Últimos 4 dígitos de la tarjeta.
	LPSTR firstSix;         //Primeros 6 dígitos de la tarjeta.
	LPSTR trxDate;          //Fecha de la transacción(“DD / MM / AAAA”).
	LPSTR trxHr;            //Hora de la transacción(“HH:MM:SS”).
	LPSTR terminalID;       //Terminal id.
	LPSTR cardCod;	        //Código de Tarjeta.
	LPSTR impTotal;	        //Importe Total
	LPSTR impCobrado;       //Importe cobrado	
}vpiQrzOut_t;
````
El QR en PoS integrado no tiene la capacidad de restringir el pago a una marca de tarjeta en específico, la terminal va a mostrar un código QR estático y será el Gateway de QR quien habilitará las opciones de pago que correspondan según lo enviado en el vpiQrzIn_t, podemos ver esto en los [ejemplos](#ejemplos). 

## Transferencias 3.0
En caso de que la intención haya sido pagada con una transferencia, los valores de algunos parametros de la estructura de respuesta van a tener valores por defecto que son importantes de tener en cuenta.
- cardCod: 0PI
- lastFour: 0000
- firstSix: 000000

## Ejemplos:

Se tiene una terminal que permite operar con las siguientes marcas:
- Visa débito
- Visa crédito
- MasterCard Crédito
- Maestro
- CBU (Para transferencias 3.0)

### Escenario 1:
Se crea una intención con los siguientes parámetros (vpiQrzIn_t):
- ammount: 10000
- cantCoutas: 01
- planCod: 0

Está intención podría ser pagada con todos los medios de pagos con los que cuenta la terminal siempre y cuando el "billeterahabiente" tenga cargada en su billetera alguna de las tarjetas con que la terminal pueda operar o dinero en cuenta (para transferencias 3.0).

### Escenario 2:
Se crea una intención con los siguientes parámetros (vpiQrzIn_t):
- ammount: 10000
- cantCoutas: 03
- planCod: 0

Está intención solo podría ser pagada con tarjetas de crédito Visa o Mastercard, siempre y cuando el "billeterahabiente" tenga cargada en su billetera alguna de estas tarjetas, ya que son los unicos medios que tiene cargada la terminal (en este ejemplo) con los que se puede operar en cuotas.

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