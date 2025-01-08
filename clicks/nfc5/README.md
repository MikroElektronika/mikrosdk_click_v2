
---
# NFC 5 Click

> [NFC 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6029) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6029&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of NFC 4 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC5

### Example Key Functions

- `nfc5_cfg_setup` Config Object Initialization function.
```c
void nfc5_cfg_setup ( nfc5_cfg_t *cfg );
```

- `nfc5_init` Initialization function.
```c
err_t nfc5_init ( nfc5_t *ctx, nfc5_cfg_t *cfg );
```

- `nfc5_default_cfg` Click Default Configuration function.
```c
err_t nfc5_default_cfg ( nfc5_t *ctx );
```

- `nfc5_get_mifare_tag_uid` This function reads the UID of a mifare tag.
```c
err_t nfc5_get_mifare_tag_uid ( nfc5_t *ctx, uint8_t *uid, uint8_t *uid_len );
```

- `nfc5_write_reg` This function writes a desired data to the selected register.
```c
err_t nfc5_write_reg ( nfc5_t *ctx, uint8_t reg, uint8_t data_in );
```

- `nfc5_read_reg` This function reads a desired data from the selected register.
```c
err_t nfc5_read_reg ( nfc5_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc5_cfg_t nfc5_cfg;  /**< Click config object. */

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
    nfc5_cfg_setup( &nfc5_cfg );
    NFC5_MAP_MIKROBUS( nfc5_cfg, MIKROBUS_1 );
    err_t init_flag = nfc5_init( &nfc5, &nfc5_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC5_ERROR == nfc5_default_cfg ( &nfc5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> If there's a tag detected, it reads its UID and displays it on the USB UART every 500ms.

```c
void application_task ( void )
{
    uint8_t tag_uid[ NFC5_NFCA_CASCADE_3_UID_LEN ] = { 0 };
    uint8_t tag_uid_len = 0;
    
    if ( NFC5_OK == nfc5_get_mifare_tag_uid( &nfc5, tag_uid, &tag_uid_len ) )
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

> Only ISO14443-A type tags are compatible with this example.
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
