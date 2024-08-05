Attribute VB_Name = "VpiPc"
Option Explicit

' Prisma Medios de pago
' 06/11/2022
' version compatible con DLL ver 2.0.0.17
'




'Definición de códigos de resultado
'----------------------------------
Public Const VPI_OK = 0               ' Operacion exitosa
Public Const VPI_MORE_REC = 1         ' Operacion exitosa, pero faltan registros

Public Const VPI_FAIL = 11            ' El comando no pudo ser enviado
Public Const VPI_TIMEOUT_EXP = 12     ' Tiempo de espera agotado.

Public Const VPI_INVALID_ISSUER = 101 ' El código de tarjeta no existe.
Public Const VPI_INVALID_TICKET = 102 ' El número de cupón no existe.
Public Const VPI_INVALID_PLAN = 103   ' El código de plan no existe.
Public Const VPI_INVALID_INDEX = 104  ' No existe el indice
Public Const VPI_EMPTY_BATCH = 105    ' El lote del POS se encuentra vacío.

Public Const VPI_TRX_CANCELED = 201   ' Transacción cancelada por el usuario.
Public Const VPI_DIF_CARD = 202       ' La tarjeta deslizada por el usuario no coincide con la pedida.
Public Const VPI_INVALID_CARD = 203   ' La tarjeta deslizada no es válida.
Public Const VPI_EXPIRED_CARD = 204   ' La tarjeta deslizada está vencida.
Public Const VPI_INVALID_TRX = 205    ' La transacción original no existe.

Public Const VPI_ERR_COM = 301        ' El POS no pudo comunicarse con el host.
Public Const VPI_ERR_PRINT = 302      ' El POS no pudo imprimir el ticket.

Public Const VPI_INVALID_IN_CMD = 901     ' Nombre del comando inexistente.
Public Const VPI_INVALID_IN_PARAM = 902   ' Formato de algún parámetro de entrada no es correcto.
Public Const VPI_INVALID_OUT_CMD = 903    ' El comando enviado por

Public Const VPI_GENERAL_FAIL = 909   ' Error general en la operación.


'Codigos de las operaciones
'--------------------------
Public Const VPI_PURCHASE = 1         ' Venta
Public Const VPI_VOID = 2             ' Anulación de venta
Public Const VPI_REFUND = 3           ' Devolución
Public Const VPI_REFUND_VOID = 4      ' Anulación de devolución

'Timeouts
'--------
Public Const VPI_TIMEOUT_STD = 3000       ' Timeout mínimo 3 segundos


'Defincion de tipos
'------------------
Type vpiComParams_t
    com As String
    baudRate As Integer
    byteSize As Integer
    parity As Byte
    stopBits As Integer
End Type

Type vpiPurchaseIn_t
    amount As String          ' Monto *100
    receiptNumber As String   ' Número de factura
    instalmentCount As String ' Cant. de cuotas
    issuerCode As String      ' Código de tarjeta
    planCode As String        ' Código de plan
    tip As String             ' Propina *100
    merchantCode As String    ' Código de comercio
    merchantName As String    ' Razon social del comercio
    cuit As String            ' CUIT del comercio
    linemode As Byte          ' Offline u Online
End Type


Type vpiVoidIn_t
    originalTicket As String  ' Número de cupón de trx. original
    issuerCode As String      ' Código de tarjeta
    merchantName As String    ' Razon social del comercio
    cuit As String            ' CUIT del comercio
End Type

Type vpiRefundIn_t
     amount As String           ' Monto *100
     instalmentCount As String  ' Cant. de cuotas
     issuerCode As String       ' Código de tarjeta
     planCode As String         ' Código de plan
     originalTicket As String   ' Nro. ticket de la trx. original
     originalDate As String     ' Fecha de la trx. original
     receiptNumber As String    ' Número de factura
     merchantCode As String     ' Código de comercio
     merchantName As String     ' Razon social del comercio
     cuit As String             ' CUIT del comercio
     linemode As Byte         ' Offline u Online
End Type

