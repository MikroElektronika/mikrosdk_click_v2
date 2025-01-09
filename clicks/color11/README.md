
---
# Color 11 Click

> [Color 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5894) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5894&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Color 11 Click driver.
> The demo application sets sensor configuration 
> and reads and displays ALS data measurement results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color11

### Example Key Functions

- `color11_cfg_setup` Config Object Initialization function.
```c
void color11_cfg_setup ( color11_cfg_t *cfg );
```

- `color11_init` Initialization function.
```c
err_t color11_init ( color11_t *ctx, color11_cfg_t *cfg );
```

- `color11_default_cfg` Click Default Configuration function.
```c
err_t color11_default_cfg ( color11_t *ctx );
```

- `color11_get_als_data` Color 11 get ALS data function.
```c
err_t color11_get_als_data ( color11_t *ctx, color11_als_data_t *als_data );
```

- `color11_get_illuminance` Color 11 get illuminance function.
```c
err_t color11_get_illuminance ( color11_t *ctx, float *lux );
```

- `color11_get_data_valid_status` Color 11 get data valid status function.
```c
err_t color11_get_data_valid_status ( color11_t *ctx, uint8_t *status );
```

### Application Init

> Initialization of I2C module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color11_cfg_t color11_cfg;  /**< Click config object. */

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
    color11_cfg_setup( &color11_cfg );
    COLOR11_MAP_MIKROBUS( color11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color11_init( &color11, &color11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR11_ERROR == color11_default_cfg ( &color11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 11 Click board&trade;.
> Reads and displays the results of the ALS data measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{   
    uint8_t status = 0;
    if ( COLOR11_OK == color11_get_data_valid_status( &color11, &status ) )
    {
        color11_als_data_t color_data;
        if ( COLOR11_OK == color11_get_als_data( &color11, &color_data ) && ( COLOR11_STATUS2_AVALID & status ) )
        {
            log_printf( &logger, " Clear: %u\r\n", color_data.clear );
            log_printf( &logger, " Red : %u\r\n", color_data.red );
            log_printf( &logger, " Green : %u\r\n", color_data.green );
            log_printf( &logger, " Blue : %u\r\n", color_data.blue );
            log_printf( &logger, " Wideband : %u\r\n", color_data.wideband );
            log_printf( &logger, " Flicker : %u\r\n", color_data.flicker );
            log_printf( &logger, " ------------------\r\n" );
            Delay_ms ( 1000 );
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
