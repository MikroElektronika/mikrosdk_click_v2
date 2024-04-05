
---
# BLE 6 click

> BLE 6 Click is a Bluetooth low energy system-on-chip application processor certified module, compliant with BT specifications v5.0 and BQE qualified. The featured BlueNRG-M2 module developed by STMicroelectronics supports multiple roles simultaneously and can act at the same time as Bluetooth master and slave device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-6-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BLE6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BLE6 Click driver.

#### Standard key functions :

- `ble6_cfg_setup` Config Object Initialization function.
```c
void ble6_cfg_setup ( ble6_cfg_t *cfg );
```

- `ble6_init` Initialization function.
```c
err_t ble6_init ( ble6_t *ctx, ble6_cfg_t *cfg );
```

#### Example key functions :

- `ble6_set_response_handler` Set response handlers function.
```c
void ble6_set_response_handler ( void ( *handler )( uint8_t* ), ble6_hdl_t driver_hdl );
```

- `ble6_set_handlers` Set handlers function.
```c
void ble6_set_handlers ( ble6_handler_t event_handler, ble6_handler_t eve_hdlr );
```

- `ble6_parser_rsp` Response parser function.
```c
void ble6_parser_rsp ( ble6_t *ctx, ble6_rsp_t *response );
```

## Example Description

> This example reads and processes data from BLE 6 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - UART, sets handlers initialize and enable UART interrupt, reset and configures BLE module, initialize BLE Server Profile ( Services and Characteristics ).

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble6_cfg_t ble6_cfg;  /**< Click config object. */

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
    ble6_cfg_setup( &ble6_cfg );
    BLE6_MAP_MIKROBUS( ble6_cfg, MIKROBUS_1 );
    err_t init_flag  = ble6_init( &ble6, &ble6_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 1000 );
    ble6_power_on( &ble6, BLE6_MODULE_POWER_ON );
    Delay_ms ( 1000 );
    ble6_module_init( );
    Delay_ms ( 100 );
    log_printf( &logger, "-> Local Version Information: \r\n" );
    ble6_send_command( &ble6, &hci_read_local_version_information[ 0 ], 4 );
    Delay_ms ( 100 );
    ble6_handler( );
    ble6_display_log( );
    ble6_local_version_info( );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "-> ACI GAP Update Value: \r\n" );
    ble6_send_command( &ble6, &aci_gatt_update_value[ 0 ], 21 );
    Delay_ms ( 10 );
    ble6_handler( );
    ble6_display_log( );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "-> HCI Set Scan. Response Data: \r\n" );
    ble6_send_command( &ble6, &hci_le_set_scan_response_data[ 0 ], 36 );
    Delay_ms ( 10 );
    ble6_handler( );
    ble6_display_log( );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "-> ACI GAP Set Discoverable: \r\n" );
    ble6_send_command( &ble6, &aci_gap_set_discoverable[ 0 ], 30 );
    Delay_ms ( 10 );
    ble6_handler( );
    ble6_display_log( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> The app starts by checking the system ready flag and returns the Bluetooth device address. After that, 
> the chain of commands creates Primary Server Profiles:
> Device Information, Generic Access and Custom Service to Start Advertising.
> For transmit messages, we use Generic Access Primary Service with Write permissions of the characteristic Element.
> In this example, transmitting message is limited to a maximum of 11 characters.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    ble6_event_handler( );
    
    while ( device_connected_flag ) 
    {
        int32_t cnt = ble6_generic_read( &ble6, rx_response, PROCESS_BUFFER_SIZE );
        Delay_ms ( 100 );
        if ( ( ble6_strncmp( rx_response, hci_le_serverwrite_event, 1 ) == 0 ) && ( cnt > 13 ) ) 
        {
            ble6_response_handler( );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