'////////////////////
' FIDELIDAD CONSULTA
'////////////////////

Type vpiLoyaltyBalanceIn_t
    productCode As String     ' CODIGO DE PRODUCTO
    issuerCode As String      ' Código de tarjeta
    merchantCode As String    ' Código de comercio
    merchantName As String    ' Razon social del comercio
    cuit As String            ' CUIT del comercio
End Type


'////////////////////
' FIDELIDAD REDIMIR
'////////////////////

Type vpiLoyaltyRedeemIn_t
    productCode As String     ' CODIGO DE PRODUCTO
    amount As String          ' Monto *100
    issuerCode As String      ' Código de tarjeta
    merchantCode As String    ' Código de comercio
    merchantName As String    ' Razon social del comercio
    cuit As String            ' CUIT del comercio
End Type

'//////////////////////////
' FIDELIDAD ANULAR REDIMIR
'/////////////////////////

Type vpiLoyaltyVoidIn_t
    originalTicket As String  ' Número de cupón de trx. original
    issuerCode As String      ' Código de tarjeta
    productCode As String     ' CODIGO DE PRODUCTO
End Type

'---------------------------------------------------------------------------------------------------------------------------------------

Type vpiPriOut_t
    issuerCode As String      ' Código de tarjeta\
    panFirst6 As String       ' Primeros 6 digitos de la tarjeta
    panLast4 As String        ' Ultimo 4 digitos de la tarjeta
    terminalId As String      ' Terminal ID
End Type

Type vpiTrxOut_t
    hostRespCode As String  ' Código de respuesta del host
    hostMessage As String   ' Mensaje de respuesta del host
    authCode As String      ' Número de autorización
    ticketNumber As String  ' Número de cupón
    batchNumber As String   ' Número de lote
    customerName As String  ' Nombre del tarjeta-habiente
    panFirst6 As String     ' Primeros 6 digitos de la tarjeta
    'MOD ELDAR
    panLast4 As String      ' Ultimo 4 digitos de la tarjeta
    'MOD ELDAR
    
    date As String          ' Fecha de la transacción
    time As String          ' Hora de la transaccion
    terminalId As String    ' Terminal ID
End Type

Type vpiBatchCloseOut_t
    hostRespCode As String  ' Código de respuesta del host
    date As String          ' Fecha de la transacción
    time As String          ' Hora de la transaccion
    terminalId As String    ' Terminal ID
End Type

' 28 Sept 2022 GetVersion
Type vpiGetVersion_t
    versionMessage As String  ' Código de respuesta del host
End Type

Type vpiBatchCloseDataOut_t
    recIndex As Integer         ' Índice del registro.
    acquirerCode As String      ' Código de procesador.
    batchNumber As String       ' Número de lote.
    issuerCode As String        ' Código de tarjeta
    purchaseCount As String     ' Cantidad de ventas.
    purchaseAmount As String    ' Monto total de ventas.
    voidCount As String         ' Cantidad anulaciones de venta.
    voidAmount As String        ' Monto total de anulaciones.
    refundCount As String       ' Cantidad de devoluciones venta.
    refundAmount As String      ' Monto total de devoluciones.
    refvoidCount As String      ' Cantidad anulaciones devolución.
    refvoidAmount As String     ' Monto total anul. devolución.
    date As String              ' Fecha del ultimo cierre
    time As String              ' Hora del ultimo cierre
    terminalId As String        ' Terminal ID
End Type

Type vpiBatchCloseDataGroupOut_t
    recIndex As Integer         ' Índice del registro.
    acquirerCode As String      ' Código de procesador.
    batchNumber As String       ' Número de lote.
    groupName As String         ' Nombre del grupo.
    issuerCode As String        ' Código de tarjeta
    purchaseCount As String     ' Cantidad de ventas.
    purchaseAmount As String    ' Monto total de ventas.
    voidCount As String         ' Cantidad anulaciones de venta.
    voidAmount As String        ' Monto total de anulaciones.
    refundCount As String       ' Cantidad de devoluciones venta.
    refundAmount As String      ' Monto total de devoluciones.
    refvoidCount As String      ' Cantidad anulaciones devolución.
    refvoidAmount As String     ' Monto total anul. devolución.
    date As String              ' Fecha del ultimo cierre
    time As String              ' Hora del ultimo cierre
    terminalId As String        ' Terminal ID
