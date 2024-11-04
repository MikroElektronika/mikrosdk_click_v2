\mainpage Main Page

---
# NFC 5 Click

> NFC 5 Click is a compact add-on board designed for advanced NFC applications. This board features the ST25R3918, a multipurpose NFC transceiver from STMicroelectronics. This Click board™ is built to cater to the growing needs of the Internet of Things (IoT) ecosystem, providing robust NFC reader functionalities, passive peer-to-peer communication, and card emulation modes with outstanding analog performance. Its notable features include exceptional read range with minimal power output, advanced noise reduction, and compatibility with ISO14443, ISO15693, and NFC Forum Tag types 1, 2, 4, and 5.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfc5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nfc-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the NFC 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC 5 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of NFC 4 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

**The demo application is composed of two sections :**

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

## Note

> Only ISO14443-A type tags are compatible with this example.
We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
