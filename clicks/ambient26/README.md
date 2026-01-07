
---
# Ambient 26 Click

> [Ambient 26 Click](https://www.mikroe.com/?pid_product=MIKROE-6856) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6856&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates how to read the ambient light level (ALS in lux) and UV index values using the Ambient 26 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient26

### Example Key Functions

- `ambient26_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ambient26_cfg_setup ( ambient26_cfg_t *cfg );
```

- `ambient26_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ambient26_init ( ambient26_t *ctx, ambient26_cfg_t *cfg );
```

- `ambient26_default_cfg` This function executes a default configuration of Ambient 26 Click board.
```c
err_t ambient26_default_cfg ( ambient26_t *ctx );
```

- `ambient26_get_als_lux` This function calculates the ALS illuminance in lux from the raw ALS data.
```c
err_t ambient26_get_als_lux ( ambient26_t *ctx, float *als_lux );
```

- `ambient26_get_uv_index` This function calculates the UV index value from the raw UVS data.
```c
err_t ambient26_get_uv_index ( ambient26_t *ctx, float *uvi );
```

### Application Init

> Initializes the logger and the Ambient 26 Click driver, then applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient26_cfg_t ambient26_cfg;  /**< Click config object. */

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
    ambient26_cfg_setup( &ambient26_cfg );
    AMBIENT26_MAP_MIKROBUS( ambient26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient26_init( &ambient26, &ambient26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT26_ERROR == ambient26_default_cfg ( &ambient26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads ALS and UV index values and logs them to the UART terminal.

```c
void application_task ( void )
{
    float als_lux = 0;
    float uv_index = 0;
    if ( AMBIENT26_OK == ambient26_get_als_lux ( &ambient26, &als_lux ) )
    {
        log_printf ( &logger, " ALS lux: %.1f\r\n", als_lux );
    }
    if ( AMBIENT26_OK == ambient26_get_uv_index ( &ambient26, &uv_index ) )
    {
        log_printf ( &logger, " UV index: %.3f\r\n\n", uv_index );
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
