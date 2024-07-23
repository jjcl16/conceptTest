# Consulta de último cierre de lote
Esta funcionalidad permite conocer la totalización, por marca y tipo de transacción, de las transacciones realizadas en el último cierre de lote.

Esta consulta se realiza con el método **vpiGetBatchCloseData** de la librería de integración.

````c
Int vpiGetBatchCloseData(WORD index, vpiBatchCloseDataOut_t * output)
````

Este método recibe como parámetros el indice a consultar y la estructura de salida, vpiBatchCloseDataOut_t :

````c
typedef struct BATCHCLOSEDATA_OUT{	
	WORD index;             // Índice del registro.   
	LPSTR acquirerCode;     // Código de procesador.   
	LPSTR batchNumber;      // Número de lote.   
	LPSTR issuerCode;       // Código de tarjeta   
	LPSTR purchaseCount;    // Cantidad de ventas.   
	LPSTR purchaseAmount;   // Monto total de ventas.   
	LPSTR voidCount;        // Cantidad anulaciones de venta.   
	LPSTR voidAmount;       // Monto total de anulaciones.   
	LPSTR refundCount;      // Cantidad de devoluciones venta.   
	LPSTR refundAmount;     // Monto total de devoluciones.   
	LPSTR refvoidCount;     // Cantidad anulaciones devolución.   
	LPSTR refvoidAmount;    // Monto total anul. devolución.
	LPSTR date;             // Fecha ("DD/MM/AAAA")  
	LPSTR time;             // Hora ("HH:MM:SS")
	LPSTR terminalID;       // Terminal id
}vpiBatchCloseDataOut_t;
````


Al ser un comando indexado, puedes consultar la sección de [comandos indexados](../Libreria/comandosIndexados.md) de la libreria de integración o bien el siguiente diagrama de flujos, que ejemplifica la [consulta de Tarjetas](consultaTarjetas.md) que tambien es un comando indexado.

![ejemplocomandos indexados](..\images\ComandosIndexados.PNG)

### Aclaración transferencias 3.0  
Para las transferencias al no existir una liquidación, ya que son inmediatas, no existe un cierre de lote que haya que presentar. Sin embargo, al consultar el último cierre y este incluya este tipo de operaciones, se incluirá un indice totalizando las operaciones realizadas con transferencias con el **issuerCode** 0PI.

## Posibles Retorno del Método
Los posibles valores de retorno del método son los siguientes:
````
VPI_OK
VPI_MORE_REC
VPI_FAIL
VPI_TIMEOUT_EXP
VPI_INVALID_INDEX 
VPI_TRX_CANCELED
VPI_INVALID_TRX
VPI_INVALID_IN_CMD 
VPI_INVALID_IN_LEN
VPI_INVALID_IN_PARAM
VPI_INVALID_OUT_CMD
VPI_INVALID_OUT_LEN
VPI_INVALID_OUT_PARAM
VPI_GENERAL_FAIL
````
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas
