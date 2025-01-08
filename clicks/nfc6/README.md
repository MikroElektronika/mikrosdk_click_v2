
---
# NFC 6 Click

> [NFC 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5935) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5935&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of NFC 6 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC6

### Example Key Functions

- `nfc6_cfg_setup` Config Object Initialization function.
```c
void nfc6_cfg_setup ( nfc6_cfg_t *cfg );
```

- `nfc6_init` Initialization function.
```c
err_t nfc6_init ( nfc6_t *ctx, nfc6_cfg_t *cfg );
```

- `nfc6_default_cfg` Click Default Configuration function.
```c
err_t nfc6_default_cfg ( nfc6_t *ctx );
```

- `nfc6_send_command` This function sends a desired command by using SPI serial interface.
```c
err_t nfc6_send_command ( nfc6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );
```

- `nfc6_read_data` This function reads a response data bytes by using SPI serial interface.
```c
err_t nfc6_read_data ( nfc6_t *ctx, uint8_t *data_out, uint16_t buffer_size, uint16_t *rx_len );
```

- `nfc6_read_mifare_tag_uid` This function reads the UID of a MIFARE ISO14443-A type tags with 4-byte or 7-byte UIDs.
```c
err_t nfc6_read_mifare_tag_uid ( nfc6_t *ctx, uint8_t *tag_uid, uint8_t *tag_uid_len );
```

### Application Init

> Initializes the driver and logger, performs the Click default configuration and reads the device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc6_cfg_t nfc6_cfg;  /**< Click config object. */

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
    nfc6_cfg_setup( &nfc6_cfg );
    NFC6_MAP_MIKROBUS( nfc6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == nfc6_init( &nfc6, &nfc6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC6_ERROR == nfc6_default_cfg ( &nfc6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t device_id[ 13 ] = { 0 };
    nfc6_send_command ( &nfc6, NFC6_CMD_IDN, NULL, NULL );
    if ( NFC6_OK == nfc6_read_data ( &nfc6, device_id, sizeof ( device_id ), NULL ) )
    {
        log_printf ( &logger, " Device ID: %s\r\n", device_id );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> If there's a tag detected, it reads its UID and displays it on the USB UART every 500ms.

```c
void application_task ( void )
{
    uint8_t tag_uid[ NFC6_TAG_UID_MAX_LEN ] = { 0 };
    uint8_t tag_uid_len = 0;
    if ( NFC6_OK == nfc6_read_mifare_tag_uid ( &nfc6, tag_uid, &tag_uid_len ) )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_uid_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms ( 500 );
    }
}
```

### Note

> Only ISO14443-A type tags with 4-byte or 7-byte UIDs are compatible with this example.
We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

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
