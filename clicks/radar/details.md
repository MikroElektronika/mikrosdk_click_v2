
---
# Radar click

> Radar Click is a compact add-on board that alerts you to the presence of an intruder via interpreting the infrared radiation that emanates from their body. This board features the MM5D91-00, a presence detection sensor module that integrates 60GHz mmWave technology that counts the number of people entering or exiting an entrance from Jorjin Technologies Inc. It includes the ARM Cortex-M4F based processor system, 1Tx, 3Rx antenna, and integrated regulator, alongside azimuth and elevation field of view of ±45° and ±40°. Its detection goes up to 10m for macro and 5m for micro motion with environmental-factors immunity such as temperature, wind, sunlight, and dust. This Click board™ is suitable for various presence sensing applications, from office and home to commercial buildings and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/radar_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/radar-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : UART type


# Software Support

We provide a library for the Radar Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Radar Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of Radar click board by reading and parsing events as well as the module internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the click default configuration.

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Radar

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
