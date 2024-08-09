# Códigos de respuesta
````c
/**
* Codigos de retorno de las funciones
*/
#define VPI_OK                  0   // Comando procesado
#define VPI_MORE_REC            1   // Comando procesado, pero faltan registros
#define VPI_FAIL                11  // El comando no pudo ser enviado
#define VPI_TIMEOUT_EXP         12  // Tiempo de espera agotado.
#define VPI_INVALID_ISSUER      101 // El código de tarjeta no existe.
#define VPI_INVALID_TICKET      102 // El número de cupón no existe.
#define VPI_INVALID_PLAN        103 // El código de plan no existe.
#define VPI_INVALID_INDEX       104 // No existe el indice
#define VPI_EMPTY_BATCH         105 // El lote del POS se encuentra vacío.
#define VPI_TRX_CANCELED        201 // Transacción cancelada por el usuario.
#define VPI_DIF_CARD            202 // La tarjeta deslizada por el usuario no coincide con la pedida.
#define VPI_INVALID_CARD        203 // La tarjeta deslizada no es válida.
#define VPI_EXPIRED_CARD        204 // La tarjeta deslizada está vencida.
#define VPI_INVALID_TRX         205 // La transacción original no existe. 
#define VPI_ERR_COM             301 // El POS no pudo comunicarse con el host.
#define VPI_ERR_PRINT           302 // El POS no pudo imprimir el ticket.
#define VPI_INVALID_IN_CMD      901 // Nombre del comando inexistente.
#define VPI_INVALID_IN_PARAM    902 // Formato de algún parámetro de entrada no es correcto.
#define VPI_INVALID_OUT_CMD     903 // El comando enviado por
#define VPI_GENERAL_FAIL        909 // Error general en la operación.

````

---
#### Otros enlaces
- [Principal](../README.md).
- [Manejo de puertos](../Funcionalidades/Puertos.md)
- [Prueba de comunicación](../Funcionalidades/ComTest.md)
- [Venta](../Funcionalidades/Venta.md).
- [Venta + Extracción](../Funcionalidades/Venta+Extracción.md).
- [Venta con QR](../Funcionalidades/VentaQR.md) + pago con transferencias.
- [Anulación](../Funcionalidades/Anulacion.md)
- [Cierre de lote](../Funcionalidades/cierreLote.md).
- [Devolución](../Funcionalidades/Devolucion.md).
- [Consulta de último cierre de lote](../Funcionalidades/consultaCierre.md).
- [Consulta de última transacción](../Funcionalidades/consultaUltTransaccion.md).
- [Consulta de tarjetas](../Funcionalidades/consultaTarjetas.md) disponibles para operar.
- [Consulta de planes](../Funcionalidades/consultaPlanes.md) a aplicar por tarjeta.