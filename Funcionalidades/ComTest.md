# Prueba de comunicación
Existen dos métodos que se pueden implementar para chequear la comunicación. 

Para verificar que la comunicación entre la terminal y la caja este establecida de manera correcta, se puede utilizar el método **vpiTestConnection** de la librería de integración. 

````c
Int vpiTestConnection()
````

Por otro lado, con el método **vpiGetVersion** podemos identificar que tipo de PoS está conectada a la caja.

````c
Int vpiGetVersion(vpiVersionOut_t* output)
````

Este recibe una estructura de salida, vpiVersionOut_t:
````c
typedef struct GETVERSION_OUT {
	WORD version;  // Mensaje de respuesta de version 
} vpiVersionOut_t;
````

Para indentificar el PoS, lo hacemos dependiendo del parametro **version** de la estrutura de retorno.
````c
    Version         -----  version 
    Legacy          -----       1
    Interprete      -----       2
````
## Posibles Retorno del Método
Los posibles valores de retorno para ambos métodos son los siguientes:
````
VPI_OK
VPI_FAIL 
VPI_TIMEOUT_EXP
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