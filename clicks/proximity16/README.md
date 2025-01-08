
---
# Proximity 16 Click

> [Proximity 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5286) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5286&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 16 Click board by reading and displaying 8x8 zones measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity16

### Example Key Functions

- `proximity16_cfg_setup` Config Object Initialization function.
```c
void proximity16_cfg_setup ( proximity16_cfg_t *cfg );
```

- `proximity16_init` Initialization function.
```c
err_t proximity16_init ( proximity16_t *ctx, proximity16_cfg_t *cfg );
```

- `proximity16_default_cfg` Click Default Configuration function.
```c
err_t proximity16_default_cfg ( proximity16_t *ctx );
```

- `proximity16_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t proximity16_get_int_pin ( proximity16_t *ctx );
```

- `proximity16_get_resolution` This function gets the current resolution (4x4 or 8x8).
```c
err_t proximity16_get_resolution ( proximity16_t *ctx, uint8_t *resolution );
```

- `proximity16_get_ranging_data` This function gets the ranging data, using the selected output and the resolution.
```c
err_t proximity16_get_ranging_data ( proximity16_t *ctx, proximity16_results_data_t *results );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity16_cfg_t proximity16_cfg;  /**< Click config object. */

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
    proximity16_cfg_setup( &proximity16_cfg );
    PROXIMITY16_MAP_MIKROBUS( proximity16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity16_init( &proximity16, &proximity16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY16_ERROR == proximity16_default_cfg ( &proximity16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all zone measurements approximately every 500ms and logs them to the USB UART as an 8x8 map. The silicon temperature measurement in degrees Celsius is also displayed.

```c
void application_task ( void )
{
    if ( !proximity16_get_int_pin ( &proximity16 ) )
    {
        proximity16_results_data_t results;
        uint8_t resolution, map_side;
        err_t error_flag = proximity16_get_resolution ( &proximity16, &resolution );
        error_flag |= proximity16_get_ranging_data ( &proximity16, &results );
        if ( PROXIMITY16_OK == error_flag )
        {
            map_side = ( PROXIMITY16_RESOLUTION_4X4 == resolution ) ? 4 : 8;
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
