
---
# NFC Tag 2 Click

> [NFC Tag 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2462) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2462&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of NFC Tag 2 Click by storing and verifying
> an NDEF URI record in user EEPROM and monitoring the RF field.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFCTag2

### Example Key Functions

- `nfctag2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void nfctag2_cfg_setup ( nfctag2_cfg_t *cfg );
```

- `nfctag2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t nfctag2_init ( nfctag2_t *ctx, nfctag2_cfg_t *cfg );
```

- `nfctag2_default_cfg` This function configures NFC Tag 2 Click for EEPROM access, RF writes, active-low RF field detection, and an approximately 20 ms I2C watchdog.
```c
err_t nfctag2_default_cfg ( nfctag2_t *ctx );
```

- `nfctag2_write_ndef_uri` This function stores a complete URI as an NDEF URI record in NFC Tag 2 Click user EEPROM and verifies the stored data through I2C readback.
```c
err_t nfctag2_write_ndef_uri ( nfctag2_t *ctx, char *uri, nfctag2_ndef_stage_t *stage );
```

- `nfctag2_write_ndef_text` This function stores one short UTF-8 Text record in NFC Tag 2 Click user EEPROM and verifies the stored data through I2C readback.
```c
err_t nfctag2_write_ndef_text ( nfctag2_t *ctx, char *text, nfctag2_ndef_stage_t *stage );
```

- `nfctag2_get_field_detect` This function reads the NFC Tag 2 Click active-low FD pin connected to mikroBUS INT.
```c
uint8_t nfctag2_get_field_detect ( nfctag2_t *ctx );
```

### Application Init

> Initializes the driver, applies the default configuration, displays the tag UID,
> and writes and verifies a URI record linking to the NFC Tag 2 Click product page.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag2_cfg_t nfctag2_cfg;  /**< Click config object. */

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
    nfctag2_cfg_setup( &nfctag2_cfg );
    NFCTAG2_MAP_MIKROBUS( nfctag2_cfg, MIKROBUS_POSITION_NFCTAG2 );
    if ( I2C_MASTER_ERROR == nfctag2_init( &nfctag2, &nfctag2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( NFCTAG2_ERROR == nfctag2_default_cfg ( &nfctag2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t uid[ NFCTAG2_UID_SIZE ];  /**< Seven-byte NFC tag identifier. */
    nfctag2_ndef_stage_t ndef_stage;  /**< Operation where NDEF preparation failed. */

    // Avoid competing with an RF reader while preparing EEPROM data.
    if ( NFCTAG2_FIELD_PRESENT == nfctag2_get_field_detect( &nfctag2 ) )
    {
        log_printf( &logger, " Remove the NFC reader during initialization.\r\n" );
        while ( NFCTAG2_FIELD_PRESENT == nfctag2_get_field_detect( &nfctag2 ) )
        {
            Delay_ms( 100 );
        }
    }

    if ( NFCTAG2_OK != nfctag2_get_uid( &nfctag2, uid ) )
    {
        log_error( &logger, " UID read." );
        for ( ; ; );
    }
    log_printf( &logger, " UID:" );
    for ( uint8_t cnt = 0; cnt < NFCTAG2_UID_SIZE; cnt++ )
    {
        log_printf( &logger, " %.2X", ( uint16_t ) uid[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    if ( NFCTAG2_OK != nfctag2_write_ndef_uri( &nfctag2, APP_NDEF_URI, &ndef_stage ) )
    {
        log_printf( &logger, " NDEF write failed at stage: %u\r\n", ( uint32_t ) ndef_stage );
        for ( ; ; );
    }
    log_printf( &logger, " NDEF URI stored and verified: %s\r\n", APP_NDEF_URI );

    log_printf( &logger, " Bring an NFC-enabled phone near the antenna to open the product page.\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the field detection pin and reports when an RF field is detected or removed.

```c
void application_task ( void )
{
    static uint8_t previous_field = NFCTAG2_FIELD_ABSENT;  /**< Last reported FD pin level. */
    uint8_t field = nfctag2_get_field_detect( &nfctag2 );

    // GPIO polling leaves the shared memory available to the RF reader.
    if ( field != previous_field )
    {
        if ( NFCTAG2_FIELD_PRESENT == field )
        {
            log_printf( &logger, " RF field: Detected\r\n" );
        }
        else
        {
            log_printf( &logger, " RF field: Removed\r\n" );
        }
        previous_field = field;
    }
    Delay_ms( 10 );
}
```

### Note

> Before first run, format the tag with NFC TagWriter using "Erase to factory default"
> or "Erase & format as NDEF". Keep the phone away during initialization. Enable NFC
> and use an NFC-enabled phone to open the stored product link.
> Initialization replaces existing NDEF content; unchanged data is not rewritten.
> RF field detection does not confirm that the phone has read the record.

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
