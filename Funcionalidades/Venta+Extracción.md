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

Respecto a la estructura de salida, se comparte la misma que con el método de venta común.

Por último, tambien se comparte la capacidad de realizar la Venta + Extracción con una tarjeta en específico o con cualquier tarjeta (mientras sea débito o prepaga) con el issuerCode "**VVI**".

## Posibles Retorno del Método
Los posibles valores de retorno del método son los siguientes:
````c
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