# Venta

La venta es la principal transacción a realizar con la terminal, existen la posibilidad de llevarla a cabo de dos formas:

- Realizar la transacción con cualquier marca de tarjeta.
- Realizar la transacción con una marca de tarjeta en especifico.

De ambas formas se utiliza el mismo método de la dll vpiPc:

`Int vpiPurchaseMark(vpiPurchaseIn_t* input, vpiPurchaseOut_t* output, LONG timeout) `

