
---
# UART MUX 4 Click

> [UART MUX 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5720) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5720&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of UART MUX 4 Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTMUX4

### Example Key Functions

- `uartmux4_cfg_setup` Config Object Initialization function.
```c
void uartmux4_cfg_setup ( uartmux4_cfg_t *cfg );
```

- `uartmux4_init` Initialization function.
```c
err_t uartmux4_init ( uartmux4_t *ctx, uartmux4_cfg_t *cfg );
```

- `uartmux4_enable_uart1` UART MUX 4 enable the UART 1 function.
```c
void uartmux4_enable_uart1 ( uartmux4_t *ctx );
```

- `uartmux4_enable_uart2` UART MUX 4 enable the UART 2 function.
```c
void uartmux4_enable_uart2 ( uartmux4_t *ctx );
```

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
