
---
# IrDA 4 click

> IrDA 4 Click is a compact add-on board that provides a cost-effective solution for sending and receiving IR serial data. This board features the TFBS4650, an infrared transceiver from Vishay Semiconductors. The transceiver includes a PIN photodiode, an infrared emitter, and a low-power integral circuit and complies with the IrDA physical layer specification. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irda4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/irda-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : UART type


# Software Support

We provide a library for the IrDA 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IrDA 4 Click driver.

#### Standard key functions :

- `irda4_cfg_setup` Config Object Initialization function.
```c
void irda4_cfg_setup ( irda4_cfg_t *cfg );
```

- `irda4_init` Initialization function.
```c
err_t irda4_init ( irda4_t *ctx, irda4_cfg_t *cfg );
```

#### Example key functions :

- `irda4_generic_write` IrDA 4 data writing function.
```c
err_t irda4_generic_write ( irda4_t *ctx, uint8_t *data_in, uint16_t len );
```

- `irda4_generic_read` IrDA 4 data reading function.
```c
err_t irda4_generic_read ( irda4_t *ctx, uint8_t *data_out, uint16_t len );
```

- `irda_hw_reset` IrDA 4 hardware reset function.
```c
void irda_hw_reset ( irda4_t *ctx );
```

## Example Description

> This example demonstrates the use of IrDA 4 click board by processing
 the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and disables the transmitter shutdown.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irda4_cfg_t irda4_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    irda4_cfg_setup( &irda4_cfg );
    IRDA4_MAP_MIKROBUS( irda4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda4_init( &irda4, &irda4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    irda4_set_tx_shutdown( &irda4, IRDA4_SHUTDOWN_DISABLED );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates the use of IrDA 4 clicks which can be used as transmitter or receiver. 
  - TRANSMITTER : Device is sending tx_message data. 
  - RECEIVER    : Device is reading a message that is being transmitted and 
                  logs it on the UART terminal. 

```c
void application_task ( void ) 
{
#if defined( DEMO_APP_TRANSMITTER )
    for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
    {
        irda4_generic_write( &irda4, &tx_message[ n_cnt ], 1 );
        Delay_ms ( 500 );
    }
    log_printf( &logger, "Message sent \r\n" );
#else
    if ( 1 == irda4_generic_read( &irda4, &rx_message, 1 ) )
    {
        log_printf( &logger, "%c", rx_message );
    }
#endif
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