End Type

Type vpiIssuerOut_t
    recIndex  As Integer       ' Índice del registro.
    acquirerCode As String     ' Código de procesador.
    issuerCode As String       ' Código de tarjeta
    issuerName As String       ' Nombre de la tarjeta
    maxInstCount As String     ' Maxima cantidad de cuotas
    terminalId As String       ' Terminal ID
End Type

Type vpiPlanOut_t
    recIndex  As Integer       ' Índice del registro.
    issuerCode  As String      ' Código de tarjeta
    planCode As String         ' Código de plan
    planLabel  As String       ' Nombre del plan
    terminalId As String       ' Terminal ID
End Type


Type vpiLoyaltyOut_t
    hostRespCode As String  ' Código de respuesta del host
    hostMessage As String   ' Mensaje de respuesta del host
    authCode As String      ' Número de autorización
    ticketNumber As String  ' Número de cupón
    batchNumber As String   ' Número de lote
    customerName As String  ' Nombre del tarjeta-habiente
    panFirst6 As String     ' Primeros 6 digitos de la tarjeta
    panLast4 As String      ' Ultimo 4 digitos de la tarjeta
    date As String          ' Fecha de la transacción
    time As String          ' Hora de la transaccion
    terminalId As String    ' Terminal ID
    loyaltyAmount As String ' Saldo de unidades
End Type

Type vpiOteOut_t
    recIndex  As Integer       ' Índice del registro.
    acquirerCode As String     ' Código de procesador.
    issuerCode  As String      ' Código de tarjeta
    issuerName As String       ' Nombre de la tarjeta
    merchNumber As String      ' Numero de establecimiento
    groupName As String        ' Nombre del Grupo
    terminalId As String       ' Terminal ID
End Type

Type vpiTrxMarkOut1_t
    hostRespCode As String 'Código de respuesta del host
    hostMessage As String  ' Mensaje de respuesta del host
    authCode As String     ' Número de autorización
    ticketNumber As String ' Número de cupón
    batchNumber As String  ' Número de lote
    customerName As String ' Nombre del tarjeta-habiente
    panLast4 As String     ' Ultimo 4 digitos de la tarjeta
    panFirst6 As String    ' Primeros 6 digitos de la tarjeta
    date As String         ' Fecha de la transacción
    time As String         ' Hora de la transaccion
    terminalId As String   ' Numero de Terminal
    issuerCode As String   ' Código de tarjeta
    merchantCode As String ' Código de comercio
    aipEmv As String       ' Aip para EMV
    appEmv As String       ' App para EMV
    promoMsg As String     ' Mensaje promocional
End Type

Type vpiTrxMarkOut_t
    hostRespCode As String 'Código de respuesta del host
    hostMessage As String  ' Mensaje de respuesta del host
    authCode As String     ' Número de autorización
    ticketNumber As String ' Número de cupón
    batchNumber As String  ' Número de lote
    customerName As String ' Nombre del tarjeta-habiente
    panLast4 As String     ' Ultimo 4 digitos de la tarjeta
    panFirst6 As String    ' Primeros 6 digitos de la tarjeta
    date As String         ' Fecha de la transacción
    time As String         ' Hora de la transaccion
    terminalId As String   ' Numero de Terminal
    issuerCode As String   ' Código de tarjeta
    aipEmv As String       ' Aip para EMV
    appEmv As String       ' App para EMV
    promoMsg As String     ' Mensaje promocional
End Type

