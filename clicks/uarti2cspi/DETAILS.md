
---
# UART I2C/SPI click

UART I2C/SPI Click is an all-in-one solution which allows ESD-protected RS-232 connectivity to any embedded application while bridging the UART and I2C/SPI interfaces at the same time. It is equipped with the DE-9 connector, so it can be easily connected.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uarti2cspi_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/uart-i2cspi-click)

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

- Set RST pin state function.
> void uarti2cspi_set_reset ( uarti2cspi_t *ctx, uint8_t state );


#### Example key functions :

- Advanced initialization function.
> void uarti2cspi_advanced_init ( uarti2cspi_t *ctx, uint32_t baud_rate, uint8_t data_bits, uint8_t parity_mode, uint8_t stop_bits );
 
- Uart write text function.
> void uarti2cspi_uart_write_text ( uarti2cspi_t *ctx, uint8_t *w_text );

- This function reads one byte from the click module.
> uint8_t uarti2cspi_uart_read ( uarti2cspi_t *ctx );

## Examples Description

> This example showcases how to initialize, configure and use the UART I2C/SPI click module. 
> The click is a I2C/SPI to UART bridge interface. It requires a RS232/485 cable in order to be 
> connected to other click module or an adapter.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, configures UART, and enables UART interrupts. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uarti2cspi_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uarti2cspi_cfg_setup( &cfg );
    UARTI2CSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uarti2cspi_init( &uarti2cspi, &cfg );
    Delay_ms( 1000 );

    uarti2cspi_advanced_init( &uarti2cspi, 115200, UARTI2CSPI_UART_8_BIT_DATA, 
                                                   UARTI2CSPI_UART_NOPARITY,
                                                   UARTI2CSPI_UART_ONE_STOPBIT );
    Delay_ms( 100 );
    uarti2cspi_interrupt_enable( &uarti2cspi, UARTI2CSPI_RXD_INT_EN | UARTI2CSPI_THR_EMPTY_INT_EN );

    Delay_ms( 100 );

#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif
    Delay_ms( 1000 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    uarti2cspi_uart_write_text( &uarti2cspi, TEXT_TO_SEND );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms( 2000 );
#endif
#ifdef DEMO_APP_RECEIVER
    if ( uarti2cspi_uart_data_ready( &uarti2cspi ) )
    {
        uint8_t rx_data = uarti2cspi_uart_read( &uarti2cspi );
        log_printf( &logger, "%c", rx_data );
    }
#endif
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
