\mainpage Main Page

---
# NFC 6 click

> NFC 6 Click is a compact add-on board that contains an NFC transceiver for contactless communication. This board features the ST25R95, a near-field communication transceiver from STMicroelectronics. It supports reader and writer operating modes and emulates ISO/IEC 14443-3 Type A cards. The RF communications are done over the 13.56MHz. The transceiver features tag detection mode, field detection mode, transmission and reception modes, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfc6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nfc-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the NFC 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC 6 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of NFC 6 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, performs the click default configuration and reads the device ID.

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
        Delay_ms( 500 );
    }
}
```

## Note

> Only ISO14443-A type tags with 4-byte or 7-byte UIDs are compatible with this example.
We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
