
---
# Color 17 Click

> [CLICK_NAME Click](https://www.mikroe.com/?pid_product=MIKROE-XXXX) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-XXXX&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Color 17 Click driver.
> This example displays CCT data, Light intensity level
> and the light color names.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color17

### Example Key Functions

- `color17_cfg_setup` Config Object Initialization function.
```c
void color17_cfg_setup ( color17_cfg_t *cfg );
```

- `color17_init` Initialization function.
```c
err_t color17_init ( color17_t *ctx, color17_cfg_t *cfg );
```

- `color17_default_cfg` Click Default Configuration function.
```c
err_t color17_default_cfg ( color17_t *ctx );
```

- `color17_get_cct` Color 17 gets correlated color temperature data function.
```c
err_t color17_get_cct ( color17_t *ctx, float *cct, float *light_intensity );
```

- `color17_get_measurement` Color 17 gets light and color measurement data function.
```c
err_t color17_get_measurement ( color17_t *ctx, uint32_t *adc_codes );
```

- `color17_set_config` Color 17 set the configuration function.
```c
err_t color17_set_config ( color17_t *ctx, color17_config_t config );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color17_cfg_t color17_cfg;  /**< Click config object. */

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
    color17_cfg_setup( &color17_cfg );
    COLOR17_MAP_MIKROBUS( color17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color17_init( &color17, &color17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR17_ERROR == color17_default_cfg ( &color17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 17 Click board&trade;.
> Reads and displays the correlated color temperature 
> and Light intensity level.
> This example also detects and displays the light color names.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR17_OK == color17_get_cct( &color17, &cct, &light_intensity ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );
        log_printf( &logger, " LIL: %.2f\r\n", light_intensity );
        log_printf( &logger, " - - - - - - -  - - - - \r\n" );
        color17_display_color( );
    }
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> Color detection is obtained based on the analysis 
> of calculate the correlated color temperature (CCT) data
> and the CIE 1931 chromaticity diagram. For more details please refer to the 
> OPT4048 High Speed High Precision Tristimulus XYZ Color Sensor datasheet 
> [OPT4048 datasheet](https://www.ti.com/lit/gpn/OPT4048).

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
