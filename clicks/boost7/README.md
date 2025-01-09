
---
# Boost 7 Click

> [Boost 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5575) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5575&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Boost 7 Click board by controlling the V- and V+ outputs state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost7

### Example Key Functions

- `boost7_cfg_setup` Config Object Initialization function.
```c
void boost7_cfg_setup ( boost7_cfg_t *cfg );
```

- `boost7_init` Initialization function.
```c
err_t boost7_init ( boost7_t *ctx, boost7_cfg_t *cfg );
```

- `boost7_enable_out1` This function enables the OUT1 (V-) by setting the STB1 pin to high logic state.
```c
void boost7_enable_out1 ( boost7_t *ctx );
```

- `boost7_disable_out1` This function disables the OUT1 (V-) by setting the STB1 pin to low logic state.
```c
void boost7_disable_out1 ( boost7_t *ctx );
```

- `boost7_enable_out2` This function enables the OUT2 (V+) by setting the STB2 pin to high logic state.
```c
void boost7_enable_out2 ( boost7_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost7_cfg_t boost7_cfg;  /**< Click config object. */

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
    boost7_cfg_setup( &boost7_cfg );
    BOOST7_MAP_MIKROBUS( boost7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost7_init( &boost7, &boost7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles the V- and V+ outputs state every 5 seconds and displays their state on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " OUT1 (V-) : ENABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : DISABLED\r\n\n" );
    boost7_enable_out1 ( &boost7 );
    boost7_disable_out2 ( &boost7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUT1 (V-) : DISABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : ENABLED\r\n\n" );
    boost7_disable_out1 ( &boost7 );
    boost7_enable_out2 ( &boost7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
