
---
# Magic RFID click

> Magic RFID Click is a compact add-on board that contains an embedded RFID module. This board features the M6E-NANO, UHF RFID module with ultra-low power consumption from JADAK. Supporting the EPC Gen2V2 and ISO 18000-63 standard, the M6E-NANO module is available for global use. It operates in the Ultra High Frequency (UHF) band in a range from 859 up to 930MHz and can be used for write/read applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magic_rfid_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magic-rfid-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : UART type


# Software Support

We provide a library for the MagicRFID Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MagicRFID Click driver.

#### Standard key functions :

- `magicrfid_cfg_setup` Config Object Initialization function.
```c
void magicrfid_cfg_setup ( magicrfid_cfg_t *cfg );
```

- `magicrfid_init` Initialization function.
```c
err_t magicrfid_init ( magicrfid_t *ctx, magicrfid_cfg_t *cfg );
```

- `magicrfid_default_cfg` Click Default Configuration function.
```c
void magicrfid_default_cfg ( magicrfid_t *ctx );
```

#### Example key functions :

- `magicrfid_device_reset` Magic RFID device reset function.
```c
void magicrfid_device_reset ( magicrfid_t *ctx );
```

- `magicrfid_send_command` Magic RFID send command function.
```c
void magicrfid_send_command ( magicrfid_t *ctx, uint8_t *tx_buf, uint8_t len );
```

- `magicrfid_get_tag_rssi` Get Tag RSSI value.
```c
int8_t magicrfid_get_tag_rssi ( magicrfid_data_t *data_obj );
```

## Example Description

> This example reads and processes data from Magic RFID clicks.

**The demo application is composed of two sections :**

### Application Init

> Initialize driver init and starts default configuration module.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magicrfid_cfg_t magicrfid_cfg;  /**< Click config object. */

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
    magicrfid_cfg_setup( &magicrfid_cfg );
    MAGICRFID_MAP_MIKROBUS( magicrfid_cfg, MIKROBUS_1 );
    if ( UART_ERROR == magicrfid_init( &magicrfid, &magicrfid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, " >> Please, wait for device setup. \r\n" );
    magicrfid_default_cfg ( &magicrfid );
    Delay_ms( 1000 );
    log_printf( &logger, " >> Initialization done, reading tag is available. \r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads TAG information and RSSI value of the TAG and logs it on UART.

```c

void application_task ( void ) 
{
    magicrfid_process( &magicrfid, &tag );
    if ( magicrfid_get_data_status( &tag ) == 1 ) 
    {
        magicrfid_tag_parser( &tag );

        log_printf( &logger, " >> TAG INFO: 0x" );
        for( uint8_t cnt = 0; cnt < 12; cnt++ ) 
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag.tag_buf[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " >> TAG RSSI: %d\r\n", ( uint16_t ) tag.tag_rssi );
        magicrfid_reset_data( &tag );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagicRFID

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
