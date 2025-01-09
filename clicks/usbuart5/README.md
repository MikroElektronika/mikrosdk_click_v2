
---
# USB UART 5 Click

> [USB UART 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5574) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5574&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from USB UART 5 Click board&trade;.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUART5

### Example Key Functions

- `usbuart5_cfg_setup` Config Object Initialization function.
```c
void usbuart5_cfg_setup ( usbuart5_cfg_t *cfg );
```

- `usbuart5_init` Initialization function.
```c
err_t usbuart5_init ( usbuart5_t *ctx, usbuart5_cfg_t *cfg );
```

- `usbuart5_default_cfg` Click Default Configuration function.
```c
void usbuart5_default_cfg ( usbuart5_t *ctx );
```

- `usbuart5_generic_write`  USB UART 5 data writing function.
```c
err_t usbuart5_generic_write ( usbuart5_t *ctx, char *data_in, uint16_t len )
```

- `usbuart5_generic_read` USB UART 5 data reading function.
```c
err_t usbuart5_generic_read ( usbuart5_t *ctx, char *data_out, uint16_t len );
```

- `usbuart5_reset_device` USB UART 5 reset the device function.
```c
void usbuart5_reset_device ( usbuart5_t *ctx );
```

### Application Init

> Initializes driver, wake-up module, and performs the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart5_cfg_t usbuart5_cfg;  /**< Click config object. */

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
    usbuart5_cfg_setup( &usbuart5_cfg );
    USBUART5_MAP_MIKROBUS( usbuart5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuart5_init( &usbuart5, &usbuart5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    usbuart5_default_cfg ( &usbuart5 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends via HidUartExample 
> will be sent over USB to the Click board and then it will be read and 
> echoed back by the MCU to the PC where the terminal program will display it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuart5_generic_read ( &usbuart5, &rx_data, 1 ) )
    {
        if ( usbuart5_generic_write ( &usbuart5, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
    }
}
```

### Note

> Make sure to download and install 
> CP2110/4 Software package for Windows/Mac/Linux on the host PC.

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
