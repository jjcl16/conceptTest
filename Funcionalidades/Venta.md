# Venta

La venta es la principal transacción a realizar con la terminal, existen la posibilidad de llevarla a cabo de dos formas:

- Realizar la transacción con cualquier marca de tarjeta.
- Realizar la transacción con una marca de tarjeta en especifico.

De ambas formas se utiliza el mismo método de la dll vpiPc:

`Int vpiPurchaseMark(vpiPurchaseIn_t* input, vpiPurchaseOut_t* output, LONG timeout)`

Esta función cuenta con dos estructuras como parámetros:


    vpiPurchaseIn_t {
        LPSTR amount;           //Monto
        LPSTR receiptNumber;    //Número de recibo
        LPSTR instalmentCount;  //Número de cuotas
        LPSTR issuerCode;       //Código de tarjeta
        LPSTR planCode;         //Código de plan
        LPSTR tip;              //Propina
        LPSTR merchantCode;     //Código de comercio 
        LPSTR merchantName;     //Nombre de comercio
        LPSTR cuit;             //CUIT del comercio
        char linemode;          //online
    }  
---    
    vpiPurchaseOut_t {
        LPSTR respcode;         //Código de respuesta del host.
        LPSTR respMsg;          //Mensaje promocional de respuesta. 
        LPSTR authCod;          //Código de autorización
        LPSTR cuponNmb;         //Número de cupón
        LPSTR customerName;     //Nombre del tarjeta-habiente 
        LPSTR lastFour;         //Últimos 4 dígitos de la tarjeta. 
        LPSTR firstSix;         //Primeros 6 dígitos de la tarjeta. 
        LPSTR trxDate;          //Fecha de la transacción(“DD/MM/AAAA”). 
        LPSTR trxHr;            //Hora de la transacción(“HH:MM:SS”). 
        LPSTR terminalID;       //Terminal id. 
        LPSTR cardCod;          //Código de Tarjeta. 
        LPSTR merchantCode      // Código de comercio 
        LPSTR aipEmv;           //Aip para EMV 
        LPSTR appEmv;           //App para EMV 
        LPSTR promoMsg;         // no usado 
    }
---
### Transacción con cualquier tarjeta 
Para realizar una transacción con cualquier tarjeta sin importar la marca, se debe indicar en el parámetro issuerCode el código "VVI" en el vpiPurchaseIn_t. 

### Transacción con una marca de tarjeta en especifico 
Para realizar una transacción con una marca de tarjeta en especifico, se debe indicar en el parámetro issuerCode el código correspondiente en el vpiPurchaseIn_t.
Para conocer los códigos de tarjetas disponibles para transaccionar en la terminal, se puede realizar la [consulta de tarjetas](Funcionalidades/tarjetas)
