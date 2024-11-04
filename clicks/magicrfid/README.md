\mainpage Main Page

---
# Magic RFID Click

> Magic RFID Click is a compact add-on board that contains an embedded RFID module. This board features the M6E-NANO, UHF RFID module with ultra-low power consumption from JADAK. Supporting the EPC Gen2V2 and ISO 18000-63 standard, the M6E-NANO module is available for global use. It operates in the Ultra High Frequency (UHF) band in a range from 859 up to 930MHz and can be used for write/read applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magic_rfid_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/magic-rfid-click)

---


#### Click library

- **Author**        : MikroE Team
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

- `magicrfid_get_response` Magic RFID get response function.
```c
err_t magicrfid_get_response ( magicrfid_t *ctx, magicrfid_response_t *rsp );
```

- `magicrfid_parse_tag_rssi` This function parses RSSI value of the tag.
```c
int8_t magicrfid_parse_tag_rssi ( magicrfid_response_t rsp );
```

- `magicrfid_parse_tag_epc` This function parses EPC bytes of the tag.
```c
void magicrfid_parse_tag_epc ( magicrfid_response_t rsp, magicrfid_epc_t *epc );
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
    magicrfid_default_cfg ( &magicrfid );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Scans for RFID TAGs and displays on the USB UART the EPC bytes of the detected tag.
It also parses and displays the RSSI as well as the frequency this tag was detected at.

```c

void application_task ( void ) 
{
    magicrfid_response_t rsp = { 0 };
    if ( ( MAGICRFID_OK == magicrfid_get_response ( &magicrfid, &rsp ) ) && 
         ( MAGICRFID_OPCODE_READ_TAG_ID_MULTIPLE == rsp.opcode ) )
    {
        if ( 0 == rsp.data_len )
        {
            log_printf( &logger, "\r\n --- SCANNING ---\r\n" );
        }
        else
        {
            log_printf( &logger, "\r\n --- TAG DETECTED ---\r\n" );
            int8_t tag_rssi = 0;
            uint32_t tag_freq = 0;
            magicrfid_epc_t epc = { 0 };
            tag_rssi = magicrfid_parse_tag_rssi ( rsp );
            log_printf( &logger, " RSSI: %d\r\n", ( int16_t ) tag_rssi );
            tag_freq = magicrfid_parse_tag_freq ( rsp );
            log_printf( &logger, " FREQ: %lu\r\n", tag_freq );
            magicrfid_parse_tag_epc ( rsp, &epc );
            log_printf( &logger, " EPC PC: 0x%.4X\r\n", epc.epc_pc );
            log_printf( &logger, " EPC ID (len: %u): ", ( uint16_t ) epc.data_len );
            for ( uint8_t cnt = 0; cnt < epc.data_len; cnt++ )
            {
                log_printf( &logger, "%.2X", ( uint16_t ) epc.data_buf[ cnt ] );
            }
            log_printf( &logger, "\r\n EPC CRC: 0x%.4X\r\n", epc.epc_crc );
            Delay_ms ( 100 );
            magicrfid_clear_buffers ( &magicrfid );
        }
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
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
