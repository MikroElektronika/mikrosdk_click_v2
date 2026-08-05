
---
# NFC 9 Click

> [NFC 9 Click](https://www.mikroe.com/?pid_product=MIKROE-7014) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7014&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of NFC 9 Click board by reading ISO14443-A type tags UID, ATQA, and SAK values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC9

### Example Key Functions

- `nfc9_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void nfc9_cfg_setup ( nfc9_cfg_t *cfg );
```

- `nfc9_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t nfc9_init ( nfc9_t *ctx, nfc9_cfg_t *cfg );
```

- `nfc9_default_cfg` This function executes a default configuration of NFC 9 Click board.
```c
err_t nfc9_default_cfg ( nfc9_t *ctx );
```

- `nfc9_read_tag` This function reads NFC-A basic tag information such as ATQA, SAK and UID.
```c
err_t nfc9_read_tag ( nfc9_t *ctx, nfc9_tag_t *tag );
```

### Application Init

> Initializes the driver and logger, performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc9_cfg_t nfc9_cfg;  /**< Click config object. */

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
    nfc9_cfg_setup( &nfc9_cfg );
    NFC9_MAP_MIKROBUS( nfc9_cfg, MIKROBUS_POSITION_NFC9 );
    if ( SPI_MASTER_ERROR == nfc9_init( &nfc9, &nfc9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( NFC9_ERROR == nfc9_default_cfg( &nfc9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously checks for an NFC tag, reads its UID and related data, and logs the results.

```c
void application_task ( void )
{
    nfc9_tag_t tag_info;
    if ( NFC9_OK == nfc9_read_tag ( &nfc9, &tag_info ) )
    {
        log_printf( &logger, " --- Tag Info ---\r\n" );
        log_printf( &logger, " UID: " );
        for ( uint8_t cnt = 0; cnt < tag_info.uid_len; cnt++ )
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag_info.uid[ cnt ] );
            if ( cnt < ( tag_info.uid_len - 1 ) )
            {
                log_printf( &logger, ":" );
            }
        }
        log_printf( &logger, "\r\n ATQA: 0x%.4X\r\n", tag_info.atqa );
        log_printf( &logger, " SAK: 0x%.2X\r\n\n", tag_info.sak );
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