Type vpiCcdMarkOut_t
    hostRespCode As String ' Código de respuesta del host
    hostMessage As String  ' Mensaje de respuesta del host
    authCode As String     ' Número de autorización
    ticketNumber As String ' Número de cupón
    batchNumber As String  ' Número de lote
    customerName As String ' Nombre del tarjeta-habiente
    panLast4 As String     ' Ultimo 4 digitos de la tarjeta
    panFirst6 As String    ' Primeros 6 digitos de la tarjeta
    date As String         ' Fecha de la transacción
    time As String         ' Hora de la transaccion
    terminalId As String   ' Numero de Terminal
    issuerCode As String   ' Código de tarjeta
    merchantCode As String ' Código de comercio
    aipEmv As String       ' Aip para EMV
    appEmv As String       ' App para EMV
    instCount1 As String   ' Cantidad de cuotas
    valueCount1 As String  ' Valor de la Cuota
    TNA1 As String         ' TNA (3 enteros y 2 decimales)
    instCount2 As String   ' Cantidad de cuotas
    valueCount2 As String  ' Valor de la Cuota
    TNA2 As String         ' TNA (3 enteros y 2 decimales)
    instCount3 As String   ' Cantidad de cuotas
    valueCount3 As String  ' Valor de la Cuota
    TNA3 As String         ' TNA (3 enteros y 2 decimales)
    instCount4 As String   ' Cantidad de cuotas
    valueCount4 As String  ' Valor de la Cuota
    TNA4 As String         ' TNA (3 enteros y 2 decimales)
    instCount5 As String   ' Cantidad de cuotas
    valueCount5 As String  ' Valor de la Cuota
    TNA5 As String         ' TNA (3 enteros y 2 decimales)
    emisorName As String   ' Nombre del Banco emisor
    promoMsg As String     ' Mensaje promocional
End Type

Type vpiRevOut_t
    respCode As String    'Codigo de respuesta.
    respMsg As String     'Mensaje de respuesta.
    date As String        ' Fecha ("DD/MM/AAAA")
    time As String        ' Hora ("HH:MM:SS")
    terminalId As String  'Terminal ID
End Type

Type vpiRevDeleteIn_t
    amount As String           ' Monto *100
    instalmentCount As String  ' Cant. de cuotas
    issuerCode As String       ' Código de tarjeta
    planCode As String         ' Código de plan
    tip As String              ' Propina *100
    merchantCode As String     ' Código de comercio a utilizar
    panFirst6 As String        ' Primeros 6
    panLast4 As String         ' Ultimos 4
    issuerCodeVRE As String    ' Código de tarjeta VRE
End Type

Type vpiIesOut_t
    Index As Integer         'Índice del registro.
    respCode As String       'Codigo de respuesta.
    issuerCode As String     'Código de tarjeta
    issuerName As String     'Nombre de la tarjeta
    merchant As String       'Numero de establecimiento.
    nameGroup As String      'Nombre del Grupo.
    terminalId As String     'Terminal ID.
End Type

Type vpiIesIn_t
    issuerCode As String     'Código de tarjeta
    newReg As String         'Ultimo registro
    nameGroup As String      'Nombre del Grupo.
    merchant As String       'Numero de establecimiento.
End Type


'ADD 1.18 Marzo 2020
Type vpiQrcOut_t
    respCode  As String     'Código de respuesta del host.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”).
    trxHr As String         'Hora de la transacción(“HH:MM:SS”).
    terminalId As String    'Terminal id.
    medioPago As String     'Medio de Pago.
    cardCod As String       'Código de Tarjeta.
    idUnico As String       'ID Unico.
    idBanco As String       'ID Banco.
    emisorDscr As String    'Descripción de emisor.
    'ADD Clarin
    impTotal As String     'Importe Total
    impCobrado As String     'Importe cobrado
    codTarjBenef As String     'Código de Tarjeta Beneficio.
    impDescuento As String     'Importe descontado
    'ADD Clarin FIN
End Type

Type vpiQrcIn_t
    idQR As String 'Id del QR consultado
End Type

Type vpiQrtOut_t
    respCode As String   'Código de respuesta del Terminal.
    respMsg As String    'Mensaje de respuesta.
    idQR As String       'QR ID.
    trxDate As String    'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String      'Hora de la transacción(“HH:MM:SS”)
    terminalId As String 'Terminal id
