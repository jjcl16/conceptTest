# Códigos de respuesta del Autorizador

|       hostRespCode        |           Significado                 |            Observación          
|:-------------------------:|:-------------------------------------:|:--------------------------------:|
|          00               |APROBADA (authno)                      |Operación aprobada, emitir cupón (cargo o ticket).
|          01               |PEDIR AUTORIZACION                     |Solicitar autorización telefónica, en caso de aprobada, cargar el código obtenido y dejar la operación en OFFLINE.
|          02               |PEDIR AUTORIZACION                     |Idem punto anterior.
|          03               |COMERCIO INVALIDO                      |Verificar parámetros del sistema, código de comercio mal cargado
|          04               |CAPTURAR TARJETA                       |Denegada, capturar la tarjeta.
|          05               |DENEGADA                               |Denegada.
|          07               |RETENGA Y LLAME                        |Denegada, llamar al Centro de Autorizaciones.
|          08               |APROBADA PEDIR IDENT.                  |
|          11               |APROBADA                               |Operación aprobada, emitir cupón (cargo o ticket).
|          12               |TRANSAC. INVALIDA                      |Verificar el sistema, transacción no reconocida en el sistema.
|          13               |MONTO INVALIDO                         |Verificar el sistema, error en el formato del campo importe.
|          14               |TARJETA INVALIDA                       |Denegada, tarjeta no corresponde.
|          19               |REINICIE OPERACIÓN                     |
|          25               |NO EXISTE ORIGINAL                     |Denegada, registro no encontrado en el archivo de  transacciones.
|          30               |ERROR EN FORMATO                       |Verificar el sistema, error en el formato del mensaje.
|          38               |EXCEDE ING. DE PIN                      |Denegada, excede cantidad de reintentos de PIN  permitidos.
|          43               |RETENER TARJETA                        |Denegada, retener tarjeta.
|          45               |NO OPERA EN CUOTAS                     |Denegada, tarjeta inhibida para operar en cuotas.
|          46               |TARJETA NO VIGENTE                     |Denegada, tarjeta no está vigente aún.
|          47               |PIN REQUERIDO                          |Denegada, tarjeta requiere ingreso de PIN.
|          48               |EXCEDE MAX. CUOTAS                     |Denegada, excede cantidad máxima de cuotas permitida.
|          49               |ERROR FECHA VENCIM.                    |Verificar el sistema, error en formato de fecha de expiración (vto)
|          50               |ENTREGA SUPERA LIMIT                   |Denegada, el monto de ENTREGA ingresado está fuera de los límites permitidos. Verifique el monto ingresado.
|          51               |FONDOS INSUFICIENTES                   |Denegada, no posee fondos suficientes.
|          53               |CUENTA INEXISTENTE                     |Denegada, no existe cuenta asociada.
|          54               |TARJETA VENCIDA                        |Denegada, tarjeta expirada.
|          55               |PIN INCORRECTO                         |Denegada, código de identificación personal es incorrecto.
|          56               |TARJ. NO HABILITADA                    |Denegada, emisor no habilitado en el sistema.
|          57               |TRANS. NO PERMITIDA                    |Verificar el sistema, transacción no permitida a dicha  tarjeta.
|          58               |SERVICIO INVALIDO                      |Verificar el sistema, transacción no permitida a dicha terminal.
|          61               |EXCEDE LIMITE                          |Denegada, excede límite remanente de la tarjeta.
|          65               |EXCEDE LIM. TARJETA                    |Denegada, excede límite remanente de la tarjeta.
|          76               |LLAMAR AL EMISOR – ERROR – DESC. PROD. |Solicitar autorización telefónica, en caso de ser aprobada, cargar el código obtenido y dejar la operación en OFFLINE.
|          77               |ERROR PLAN/CUOTAS – ERROR  RECONC.     |Denegada, cantidad de cuotas inválida para el plan seleccionado.
|          85               |APROBADA – LOTE NO ENCONTRADA          |Operación aprobada, emitir cupón (cargo o ticket).
|          88               |APROB. CLIENTE LLAME                   |
|          89               |TERMINAL INVALIDA                      |Denegada, número de terminal no habilitado por el Emisor.
|          91               |EMISOR FUERA LINEA                     |Solicitar autorización telefónica, en caso de ser aprobada, cargar el código obtenido y dejar la operación en OFFLINE.
|          94               |NRO. SEC. DUPLICAD                     |Denegada. Error en mensaje. Envíe nuevamente la transacción incrementando en uno el system trace de la misma.
|          95               |RE-TRANSMITIENDO                       |Diferencias en la conciliación del cierre, envíe Batch Upload.
|          96               |ERROR EN SISTEMA – MENSAJE INVALIDO    |Mal funcionamiento del sistema. Solicitar autorización telefónica.
|          BB               |COMP NO DISPONILE INTENTE MAS TARDE    |El host responde este codgo cuando la captura de lote no esta disponible. EL terminal podrá seguir operando pero no será posible efectuar el cierre de lote.
|          XX               |RECHAZADA (codnum)                     |Denegada, cualquier otro código no contemplado en tabla.



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