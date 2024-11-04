
---
# UART MUX 4 Click

> UART MUX 4 Click is a compact add-on board that switches the UART pins (RX and TX) 
from the mikroBUS™ socket to one of the two available outputs. 
This board features the 74HC4066D, a quad single-pole, single-throw analog switch from Nexperia. 
The UART MUX 4 Click allows you to switch from one multiplexed UART to another easily, 
but not both simultaneously.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uartmux4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/uart-mux-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : UART type


# Software Support

We provide a library for the UART MUX 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UART MUX 4 Click driver.

#### Standard key functions :

- `uartmux4_cfg_setup` Config Object Initialization function.
```c
void uartmux4_cfg_setup ( uartmux4_cfg_t *cfg );
```

- `uartmux4_init` Initialization function.
```c
err_t uartmux4_init ( uartmux4_t *ctx, uartmux4_cfg_t *cfg );
```

#### Example key functions :

- `uartmux4_enable_uart1` UART MUX 4 enable the UART 1 function.
```c
void uartmux4_enable_uart1 ( uartmux4_t *ctx );
```

- `uartmux4_enable_uart2` UART MUX 4 enable the UART 2 function.
```c
void uartmux4_enable_uart2 ( uartmux4_t *ctx );
```

## Example Description

> This example demonstrates the use of UART MUX 4 Click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the UART driver and additional pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uartmux4_cfg_t uartmux4_cfg;  /**< Click config object. */

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
    uartmux4_cfg_setup( &uartmux4_cfg );
    UARTMUX4_MAP_MIKROBUS( uartmux4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uartmux4_init( &uartmux4, &uartmux4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Writes demo message, echos it back, processes all incoming data 
> and displays them on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, " ---------------- \r\n" );
    log_printf( &logger, " UART 1 demo message:\r\n" );
    uartmux4_enable_uart1( &uartmux4 );
    Delay_ms ( 100 );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( uartmux4_generic_write ( &uartmux4, DEMO_MESSAGE, sizeof( DEMO_MESSAGE ) ) )
        {
            if ( uartmux4_generic_read( &uartmux4, app_buf, sizeof( DEMO_MESSAGE ) ) )
            {
                log_printf( &logger, "%s", app_buf );
            }
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " ---------------- \r\n" );
    log_printf( &logger, " UART 2 demo message:\r\n" );
    uartmux4_enable_uart1( &uartmux4 );
    Delay_ms ( 100 );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( uartmux4_generic_write ( &uartmux4, DEMO_MESSAGE, sizeof( DEMO_MESSAGE ) ) )
        {
            if ( uartmux4_generic_read( &uartmux4, app_buf, sizeof( DEMO_MESSAGE ) ) )
            {
                log_printf( &logger, "%s", app_buf );
            }
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTMUX4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