End Type

Type vpiQrtIn_t
    ammount As String        'Monto
    ticketNmb As String      'Número de factura.
    cantCoutas  As String    'Cantidad de cuotas.
    planCod As String        'Código de plan.
    voidId As String         'QR ID utilizado para anulación
    refundId As String       'ID Para devoluciones
    trxDate As String        'Fecha de la transacción(“DD / MM / AAAA”)
    imprimeTckt As String    'Imprime ticket.
    nombreComercio As String 'Nombre de comercio.
    cuitComercio As String   'Cuit del comercio
    tipoQR As String         'Tipo de QR
    merchants As String      'Merchants
End Type
'ADD 1.18 Marzo 2020 FIN



Type vpiQrzOut_t
    respCode As String   'Código de respuesta del Terminal.
    respMsg As String    'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”).
    trxHr As String         'Hora de la transacción(“HH:MM:SS”).
    terminalId As String    'Terminal id.
    cardCod As String       'Código de Tarjeta.
    impTotal As String     'Importe Total
    impCobrado As String     'Importe cobrado

End Type

Type vpiQrzIn_t
    ammount As String        'Monto
    cantCoutas  As String    'Cantidad de cuotas.
    planCod As String        'Código de plan.
End Type



'ADD Fidelidad
Type vpiFcoOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    uniAcumm As String      'Unidades acumuladas
End Type

Type vpiFcoIn_t
    prodCod As String           'Codigo de producto
    cardCod As String           'Codigo de tarjeta
    codComercio As String       'Codigo de comercio.
    nombreComercio As String    'Nombre de comercio.
    cuitComercio As String      'Cuit del comercio
End Type

Type vpiFreOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    saldoUni As String      'Saldo de unidades
End Type




    
Type vpiFCAOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    saldoUni As String      'Saldo de unidades
    operationCode As String 'codigo de operacion
End Type

Type vpiFACOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    saldoUni As String      'Saldo de unidades
    operationCode As String 'codigo de operacion
End Type

Type vpiFANOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    saldoUni As String      'Saldo de unidades
    operationCode As String 'codigo de operacion
End Type


Type vpiFreIn_t
    prodCod As String           'Codigo de producto
    uniRed As String            'Unidades a redimir
    cardCod As String           'Codigo de tarjeta
    codComercio As String       'Codigo de comercio.
    nombreComercio As String    'Nombre de comercio.
    cuitComercio As String      'Cuit del comercio
End Type

Type vpiFCAIn_t
    prodCod As String           'Codigo de producto
    uniRed As String            'Unidades a redimir
    cardCod As String           'Codigo de tarjeta
    codComercio As String       'Codigo de comercio.
    nombreComercio As String    'Nombre de comercio.
    cuitComercio As String      'Cuit del comercio
End Type

Type vpiFACIn_t
    prodCod As String           'Codigo de producto
    uniAcum As String            'Unidades a acumular
End Type

Type vpiFANIn_t
    numCupon As String           'Codigo de producto
End Type

Type vpiFarOut_t
    respCode As String      'Código de respuesta del Terminal.
    respMsg As String       'Mensaje de respuesta.
    authCod As String       'Código de autorización
    cuponNmb As String      'Número de cupón
    loteNmb As String       'Número de lote.
    nombreCli As String     'Nombre del cliente.
    firstSix As String      'Primeros 6 dígitos de la tarjeta.
    lastFour As String      'Últimos 4 dígitos de la tarjeta.
    trxDate As String       'Fecha de la transacción(“DD / MM / AAAA”)
    trxHr As String         'Hora de la transacción(“HH:MM:SS”)
    terminalId As String    'Terminal id
    saldoUni As String      'Saldo de unidades
End Type

Type vpiFarIn_t
    prodCod As String   'Codigo de producto
    cardCod As String   'Codigo de tarjeta
    cuponNum As String  'Numero de cupon
