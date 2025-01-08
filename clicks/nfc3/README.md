
---
# NFC 3 Click

> [NFC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5538) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5538&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of NFC 3 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC3

### Example Key Functions

- `nfc3_cfg_setup` Config Object Initialization function.
```c
void nfc3_cfg_setup ( nfc3_cfg_t *cfg );
```

- `nfc3_init` Initialization function.
```c
err_t nfc3_init ( nfc3_t *ctx, nfc3_cfg_t *cfg );
```

- `nfc3_reset` NFC 3 reset function.
```c
void nfc3_reset ( nfc3_t *ctx );
```

- `nfc3_read_card_uid` NFC 3 read card UID function.
```c
uint8_t nfc3_read_card_uid ( nfc3_t *ctx, uint8_t *data_out );
```

- `nfc3_read_firmware_version` NFC 3 reading firmware version function.
```c
err_t nfc3_read_firmware_version ( nfc3_t *ctx, uint16_t *data_out );
```

- `nfc3_read_eeprom_version` NFC 3 reading EEPROM version function.
```c
err_t nfc3_read_eeprom_version ( nfc3_t *ctx, uint16_t *data_out );
```

### Application Init

> Initializes driver and logger, then enables the Click board and reads the device product, firmware and eeprom versions.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc3_cfg_t nfc3_cfg;  /**< Click config object. */

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

    nfc3_cfg_setup( &nfc3_cfg );
    NFC3_MAP_MIKROBUS( nfc3_cfg, MIKROBUS_1 );
    err_t init_flag = nfc3_init( &nfc3, &nfc3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    nfc3_reset ( &nfc3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "------------------------\r\n" );
    nfc3_read_product_version ( &nfc3, &info );
    log_printf( &logger, "Product version: 0x%.4X\r\n", info );
    nfc3_read_firmware_version ( &nfc3, &info );
    log_printf( &logger, "Firmware version: 0x%.4X\r\n", info );
    nfc3_read_eeprom_version ( &nfc3, &info );
    log_printf( &logger, "EEPROM version: 0x%.4X\r\n", info );
    log_printf( &logger, "------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> If there's a tag detected, it reads its UID and displays it on USB UART.

```c
void application_task ( void )
{
    uint8_t uid[ 7 ];
    uint8_t uid_len;
    uid_len = nfc3_read_card_uid( &nfc3, uid );
    if ( uid_len > 0 )
    {
        log_printf( &logger, "Tag UID: " );
        for ( uint8_t cnt = 0; cnt < uid_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) uid[ cnt ] );
        }
        log_printf( &logger, "\r\n------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> Only tags with 4-byte or 7-byte UIDs are compatible with this example. We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

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
