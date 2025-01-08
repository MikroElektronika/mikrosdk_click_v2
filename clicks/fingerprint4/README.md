
---
# Fingerprint 4 Click

> [Fingerprint 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5465) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5465&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Fingerprint 4 Click boards by registering 3 fingerprints and
then waiting until a finger is detected on the sensor and identifying if the fingerprint matches one of
those stored in the Flash storage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint4

### Example Key Functions

- `fingerprint4_cfg_setup` Config Object Initialization function.
```c
void fingerprint4_cfg_setup ( fingerprint4_cfg_t *cfg );
```

- `fingerprint4_init` Initialization function.
```c
err_t fingerprint4_init ( fingerprint4_t *ctx, fingerprint4_cfg_t *cfg );
```

- `fingerprint4_version` This function reads out version information from the device. The response contains a variable length string that contains version information of the device.
```c
err_t fingerprint4_version ( fingerprint4_t *ctx, char *version, uint8_t len );
```

- `fingerprint4_identify_finger` This function captures and identifies finger against existing templates in Flash storage. 
```c
err_t fingerprint4_identify_finger ( fingerprint4_t *ctx, uint32_t timeout, uint16_t *template_id, bool *match );
```

- `fingerprint4_wait_finger_not_present` This function waits until no finger is detected on the sensor.
```c
err_t fingerprint4_wait_finger_not_present ( fingerprint4_t *ctx, uint32_t timeout );
```

### Application Init

> Initializes the driver and reads the sensor firmware version, then resets the sensor and removes all
stored fingerprint templates. After that it registers 3 new fingerprint templates and stores them in the Flash storage.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fingerprint4_cfg_t fingerprint4_cfg;  /**< Click config object. */

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
    fingerprint4_cfg_setup( &fingerprint4_cfg );
    FINGERPRINT4_MAP_MIKROBUS( fingerprint4_cfg, MIKROBUS_1 );
    if ( FINGERPRINT4_RES_OK != fingerprint4_init( &fingerprint4, &fingerprint4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    fingerprint4_reset_device ( &fingerprint4 );
    
    fingerprint4.phy_rx_timeout = FINGERPRINT4_DEFAULT_PHY_RX_TIMEOUT_MS;
    
    uint8_t version[ 50 ] = { 0 };
    if ( FINGERPRINT4_RES_OK == fingerprint4_version ( &fingerprint4, version, 50 ) )
    {
        log_printf( &logger, " FW version: %s\r\n", version );
        log_printf( &logger, "---------------------------------\r\n\n" );
    }
    
    fingerprint4_error_check( "Sensor reset", fingerprint4_sensor_reset ( &fingerprint4 ) );
    
    fingerprint4_error_check( "Remove all templates", fingerprint4_template_remove_all ( &fingerprint4 ) );
    
    fingerprint4_register_fingerprints ( &fingerprint4, LOCATION_IN_FLASH, NUMBER_OF_FINGERPRINTS );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits until a finger is detected on the sensor, takes an image of the finger and checks if there's
a fingerprint in the library that matches the one it has just read. If it finds a match, a fingerprint template
ID will be displayed. All data is being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    uint16_t template_id;
    bool match;
    log_printf( &logger, " Put your finger on the sensor.\r\n" );
    err_t error_flag = fingerprint4_identify_finger ( &fingerprint4, FINGERPRINT4_INFINITE_TIMEOUT, &template_id, &match );
    if ( error_flag )
    {
        fingerprint4_error_check( "Identify finger", error_flag );
    }
    else
    {
        if ( match )
        {
            log_printf( &logger, " >>>>> Fingerprint MATCH - Template ID: %u <<<<<\r\n", template_id );
        }
        else
        {
            log_printf( &logger, " >>>>> NO MATCH in the library <<<<<\r\n" );
        }
    }
    log_printf( &logger, " Lift the finger of the sensor.\r\n" );
    fingerprint4_wait_finger_not_present ( &fingerprint4, FINGERPRINT4_INFINITE_TIMEOUT );
    log_printf( &logger, "---------------------------------\r\n\n" );
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
