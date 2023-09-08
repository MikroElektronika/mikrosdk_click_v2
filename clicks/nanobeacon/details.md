
---
# NanoBeacon click

> NanoBeacon Click is a compact add-on board that provides a powerful and efficient Bluetooth beacon solution. This board features the IN100, an ultra-low power Bluetooth 5.3 Beacon SoC from InPlay, that sets a new standard in beacon technology. Its ultra-low power consumption, enhanced privacy mode, and three beacon modes offer seamless compatibility with no Bluetooth programming required - plug and play. Its compact design houses two types of built-in memory (4Kb OTP and 4KB SRAM), UART and I2C interfaces, and a hardware security engine.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanobeacon_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nanobeacon-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2023.
- **Type**          : UART type


# Software Support

We provide a library for the NanoBeacon Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NanoBeacon Click driver.

#### Standard key functions :

- `nanobeacon_cfg_setup` Config Object Initialization function.
```c
void nanobeacon_cfg_setup ( nanobeacon_cfg_t *cfg );
```

- `nanobeacon_init` Initialization function.
```c
err_t nanobeacon_init ( nanobeacon_t *ctx, nanobeacon_cfg_t *cfg );
```

#### Example key functions :

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

## Example Description

> This example demonstrates the use of NanoBeacon click board by setting the Eddystone URI advertisement to click boards webpage.

**The demo application is composed of two sections :**

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

> Every 10 seconds, it restarts and configures the device for advertisement with the Eddystone URI beacon format set to click boards webpage: https://www.mikroe.com/click

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
    Delay_ms ( 10000 );
}
```

## Note

> During advertising, the click board should appear as an Eddystone URI beacon on the BLE Scanner application.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoBeacon

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
