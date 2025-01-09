
---
# NanoBeacon Click

> [NanoBeacon Click](https://www.mikroe.com/?pid_product=MIKROE-5794) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5794&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of NanoBeacon Click board by setting the Eddystone URI advertisement to Click boards webpage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoBeacon

### Example Key Functions

- `nanobeacon_cfg_setup` Config Object Initialization function.
```c
void nanobeacon_cfg_setup ( nanobeacon_cfg_t *cfg );
```

- `nanobeacon_init` Initialization function.
```c
err_t nanobeacon_init ( nanobeacon_t *ctx, nanobeacon_cfg_t *cfg );
```

- `nanobeacon_set_advertising` This function sets the device MAC address, interval and advertising raw data.
```c
err_t nanobeacon_set_advertising ( uint8_t *mac_address, uint16_t interval, uint8_t *adv_raw_data, uint8_t len );
```

- `nanobeacon_load_adv_to_ram` This function loads advertising data to RAM.
```c
err_t nanobeacon_load_adv_to_ram ( nanobeacon_t *ctx );
```

- `nanobeacon_start_advertising` This function starts the advertising.
```c
err_t nanobeacon_start_advertising ( nanobeacon_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanobeacon_cfg_t nanobeacon_cfg;  /**< Click config object. */

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
    nanobeacon_cfg_setup( &nanobeacon_cfg );
    NANOBEACON_MAP_MIKROBUS( nanobeacon_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nanobeacon_init( &nanobeacon, &nanobeacon_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Every 10 seconds, it restarts and configures the device for advertisement with the Eddystone URI beacon format set to Click boards webpage: https://www.mikroe.com/click

```c
void application_task ( void )
{
    // The device MAC address for advertisement
    static uint8_t mac_address[ 6 ] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };

    // Eddystone advertisement raw data
    static uint8_t eddystone_adv_raw[ ] = 
    { 
        0x03, // Length of Service List
        0x03, // Param: Service List
        0xAA, 0xFE, // Eddystone ID
        0x12, // Length of Service Data
        0x16, // Service Data
        0xAA, 0xFE, // Eddystone ID
        0x10, // Frame type: URL
        0x00, // Power
        0x01, // https://www.
        'm','i','k','r','o','e', 
        0x00, // .com/
        'c','l','i','c','k' 
    };
    log_printf( &logger, "\r\n Restart device\r\n" );
    nanobeacon_restart_device ( &nanobeacon );
    
    while ( NANOBEACON_OK != nanobeacon_check_communication ( &nanobeacon ) )
    {
        log_error( &logger, " Check communication." );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Configure device for advertisement\r\n" );
    if ( NANOBEACON_OK != nanobeacon_set_advertising ( mac_address, 1000, eddystone_adv_raw, 
                                                       sizeof( eddystone_adv_raw ) ) )
    {
        log_error( &logger, " Set advertising." );
    }

    if ( NANOBEACON_OK != nanobeacon_load_adv_to_ram( &nanobeacon ) )
    {
        log_error( &logger, " Load data to RAM." );
    }
    
    log_printf( &logger, " Start advertising\r\n" );
    if ( NANOBEACON_OK != nanobeacon_start_advertising ( &nanobeacon ) )
    {
        log_error( &logger, " Start advertising." );
    }    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> During advertising, the Click board should appear as an Eddystone URI beacon on the BLE Scanner application.

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
