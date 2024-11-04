
---
# Smart Card 2 Click

> Smart Card 2 Click is a compact add-on board for reading smart cards. This board features Microchip’s SEC1210, a low-power single-chip Smart Card controller with a UART interface. The SEC1210 bridge controller uses a combination of hardware and software to deliver high-performance and flexible design customization options. It is fully compliant with standards like ISO/IEC 7816, EMV 4.2/4.3, ETSI TS 102 221, and PC/SC, utilizing TrustSpan™ technology that enables digital systems to communicate securely, process, move and store information. With its onboard card holder, it supports data processing with 2FF smart cards, and with an additional connector for external connection, it also allows the processing of a standard 1FF card.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartcard2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/smart-card-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : UART type


# Software Support

We provide a library for the Smart Card 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Card 2 Click driver.

#### Standard key functions :

- `smartcard2_cfg_setup` Config Object Initialization function.
```c
void smartcard2_cfg_setup ( smartcard2_cfg_t *cfg );
```

- `smartcard2_init` Initialization function.
```c
err_t smartcard2_init ( smartcard2_t *ctx, smartcard2_cfg_t *cfg );
```

#### Example key functions :

- `smartcard2_send_ccid` This function sends the CCID command message by using UART serial interface.
```c
err_t smartcard2_send_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_in );
```

- `smartcard2_read_ccid` This function reads a CCID response or event message by using UART serial interface.
```c
err_t smartcard2_read_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_out );
```

- `smartcard2_icc_power_on` This function activates the card by performing an ICC power ON command. The device will respond with a data block containing ICC ATR (Answer to Reset) message.
```c
err_t smartcard2_icc_power_on ( smartcard2_t *ctx, uint8_t power_sel );
```

## Example Description

> This example demonstrates the use of Smart Card 2 Click board by checking the SIM card presence and activating the card on insert. The card should respond with an ATR (Answer to Reset) message.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartcard2_cfg_t smartcard2_cfg;  /**< Click config object. */

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
    smartcard2_cfg_setup( &smartcard2_cfg );
    SMARTCARD2_MAP_MIKROBUS( smartcard2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == smartcard2_init( &smartcard2, &smartcard2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and parses all CCID messages received from the device. Checks the SIM card presence
and activates it if it's inserted. The card should respond with an ATR (Answer to Reset) message.
All data is being logged on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    smartcard2_ccid_t ccid = { 0 };
    if ( SMARTCARD2_OK == smartcard2_read_ccid ( &smartcard2, &ccid ) )
    {
        smartcard2_display_ccid_message ( ccid );
    }
    if ( SMARTCARD2_ICC_PRESENT == icc_status )
    {
        log_printf( &logger, " Activating card... \r\n" );
        smartcard2_icc_power_on ( &smartcard2, SMARTCARD2_POWER_SEL_3V );
        Delay_ms ( 100 );
    }
}
```

## Note

> This example doesn't parse ATR messages.
There are some online ATR parsers which could be used for decoding those messages.
For example: https://smartcard-atr.apdu.fr/

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartCard2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
