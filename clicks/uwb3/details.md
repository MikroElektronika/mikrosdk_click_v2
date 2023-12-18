
---
# UWB 3 click

> UWB 3 Click is a compact add-on board that brings Ultra-Wideband communication to your application. This board features the DWM3001, a fully integrated UWB transceiver module from Qorvo. The module integrates the DW3110 IC, nRF52833 MCU, planar UWB antenna, accelerometer, power management, and crystal. It is a fully calibrated, tested, and validated design. This Click board™ makes the perfect solution for the development of precision real-time location systems (RTLS) using two-way ranging or TDoA schemes in various markets, location-aware wireless sensor networks (WSNs), and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uwb3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uwb-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART type


# Software Support

We provide a library for the UWB 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UWB 3 Click driver.

#### Standard key functions :

- `uwb3_cfg_setup` Config Object Initialization function.
```c
void uwb3_cfg_setup ( uwb3_cfg_t *cfg );
```

- `uwb3_init` Initialization function.
```c
err_t uwb3_init ( uwb3_t *ctx, uwb3_cfg_t *cfg );
```

#### Example key functions :

- `uwb3_send_cmd` This function sends a specified command to the click module.
```c
void uwb3_send_cmd ( uwb3_t *ctx, uint8_t *cmd );
```

- `uwb3_send_cmd_with_parameter` This function sends a command with specified parameter to the click module.
```c
void uwb3_send_cmd_with_parameter ( uwb3_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `uwb3_reset_device` This function resets the device by toggling the RST pin state.
```c
void uwb3_reset_device ( uwb3_t *ctx );
```

## Example Description

> This example demonstrates the use of an UWB 3 click board by showing the communication between the two click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board for the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb3_cfg_t uwb3_cfg;  /**< Click config object. */

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
    uwb3_cfg_setup( &uwb3_cfg );
    UWB3_MAP_MIKROBUS( uwb3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uwb3_init( &uwb3, &uwb3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    // Clear buffers
    uwb3_process( &uwb3 );
    uwb3_clear_app_buf( );
    
    // Switch to stop mode
    uwb3_send_cmd ( &uwb3, UWB3_CMD_STOP );
    uwb3_display_response ( &uwb3 );
    Delay_ms ( 1000 );
    
#if ( DEMO_APP == APP_RESPONDER_1 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_1_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 1\r\n" );
#elif ( DEMO_APP == APP_RESPONDER_2 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_2_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 2\r\n" );
#else
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_INITF, INITIATOR_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Initiator\r\n" );
#endif
    
    uwb3_clear_app_buf( );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all incoming ranging block messages and displays them
on the USB UART. One click board should be configured to initiator mode and
the others to responder 1 or 2. The initiator click displays the address
and distance of each responder nodes, while the responder click boards displays
the address and distance of the initiator click board.

```c
void application_task ( void )
{
    if ( UWB3_OK == uwb3_process( &uwb3 ) ) 
    {
        if ( UWB3_OK == uwb3_parse_ranging_block ( ) )
        {
            uwb3_clear_app_buf( );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UWB3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
