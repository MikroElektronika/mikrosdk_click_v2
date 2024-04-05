\mainpage Main Page

---
# NFC 3 click

NFC 3 Click is a compact add-on board that contains an NFC transceiver for contactless communication at 13.56MHz. This board features the PN5180A0HN, a highly integrated high-performance full NFC Forum-compliant frontend from NXP Semiconductors. The PN5180A0HN utilizes an outstanding modulation and demodulation concept for different contactless communication methods and protocols. It is fully compliant with many Reader/Writer standards (ISO 14443A/B, ISO 15693, ISO 18092, and more), alongside support for reading all NFC tag types (type 1, 2, 3, 4A, and 4B). Besides the SPI host interface, it also features high RF output power to drive an antenna etched on the PCB directly, besides its tuning circuit, at high efficiency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfc3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nfc-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the NFC3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC3 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of NFC 3 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and logger, then enables the click board and reads the device product, firmware and eeprom versions.

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

## Note

> Only tags with 4-byte or 7-byte UIDs are compatible with this example. We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