End Type
'ADD Fidelidad FIN
Type vpiPurchaseGroupIn_t
    amount As String           ' Monto *100
    receiptNumber As String    ' Número de factura
    instalmentCount As String  ' Cant. de cuotas
    issuerCode As String       ' Código de tarjeta
    planCode As String         ' Código de plan
    tip As String              ' Propina *100
    groupName As String        ' Nombre del Grupo a utilizar
    merchantName As String     ' Razon social del comercio
    cuit As String             ' CUIT del comercio
    linemode As Byte          ' transaccion Online(1) o Offline(0)
End Type

Type vpiTrxGroupOut_t
     hostRespCode As String ' Código de respuesta del host
     hostMessage As String  ' Mensaje de respuesta del host
     authCode As String     ' Número de autorización
     ticketNumber As String ' Número de cupón
     batchNumber As String  ' Número de lote
     customerName As String ' Nombre del tarjeta-habiente
     panFirst6 As String    ' Primeros 6 digitos de la tarjeta
     panLast4 As String     ' Ultimo 4 digitos de la tarjeta
     date As String         ' Fecha de la transacción
     time As String         ' Hora de la transaccion
     terminalId As String   ' Numero de Terminal
     issuerCode As String   ' Código de tarjeta
     merchantCode As String ' Código de comercio
     aipEmv As String       ' Aip para EMV
     appEmv As String       ' App para EMV
     promoMsg As String     ' Mensaje promocional
End Type

'Declaración de funciones
'------------------------
Public Declare Function vpiOpenPort Lib "VpiPc.dll" (params As vpiComParams_t) As Integer

Public Declare Function vpiClosePort Lib "VpiPc.dll" () As Integer

Public Declare Function vpiTestConnection Lib "VpiPc.dll" () As Integer



Public Declare Function vpiPurchase Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxOut_t, timeout As Long) As Integer

Public Declare Function vpiVoid Lib "VpiPc.dll" (paramIn As vpiVoidIn_t, paramOut As vpiTrxOut_t, timeout As Long) As Integer

Public Declare Function vpiRefund Lib "VpiPc.dll" (paramIn As vpiRefundIn_t, paramOut As vpiTrxOut_t, timeout As Long) As Integer

Public Declare Function vpiRefundVoid Lib "VpiPc.dll" (paramIn As vpiVoidIn_t, paramOut As vpiTrxOut_t, timeout As Long) As Integer

Public Declare Function vpiBatchClose Lib "VpiPc.dll" (paramOut As vpiBatchCloseOut_t, timeout As Long) As Integer

' 28 Sept 2022 GetVersion Implementation FCO
Public Declare Function vpiGetVersion Lib "VpiPc.dll" (paramOut As Integer) As Integer

Public Declare Function vpiGetLastTrxData Lib "VpiPc.dll" (ByRef trxCode As Integer, paramOut As vpiTrxOut_t) As Integer

Public Declare Function vpiGetBatchCloseData Lib "VpiPc.dll" (ByVal recIndex As Integer, paramOut As vpiBatchCloseDataOut_t) As Integer

Public Declare Function vpiPrintTicket Lib "VpiPc.dll" () As Integer

Public Declare Function vpiPrintBatchClose Lib "VpiPc.dll" () As Integer

Public Declare Function vpiGetIssuer Lib "VpiPc.dll" (ByVal recIndex As Integer, paramOut As vpiIssuerOut_t) As Integer

Public Declare Function vpiGetPlan Lib "VpiPc.dll" (ByVal recIndex As Integer, paramOut As vpiPlanOut_t) As Integer

Public Declare Function vpiGetPANData Lib "VpiPc.dll" (paramPRIOut As vpiPriOut_t) As Integer

Public Declare Function vpiPurchaseExtraCash Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxOut_t, timeout As Long) As Integer

Public Declare Function vpiLoyaltyRedeem Lib "VpiPc.dll" (paramIn As vpiLoyaltyRedeemIn_t, paramOut As vpiLoyaltyOut_t, timeout As Long) As Integer

