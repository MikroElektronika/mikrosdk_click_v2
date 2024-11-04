
---
# ANNA-B412 Click

> ANNA-B412 Click is a compact add-on board that provides BT/BLE connectivity for any embedded application. 
> This board features the ANNA-B412, a standalone Bluetooth 5.1 low-energy module from u-blox. 
> It is a System-in-Package (SiP) design with pre-flashed u-connectXpress software, 
> which supports Bluetooth LE Serial port service, GATT client and server, Bluetooth beacons, 
> Bluetooth long-range, NFC, and simultaneous peripheral and central roles. 
> The Bluetooth module in LE mode can achieve up to 2Mbps data rates.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/annab412_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/anna-b412-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type


# Software Support

We provide a library for the ANNA-B412 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ANNA-B412 Click driver.

#### Standard key functions :

- `annab412_cfg_setup` Config Object Initialization function.
```c
void annab412_cfg_setup ( annab412_cfg_t *cfg );
```

- `annab412_init` Initialization function.
```c
err_t annab412_init ( annab412_t *ctx, annab412_cfg_t *cfg );
```

- `annab412_default_cfg` Click Default Configuration function.
```c
err_t annab412_default_cfg ( annab412_t *ctx );
```

#### Example key functions :

- `annab412_set_cmd_conn_mode` ANNA-B412 set connectability mode function.
```c
err_t annab412_set_cmd_conn_mode ( annab412_t *ctx, uint8_t mode );
```

- `annab412_set_cmd_discover_mode` ANNA-B412 set discoverability mode function.
```c
err_t annab412_set_cmd_discover_mode ( annab412_t *ctx, uint8_t mode );
```

- `annab412_set_cmd_device_name` ANNA-B412 set device name function.
```c
err_t annab412_set_cmd_device_name ( annab412_t *ctx, char *device_name );
```

## Example Description

> This example demonstrates the use of ANNA-B412 Click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    annab412_cfg_t annab412_cfg;  /**< Click config object. */

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
    annab412_cfg_setup( &annab412_cfg );
    ANNAB412_MAP_MIKROBUS( annab412_cfg, MIKROBUS_1 );
    if ( UART_ERROR == annab412_init( &annab412, &annab412_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANNAB412_ERROR == annab412_default_cfg ( &annab412 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    annab412_set_cmd_echo_on( &annab412 );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );
    
    annab412_set_cmd_device_name( &annab412, DEVICE_NAME );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );

    annab412_set_cmd_discover_mode( &annab412, ANNAB412_DISCOVERABLE_MODE_ON );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );

    annab412_set_cmd_enter_mode( &annab412, ANNAB412_ENTER_MODE_DATA );
    annab412_display_rsp( RSP_OK );
    Delay_ms ( 100 );
    
    annab412_set_dsr_pin( &annab412, ANNAB412_PIN_STATE_LOW );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    annab412_process( &annab412 );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        annab412_clear_app_buf( );
    }
}
```

## Note

> We have used the BLE Scanner smartphone application for the test.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ANNAB412

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
