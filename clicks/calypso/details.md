
---
# Calypso click

> Calypso Click is a compact add-on board for wireless connectivity in embedded applications. This board features the WIRL-WIFS Calypso WLAN module (2610011025000) from Würth Elektronik, which supports IEEE 802.11 b/g/n standards and includes a fully integrated TCP/IP stack. It also features edge castellated connections, a smart antenna configuration, and supports both IPv4 and IPv6 protocols, including SNTP, DHCP, mDNS, HTTP(S), and MQTT, offering secure connectivity with six simultaneous secure sockets, secure boot, and OTA updates.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/calypso_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/calypso-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the Calypso Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Calypso Click driver.

#### Standard key functions :

- `calypso_cfg_setup` Config Object Initialization function.
```c
void calypso_cfg_setup ( calypso_cfg_t *cfg );
```

- `calypso_init` Initialization function.
```c
err_t calypso_init ( calypso_t *ctx, calypso_cfg_t *cfg );
```

- `calypso_default_cfg` Click Default Configuration function.
```c
err_t calypso_default_cfg ( calypso_t *ctx );
```

#### Example key functions :

- `calypso_set_app_mode` This function is used to set selected APP mode of Calypso click board.
```c
err_t calypso_set_app_mode ( calypso_t *ctx, uint8_t mode_sel );
```

- `calypso_hw_reset` This function is used to perform HW reset.
```c
void calypso_hw_reset ( calypso_t *ctx );
```

- `calypso_send_cmd` This function is used to send a desired command.
```c
void calypso_send_cmd ( calypso_t *ctx, uint8_t *at_cmd_buf );
```

## Example Description

> This example demonstrates the use of Calypso click board by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and places AT command mode, tests the communication, and after that restarts the device, and performs example configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    calypso_cfg_t calypso_cfg;  /**< Click config object. */

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
    calypso_cfg_setup( &calypso_cfg );
    CALYPSO_MAP_MIKROBUS( calypso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == calypso_init( &calypso, &calypso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CALYPSO_ERROR == calypso_default_cfg ( &calypso ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    calypso_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, displaces it on the UART terminal, and then closes the connection.

```c
void application_task ( void ) 
{
    calypso_example( );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Calypso

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
