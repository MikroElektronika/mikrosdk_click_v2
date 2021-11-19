
---
# NFC 4 click

> NFC 4 Click is a compact add-on board that contains an NFC transceiver for contactless communication. This board features the ST25R3916, a multi-purpose NFC transceiver supporting passive peer-to-peer functionality and NFC card-emulation mode, as well as NFC reader operation from STMicroelectronics. It features high RF output power to directly drive an antenna etched on the PCB, alongside its tuning circuit, at high efficiency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfc4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nfc-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the NFC4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC4 Click driver.

#### Standard key functions :

- `nfc4_cfg_setup` Config Object Initialization function.
```c
void nfc4_cfg_setup ( nfc4_cfg_t *cfg );
```

- `nfc4_init` Initialization function.
```c
err_t nfc4_init ( nfc4_t *ctx, nfc4_cfg_t *cfg );
```

- `nfc4_default_cfg` Click Default Configuration function.
```c
err_t nfc4_default_cfg ( nfc4_t *ctx );
```

#### Example key functions :

- `nfc4_get_mifare_tag_uid` This function reads the UID of a mifare tag.
```c
err_t nfc4_get_mifare_tag_uid ( nfc4_t *ctx, uint8_t *uid, uint8_t *uid_len );
```

- `nfc4_write_register` This function writes a desired data to the selected register.
```c
err_t nfc4_write_register ( nfc4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `nfc4_read_register` This function reads a desired data from the selected register.
```c
err_t nfc4_read_register ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of NFC 4 Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    nfc4_cfg_t nfc4_cfg;    /**< Click config object. */

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
    nfc4_cfg_setup( &nfc4_cfg );
    NFC4_MAP_MIKROBUS( nfc4_cfg, MIKROBUS_1 );
    err_t init_flag  = nfc4_init( &nfc4, &nfc4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    NFC4_SET_DATA_SAMPLE_EDGE;
    
    if ( NFC4_ERROR == nfc4_default_cfg ( &nfc4 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

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
    uint8_t tag_uid[ 10 ] = { 0 };
    uint8_t uid_len = 0;
    
    if( NFC4_OK == nfc4_get_mifare_tag_uid( &nfc4, tag_uid, &uid_len ) )
    {
        log_printf( &logger, " Tag UID: " );
        for ( uint8_t cnt = 0; cnt < uid_len; cnt++ )
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms( 500 );
    }
}

```

## Note

> For testing purposes we used MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
