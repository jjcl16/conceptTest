# Venta + Extracción 

La venta con extracción hace referencia a la acción de realizar una venta y a su vez una extracción de efectivo o Extra Cash.

Para ello se hace uso del método **vpiPurchaseExtraCashMark** de la librería de integración.

`Int vpiPurchaseExtraCashMark(vpiPurchaseIn_t* input, vpiTrxMarkOut1_t* output, LONG timeout)`  

Como podemos ver, este método recibe como parámetro la misma estructura de entrada que el método de venta común, la diferencia acá radica en que en el campo **"tip"** se ingresaría el valor de la extracción de efectivo.

````c
typedef struct PURCHASE_IN{
	LPSTR amount;           // Monto x100  
	LPSTR receiptNumber;    // Número de factura  
	LPSTR instalmentCount;  // Cant. de cuotas  
	LPSTR issuerCode;       // Código de tarjeta  
	LPSTR planCode;         // Código de plan  
	LPSTR tip;              // Extracash x100
	LPSTR merchantCode;     // Código de comercio a utilizar
	LPSTR merchantName;     // Razón social del comercio
	LPSTR cuit;             // CUIT del comercio
	char  linemode;         // transaccion Online(1)
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

Respecto a la estructura de salida, se comparte la misma que con el método de [venta](./Venta.md).

Por último, tambien se comparte la capacidad de realizar la Venta + Extracción con una tarjeta en específico o con cualquier tarjeta (mientras sea débito o prepaga) con el issuerCode "**VVI**".

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