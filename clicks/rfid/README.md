\mainpage Main Page

---
# RFID Click

RFid Click features CR95HF 13.56 MHz contactless transceiver as well as trace antenna.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfid_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rfid-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RFID Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RFID Click driver.

#### Standard key functions :

- `rfid_cfg_setup` Config Object Initialization function.
```c
void rfid_cfg_setup ( rfid_cfg_t *cfg );
```

- `rfid_init` Initialization function.
```c
RFID_RETVAL rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg );
```

- `rfid_default_cfg` Click Default Configuration function.
```c
void rfid_default_cfg ( rfid_t *ctx );
```

#### Example key functions :

- `rfid_select_communication_interface` Select communication interface.
```c
err_t rfid_select_communication_interface ( rfid_t* ctx, uint8_t com_interface );
```

- `rfid_get_tag_uid` Get RFID tag uid function.
```c
err_t rfid_get_tag_uid ( rfid_t *ctx, uint8_t rfid_protocol, uint8_t *tag_uid );
```

- `rfid_get_device_id` RFID get device id function.
```c
err_t rfid_get_device_id ( rfid_t *ctx, uint8_t *device_id );
```

## Example Description

> This example demonstrates the use of RFID Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, selects the communication interface and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfid_cfg_t rfid_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    // Click initialization.

    rfid_cfg_setup( &rfid_cfg );
    RFID_MAP_MIKROBUS( rfid_cfg, MIKROBUS_1 );
    err_t error_flag = rfid_init( &rfid, &rfid_cfg );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Selecting communication interface... \r\n" );
    error_flag = rfid_select_communication_interface ( &rfid, RFID_SPI );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring the device... \r\n" );
    error_flag = rfid_default_cfg ( &rfid );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " The device has been configured! \r\n" );
}

```

### Application Task

> If there's a tag detected, it reads its UID and displays it on USB UART.

```c

void application_task ( void )
{
    uint8_t tag_uid[ 20 ] = { 0 };
    uint8_t tag_len = rfid_get_tag_uid( &rfid, RFID_ISO_14443A, tag_uid );
    if ( tag_len > 0 )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}

```

## Note

> It is recommended to tie SSI_0, SSI_1 to VCC/GND at power-up, depending on 
> the communication interface selection by A and B on-board jumpers. 
> SSI_0 - UART: 0 SPI: 1
> SSI_1 - UART: 0 SPI: 0
> 
> Only tags with 4-byte or 7-byte UIDs are compatible with this example.
> We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RFID

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
