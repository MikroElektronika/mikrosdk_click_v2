 
---
# UART I2C/SPI click

UART I2C/SPI Click is an all-in-one solution which allows ESD-protected RS-232 connectivity to any embedded application while bridging the UART and I2C/SPI interfaces at the same time. It is equipped with the DE-9 connector, so it can be easily connected.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uarti2cspi_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/uart-i2cspi-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the UARTI2CSPI Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UARTI2CSPI Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uarti2cspi_cfg_setup ( uarti2cspi_cfg_t *cfg ); 
 
- Initialization function.
> UARTI2CSPI_RETVAL uarti2cspi_init ( uarti2cspi_t *ctx, uarti2cspi_cfg_t *cfg );

- Click Default Configuration function.
> void uarti2cspi_default_cfg ( uarti2cspi_t *ctx );


#### Example key functions :

- This function formats and sends the specified string using UART.
> void uarti2cspi_serial_write ( uarti2cspi_t *ctx, uint8_t *str_data, uint8_t print_mode );
 
- This function sends the specified byte using UART.
> void uarti2cspi_advanced_uart_write ( uarti2cspi_t *ctx, uint8_t w_byte );

- This function reads one byte from the click module.
> uint8_t uarti2cspi_uart_read ( uarti2cspi_t *ctx );

## Examples Description

> This example showcases how to initialize, configure and use the UART I2C/SPI click module. The
  click is a I2C/SPI to UART bridge interface. It requires a RS232/485 cable in order to be conn-
  ected to a different click module or an adapter.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. There's also a communic-
  ation initialization function which puts the click module in "echo-mode". 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uarti2cspi_cfg_t cfg;
    uarti2cspi_package_t package;
    uint8_t vector;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 19200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uarti2cspi_cfg_setup( &cfg );
    UARTI2CSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uarti2cspi_init( &uarti2cspi, &cfg );

    package.baud_rate = 19200;
    package.data_bits = UARTI2CSPI_UART_8_BIT_DATA;
    package.parity_mode = UARTI2CSPI_UART_NOPARITY;
    package.stop_bits = UARTI2CSPI_UART_ONE_STOPBIT;

    vector = UARTI2CSPI_RXD_INT_EN | UARTI2CSPI_THR_EMPTY_INT_EN;

    uarti2cspi_advanced_init( &uarti2cspi, package );
    uarti2cspi_interrupt_enable( &uarti2cspi, vector );

    Delay_100ms( );
    uarti2cspi_serial_write( &uarti2cspi, &str0[ 0 ], LINE_PRINT );
    log_printf( &logger, " * Initialization complete *\r\n" );
    Delay_1sec( );

    comm_init( );
    Delay_1sec( );
}
  
```

### Application Task

> This function uses the "echo-mode" to write back every message the click receives over UART.

```c

void application_task ( void )
{
    uarti2cspi_uart_write( &uarti2cspi, uarti2cspi_uart_read( &uarti2cspi ) );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTI2CSPI

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
