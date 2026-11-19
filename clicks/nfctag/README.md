
---
# NFC Tag Click

> [NFC Tag Click](https://www.mikroe.com/?pid_product=MIKROE-1726) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1726&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of NFC Tag Click by storing and verifying
> an NDEF URI record in user EEPROM and monitoring the GPO pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFCTag

### Example Key Functions

- `nfctag_cfg_setup` This function sets the default I2C address and marks all pins as unconnected.
```c
void nfctag_cfg_setup ( nfctag_cfg_t *cfg );
```

- `nfctag_init` This function initializes SCL and SDA for software I2C and configures RF-DIS and GPO.
```c
err_t nfctag_init ( nfctag_t *ctx, nfctag_cfg_t *cfg );
```

- `nfctag_default_cfg` This function enables RF communication on NFC Tag Click, clears a stale I2C token, and checks that the NDEF Tag Application can be selected.
```c
err_t nfctag_default_cfg ( nfctag_t *ctx );
```

- `nfctag_get_uid` This function reads the seven-byte NFC Tag Click UID using its own I2C session.
```c
err_t nfctag_get_uid ( nfctag_t *ctx, uint8_t *uid );
```

- `nfctag_write_ndef_uri` This function stores a complete URI as an NDEF URI record in NFC Tag Click user EEPROM and verifies the stored data through I2C readback.
```c
err_t nfctag_write_ndef_uri ( nfctag_t *ctx, char *uri, nfctag_ndef_stage_t *stage );
```

- `nfctag_get_gpo` This function reads the NFC Tag Click active-low GPO pin on mikroBUS INT directly through GPIO.
```c
uint8_t nfctag_get_gpo ( nfctag_t *ctx );
```

### Application Init

> Initializes the driver, applies the default configuration, displays the tag UID,
> and writes and verifies a URI record linking to the NFC Tag Click product page.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag_cfg_t nfctag_cfg;  /**< Click config object. */
    err_t error_flag;

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
    nfctag_cfg_setup( &nfctag_cfg );
    NFCTAG_MAP_MIKROBUS( nfctag_cfg, MIKROBUS_POSITION_NFCTAG );
    if ( NFCTAG_ERROR == nfctag_init( &nfctag, &nfctag_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    error_flag = nfctag_default_cfg( &nfctag );
    if ( NFCTAG_OK != error_flag )
    {
        log_error( &logger, " Default configuration failed, error: %d, SW: %.4X",
                   ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    
    uint8_t uid[ NFCTAG_UID_SIZE ];  /**< Seven-byte NFC tag identifier. */
    nfctag_ndef_stage_t ndef_stage;  /**< Operation where NDEF preparation failed. */
    
    error_flag = nfctag_get_uid( &nfctag, uid );
    if ( NFCTAG_OK != error_flag )
    {
        log_error( &logger, " UID read failed at stage: %u, error: %d, SW: %.4X",
                   ( uint16_t ) nfctag.uid_stage, ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    log_printf( &logger, " UID:" );
    for ( uint8_t cnt = 0; cnt < NFCTAG_UID_SIZE; cnt++ )
    {
        log_printf( &logger, " %.2X", ( uint16_t ) uid[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    error_flag = nfctag_write_ndef_uri( &nfctag, APP_NDEF_URI, &ndef_stage );
    if ( NFCTAG_OK != error_flag )
    {
        log_printf( &logger, " NDEF write failed at stage: %u, error: %d, SW: %.4X\r\n",
                    ( uint16_t ) ndef_stage, ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    log_printf( &logger, " NDEF URI stored and verified: %s\r\n", ( char * ) APP_NDEF_URI );

    log_printf( &logger, " Bring an NFC-enabled phone near the antenna to open the product page.\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the GPO pin and reports changes in its active-low output level.

```c
void application_task ( void ) 
{
    static uint8_t previous_gpo = NFCTAG_GPO_INACTIVE;  /**< Previous GPO pin level. */
    uint8_t gpo = nfctag_get_gpo( &nfctag );

    // GPIO polling leaves the shared memory available to the RF reader.
    if ( gpo != previous_gpo )
    {
        if ( NFCTAG_GPO_ACTIVE == gpo )
        {
            log_printf( &logger, " GPO: Active\r\n" );
        }
        else
        {
            log_printf( &logger, " GPO: Inactive\r\n" );
        }
        previous_gpo = gpo;
    }
    Delay_ms( 10 );
}
```

### Note

> Initialization replaces the NFC message on the Click board if it differs from the product link.
> Keep your phone away during initialization, then hold it near the antenna with NFC enabled to open the link.

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
