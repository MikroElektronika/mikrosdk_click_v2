
---
# XBEE 2 Click

> Xbee 2 Click is a compact add-on board providing wireless end-point connectivity to other devices. This board features the XB3-24Z8UM, a Digi XBee® 3 transceiver module offering a fully interoperable ecosystem covering all vertical markets from Digi International. Building on industry-leading technology, the pre-certified Digi XBee® 3 module delivers the flexibility to switch between multiple frequencies and wireless protocols as needed (Zigbee, 802.15.4, DigiMesh® and BLE). It can be easily configured and controlled from a simple, central platform and comes with built-in Digi TrustFence® security, identity, and data privacy features which use more than 175 controls to protect against new and evolving cyber threats.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/xbee2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/xbee-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type


# Software Support

We provide a library for the XBEE 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for XBEE 2 Click driver.

#### Standard key functions :

- `xbee2_cfg_setup` Config Object Initialization function.
```c
void xbee2_cfg_setup ( xbee2_cfg_t *cfg );
```

- `xbee2_init` Initialization function.
```c
err_t xbee2_init ( xbee2_t *ctx, xbee2_cfg_t *cfg );
```

#### Example key functions :

- `xbee2_get_serial_number` This function sends a get serial number command.
```c
err_t xbee2_get_serial_number ( xbee2_t *ctx );
```

- `xbee2_set_device_name` This function sets the device name (node identifier).
```c
err_t xbee2_set_device_name ( xbee2_t *ctx, char *dev_name );
```

- `xbee2_set_destination_address` This function sets the destination address high and low bytes.
```c
err_t xbee2_set_destination_address ( xbee2_t *ctx, char *dest_addr_high, char *dest_addr_low );
```

## Example Description

> This example demonstrates the use of an XBEE 2 Click board by showing the communication between the two Click boards configured in transparent mode.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the Click board by performing a factory reset, and setting the device name, destination address, api mode to transparent,
and a device role to join or form network depending on the application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xbee2_cfg_t xbee2_cfg;  /**< Click config object. */

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
    xbee2_cfg_setup( &xbee2_cfg );
    XBEE2_MAP_MIKROBUS( xbee2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xbee2_init( &xbee2, &xbee2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    xbee2_hw_reset ( &xbee2 );
    xbee2_process( );
    xbee2_clear_app_buf( );
    
    log_printf( &logger, " - Enter command mode -\r\n" );
    xbee2_enter_command_mode ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    xbee2_factory_reset ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Get serial number -\r\n" );
    xbee2_get_serial_number ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    xbee2_set_device_name ( &xbee2, DEVICE_NAME );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Destination Address -\r\n" );
    xbee2_set_destination_address ( &xbee2, DESTINATION_ADDRESS_HIGH, DESTINATION_ADDRESS_LOW );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set API mode -\r\n" );
    xbee2_set_api_mode ( &xbee2, XBEE2_MODE_TRANSPARENT );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Device Role -\r\n" );
#ifdef DEMO_APP_TRANSMITTER
    xbee2_set_device_role ( &xbee2, XBEE2_DEVICE_ROLE_JOIN_NETWORK );
#else
    xbee2_set_device_role ( &xbee2, XBEE2_DEVICE_ROLE_FORM_NETWORK );
#endif
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Apply changes -\r\n" );
    xbee2_apply_changes ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Save changes -\r\n" );
    xbee2_save_changes ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 );
    
    log_printf( &logger, " - Exit command mode -\r\n" );
    xbee2_exit_command_mode ( &xbee2 );
    Delay_ms ( 100 );
    xbee2_display_rsp ( 1000 ); 
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired message every 3 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    xbee2_generic_write( &xbee2, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    xbee2_process( );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        xbee2_clear_app_buf(  );
    }
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.XBEE2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
