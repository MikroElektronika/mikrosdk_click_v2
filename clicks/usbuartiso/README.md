
---
# USB UART ISO Click

> [USB UART ISO Click](https://www.mikroe.com/?pid_product=MIKROE-5815) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5815&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of USB UART ISO Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUARTISO

### Example Key Functions

- `usbuartiso_cfg_setup` Config Object Initialization function.
```c
void usbuartiso_cfg_setup ( usbuartiso_cfg_t *cfg );
```

- `usbuartiso_init` Initialization function.
```c
err_t usbuartiso_init ( usbuartiso_t *ctx, usbuartiso_cfg_t *cfg );
```

- `usbuartiso_default_cfg` Click Default Configuration function.
```c
void usbuartiso_default_cfg ( usbuartiso_t *ctx );
```

- `usbuartiso_generic_write` USB UART ISO data writing function.
```c
err_t usbuartiso_generic_write ( usbuartiso_t *ctx, uint8_t *data_in, uint16_t len );
```

- `usbuartiso_generic_read` USB UART ISO data reading function.
```c
err_t usbuartiso_generic_read ( usbuartiso_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuartiso_cfg_t usbuartiso_cfg;  /**< Click config object. */

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
    usbuartiso_cfg_setup( &usbuartiso_cfg );
    USBUARTISO_MAP_MIKROBUS( usbuartiso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuartiso_init( &usbuartiso, &usbuartiso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbuartiso_default_cfg ( &usbuartiso );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends via UART Terminal
> will be sent over USB to the Click board and then it will be read and 
> echoed back by the MCU to the PC where the terminal program will display it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuartiso_generic_read ( &usbuartiso, &rx_data, 1 ) )
    {
        if ( usbuartiso_generic_write ( &usbuartiso, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
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
