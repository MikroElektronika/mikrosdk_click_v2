
---
# IrDA 2 click

> IrDA2 click features the TFDU4101 infrared transceiver module as well as MCP2120 infrared encoder/decoder from Microchip connected with the 7.3728 MHz external crystal. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target board via UART interface and the following mikroBUS™ pins: AN, RST, CS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irda2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/irda2-click)

---


#### Click library

- **Author**        : MikroE Team
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the IrDA2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IrDA2 Click driver.

#### Standard key functions :

- `irda2_cfg_setup` Config Object Initialization function.
```c
void irda2_cfg_setup ( irda2_cfg_t *cfg );
```

- `irda2_init` Initialization function.
```c
err_t irda2_init ( irda2_t *ctx, irda2_cfg_t *cfg );
```

- `irda2_default_cfg` Click Default Configuration function.
```c
void irda2_default_cfg ( irda2_t *ctx );
```

#### Example key functions :

- `irda2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t irda2_generic_write ( irda2_t *ctx, uint8_t *data_in, uint16_t len )
```

- `irda2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t irda2_generic_read ( irda2_t *ctx, uint8_t *data_out, uint16_t len );
```

- `irda2_reset` This function executes a device reset operation.
```c
void irda2_reset( irda2_t *ctx );
```

## Example Description

> This example demonstrates the use of an IrDA 2 click board by showing the communication between the two click boards.

**The demo application is composed of two sections :**

### Application Init

> Initalizes device and makes an initial log.

```c

void application_init( void ) 
{
    irda2_cfg_t irda2_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_info( &logger, " Application Init " );
    
    //  Click initialization.
    irda2_cfg_setup( &irda2_cfg );
    IRDA2_MAP_MIKROBUS( irda2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda2_init( &irda2, &irda2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    irda2_default_cfg( &irda2 );
    irda2_reset( &irda2 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message once per second.

```c

void application_task( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    irda2_generic_write( &irda2, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == irda2_generic_read( &irda2, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
