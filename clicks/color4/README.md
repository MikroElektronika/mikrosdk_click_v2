
---
# Color 4 Click

> [Color 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2220) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2220&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Color 4 Click driver.
> This driver provides the functions for the sensor configuration
> and for reading RGBW and ambient light data from the device.
> This example displays RGBW data, Ambient light level, CCT data 
> and the light color names.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color4

### Example Key Functions

- `color4_cfg_setup` Config Object Initialization function.
```c
void color4_cfg_setup ( color4_cfg_t *cfg );
```

- `color4_init` Initialization function.
```c
err_t color4_init ( color4_t *ctx, color4_cfg_t *cfg );
```

- `color4_default_cfg` Click Default Configuration function.
```c
err_t color4_default_cfg ( color4_t *ctx );
```

- `color4_set_config` Color 4 set configuration function.
```c
err_t color4_set_config ( color4_t *ctx, color4_config_t config ) 
```

- `color4_get_color_data` Color 4 get color data function.
```c
err_t color4_get_color_data ( color4_t *ctx, color4_ch_color_t ch_color, uint16_t *color_data );
```

- `color4_get_ambient_light` Color 4 get ambient light level function.
```c
err_t color4_get_ambient_light ( color4_t *ctx, float *ambient_light );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color4_cfg_t color4_cfg;  /**< Click config object. */

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
    color4_cfg_setup( &color4_cfg );
    COLOR4_MAP_MIKROBUS( color4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color4_init( &color4, &color4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR4_ERROR == color4_default_cfg ( &color4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 4 Click board&trade;.
> Reads and displays the results of the RGBW, Ambient light level, 
> calculate the correlated color temperature. 
> This example also detects and displays the light color names.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_RED, &red_data ) )
    {
        log_printf( &logger, " Red: %u\r\n", red_data );    
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_GREEN, &green_data ) )
    {
        log_printf( &logger, " Green: %u\r\n", green_data );   
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_BLUE, &blue_data ) )
    {
        log_printf( &logger, " Blue: %u\r\n", blue_data );
    }
    
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_WHITE, &white_data ) )
    {
        log_printf( &logger, " White: %u\r\n", white_data );    
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );
    
    if ( COLOR4_OK == color4_get_ambient_light( &color4, &ambient_light ) )
    {
        log_printf( &logger, " ALS lux level: %.2f\r\n", ambient_light );    
    }
    
    if ( COLOR4_OK == color4_get_cct( &color4, &cct ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );   
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );

    display_color( );
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> Color detection is obtained based on the analysis 
> of calculate the correlated color temperature (CCT) data 
> and the CIE 1931 chromaticity diagram.
> For more details please refer to the Designing the VEML6040 into an Application
> application note (https://www.vishay.com/docs/84331/designingveml6040.pdf).

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