Public Declare Function vpiLoyaltyBalance Lib "VpiPc.dll" (paramIn As vpiLoyaltyBalanceIn_t, paramOut As vpiLoyaltyOut_t, timeout As Long) As Integer

Public Declare Function vpiGetOTE Lib "VpiPc.dll" (ByVal recIndex As Integer, paramOut As vpiOteOut_t) As Integer

Public Declare Function vpiPurchaseMark Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxMarkOut1_t, timeout As Long) As Integer

Public Declare Function vpiPurchaseExtraCashMark Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxMarkOut1_t, timeout As Long) As Integer

Public Declare Function vpiPurchaseCreditoDirecto Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxMarkOut1_t, timeout As Long) As Integer

Public Declare Function vpiConsultaCreditoDirecto Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiCcdMarkOut_t, timeout As Long) As Integer

Public Declare Function vpiPurchaseRev Lib "VpiPc.dll" (paramIn As vpiPurchaseIn_t, paramOut As vpiTrxMarkOut_t, timeout As Long) As Integer

Public Declare Function vpiDeleteRev Lib "VpiPc.dll" (paramIn As vpiRevDeleteIn_t, paramOut As vpiRevOut_t, timeout As Long) As Integer

Public Declare Function vpiGetIES Lib "VpiPc.dll" (paramIn As vpiIesIn_t, paramOut As vpiIesOut_t, timeout As Long) As Integer
'ADD 1.18 Marzo 2020
Public Declare Function vpiGetQRC Lib "VpiPc.dll" (paramIn As vpiQrcIn_t, paramOut As vpiQrcOut_t, timeout As Long) As Integer

Public Declare Function vpiGetQRT Lib "VpiPc.dll" (paramIn As vpiQrtIn_t, paramOut As vpiQrtOut_t, timeout As Long) As Integer
'ADD 1.18 Marzo 2020 FIN
'ADD Fidelidad
Public Declare Function vpiGetFCO Lib "VpiPc.dll" (paramIn As vpiFcoIn_t, paramOut As vpiFcoOut_t, timeout As Long) As Integer

Public Declare Function vpiGetFRE Lib "VpiPc.dll" (paramIn As vpiFreIn_t, paramOut As vpiFreOut_t, timeout As Long) As Integer

Public Declare Function vpiGetFAR Lib "VpiPc.dll" (paramIn As vpiFarIn_t, paramOut As vpiFarOut_t, timeout As Long) As Integer
'ADD Fidelidad FIN
Public Declare Function vpiPurchaseGroup Lib "VpiPc.dll" (paramIn As vpiPurchaseGroupIn_t, paramOut As vpiTrxGroupOut_t, timeout As Long) As Integer

Public Declare Function vpiPurchaseGroupExtraCash Lib "VpiPc.dll" (paramIn As vpiPurchaseGroupIn_t, paramOut As vpiTrxGroupOut_t, timeout As Long) As Integer

Public Declare Function vpiGetBatchCloseDataGroup Lib "VpiPc.dll" (ByVal recIndex As Integer, paramOut As vpiBatchCloseDataGroupOut_t) As Integer

Public Declare Function vpiGetQRZ Lib "VpiPc.dll" (paramIn As vpiQrzIn_t, paramOut As vpiQrzOut_t, timeout As Long) As Integer

' Public Declare Function vpiGetPOSVersion Lib "VpiPc.dll" (paramIn As vpiQrzIn_t, paramOut As vpiQrzOut_t, timeout As Long) As Integer
Public Declare Function vpiGetFCA Lib "VpiPc.dll" (paramIn As vpiFCAIn_t, paramOut As vpiFCAOut_t, timeout As Long) As Integer
' to do FAN
Public Declare Function vpiGetFAN Lib "VpiPc.dll" (paramIn As vpiFANIn_t, paramOut As vpiFANOut_t, timeout As Long) As Integer
Public Declare Function vpiGetFAC Lib "VpiPc.dll" (paramIn As vpiFACIn_t, paramOut As vpiFACOut_t, timeout As Long) As Integer

