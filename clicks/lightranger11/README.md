
---
# LightRanger 11 Click

> [LightRanger 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5864) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5864&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LightRanger 11 Click board by reading and displaying
> 8x8 zones measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger11

### Example Key Functions

- `lightranger11_cfg_setup` Config Object Initialization function.
```c
void lightranger11_cfg_setup ( lightranger11_cfg_t *cfg );
```

- `lightranger11_init` Initialization function.
```c
err_t lightranger11_init ( lightranger11_t *ctx, lightranger11_cfg_t *cfg );
```

- `lightranger11_default_cfg` Click Default Configuration function.
```c
err_t lightranger11_default_cfg ( lightranger11_t *ctx );
```

- `lightranger11_get_ranging_data` LightRanger 11 get ranging data function.
```c
err_t lightranger11_get_ranging_data ( lightranger11_t *ctx, lightranger11_results_data_t *results );
```

- `lightranger11_get_resolution` LightRanger 11 get resolution function.
```c
err_t lightranger11_get_resolution ( lightranger11_t *ctx, uint8_t *resolution );
```

- `lightranger11_get_int_pin` LightRanger 11 get int pin function.
```c
uint8_t lightranger11_get_int_pin ( lightranger11_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger11_cfg_t lightranger11_cfg;  /**< Click config object. */

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
    lightranger11_cfg_setup( &lightranger11_cfg );
    LIGHTRANGER11_MAP_MIKROBUS( lightranger11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger11_init( &lightranger11, &lightranger11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER11_ERROR == lightranger11_default_cfg ( &lightranger11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all zone measurements approximately every 500ms and logs them to the USB UART as an 8x8 map. 
> The silicon temperature measurement in degrees Celsius is also displayed.

```c
void application_task ( void ) 
{
    if ( !lightranger11_get_int_pin ( &lightranger11 ) )
    {
        lightranger11_results_data_t results;
        uint8_t resolution, map_side;
        err_t error_flag = lightranger11_get_resolution ( &lightranger11, &resolution );
        error_flag |= lightranger11_get_ranging_data ( &lightranger11, &results );
        if ( LIGHTRANGER11_OK == error_flag )
        {
            map_side = ( LIGHTRANGER11_RESOLUTION_4X4 == resolution ) ? 4 : 8;
            log_printf ( &logger, "\r\n %ux%u MAP (mm):\r\n", ( uint16_t ) map_side, ( uint16_t ) map_side );
            for ( uint16_t cnt = 1; cnt <= resolution; cnt++ )
            {
                log_printf ( &logger, " %u\t", results.distance_mm[ cnt - 1 ] );
                if ( 0 == ( cnt % map_side ) )
                {
                    log_printf ( &logger, "\r\n" );
                }
            }
            log_printf ( &logger, " Silicon temperature : %d degC\r\n", ( int16_t ) results.silicon_temp_degc );
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
