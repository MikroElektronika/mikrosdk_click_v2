
---
# Magic RFID Click

> [Magic RFID Click](https://www.mikroe.com/?pid_product=MIKROE-4425) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4425&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Magic RFID Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagicRFID

### Example Key Functions

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
