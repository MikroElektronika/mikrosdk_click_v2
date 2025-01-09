
---
# Radar Click

> [Radar Click](https://www.mikroe.com/?pid_product=MIKROE-5183) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5183&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Radar Click board by reading and parsing events as well as the module internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Radar

### Example Key Functions

- `radar_cfg_setup` Config Object Initialization function.
```c
void radar_cfg_setup ( radar_cfg_t *cfg );
```

- `radar_init` Initialization function.
```c
err_t radar_init ( radar_t *ctx, radar_cfg_t *cfg );
```

- `radar_default_cfg` Click Default Configuration function.
```c
err_t radar_default_cfg ( radar_t *ctx );
```

- `radar_get_event` This function waits for an IN/OUT event or ACK command response.
```c
err_t radar_get_event ( radar_t *ctx, uint8_t *evt_id, uint8_t *payload, uint8_t *payload_size );
```

- `radar_get_temperature` This function reads the chip internal temperature.
```c
err_t radar_get_temperature ( radar_t *ctx, float *temperature );
```

- `radar_set_detection_range` This function sets the min and max presence detection values.
```c
err_t radar_set_detection_range ( radar_t *ctx, float min, float max );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    radar_cfg_t radar_cfg;  /**< Click config object. */

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
    radar_cfg_setup( &radar_cfg );
    RADAR_MAP_MIKROBUS( radar_cfg, MIKROBUS_1 );
    if ( UART_ERROR == radar_init( &radar, &radar_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RADAR_ERROR == radar_default_cfg ( &radar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the detection event and then displays on the USB UART the distance of detected object, accuracy, elapsed time since last reset, and the module internal temperature.

```c
void application_task ( void )
{
    uint8_t evt_id, evt_payload_size, evt_payload[ 16 ];
    if ( RADAR_OK == radar_get_event ( &radar, &evt_id, evt_payload, &evt_payload_size ) )
    {
        if ( RADAR_CMD_ID_DETECT_IN_EVT == evt_id )
        {
            log_printf( &logger, " EVENT: IN\r\n" );
            radar_float_bytes_t distance;
            memcpy ( distance.b_data, &evt_payload[ 8 ], 4 );
            radar_float_ieee_to_mchip ( &distance.f_data );
            log_printf( &logger, " Target distance: %.3f m\r\n", distance.f_data );
            memcpy ( distance.b_data, &evt_payload[ 12 ], 4 );
            radar_float_ieee_to_mchip ( &distance.f_data );
            log_printf( &logger, " Accuracy (+/-): %.3f m\r\n", distance.f_data );
        }
        else
        {
            log_printf( &logger, " EVENT: OUT\r\n" );
        }
        uint32_t evt_time = ( ( uint32_t ) evt_payload[ 3 ] << 24 ) | ( ( uint32_t ) evt_payload[ 2 ] << 16 ) | 
                            ( ( uint16_t ) evt_payload[ 1 ] << 8 ) | evt_payload[ 0 ];
        log_printf( &logger, " Elapsed time: %.2f s\r\n", evt_time / 1000.0 );
        float temperature;
        if ( RADAR_OK == radar_get_temperature ( &radar, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
