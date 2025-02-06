
---
# Color 19 Click

> [Color 19 Click](https://www.mikroe.com/?pid_product=MIKROE-6415) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6415&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 19 Click by reading and displaying the color measurement from RGBW channels and the light intensity level in lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color19

### Example Key Functions

- `color19_cfg_setup` Config Object Initialization function.
```c
void color19_cfg_setup ( color19_cfg_t *cfg );
```

- `color19_init` Initialization function.
```c
err_t color19_init ( color19_t *ctx, color19_cfg_t *cfg );
```

- `color19_default_cfg` Click Default Configuration function.
```c
err_t color19_default_cfg ( color19_t *ctx );
```

- `color19_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t color19_get_int_pin ( color19_t *ctx );
```

- `color19_read_data` This function reads the color data measurement of all channels and calculates the light intensity in lux.
```c
err_t color19_read_data ( color19_t *ctx, color19_data_t *data_out );
```

- `color19_check_communication` This function checks the communication by reading and verifying the device ID.
```c
err_t color19_check_communication ( color19_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color19_cfg_t color19_cfg;  /**< Click config object. */

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
    color19_cfg_setup( &color19_cfg );
    COLOR19_MAP_MIKROBUS( color19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color19_init( &color19, &color19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR19_ERROR == color19_default_cfg ( &color19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt then reads the color measurement from 
RGBW channels and the light intensity level in lux and displays the results
on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    color19_data_t color_data;

    // Wait for a data ready interrupt
    while ( color19_get_int_pin ( &color19 ) );

    if ( COLOR19_OK == color19_read_data ( &color19, &color_data ) )
    {
        log_printf ( &logger, "RED: %lu\r\n", color_data.red );
        log_printf ( &logger, "GREEN: %lu\r\n", color_data.green );
        log_printf ( &logger, "BLUE: %lu\r\n", color_data.blue );
        log_printf ( &logger, "WHITE: %lu\r\n", color_data.white );
        log_printf ( &logger, "LUX: %lu\r\n\n", color_data.lux );
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
