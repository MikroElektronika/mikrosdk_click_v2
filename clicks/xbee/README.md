\mainpage Main Page

---
# XBEE click

> XBee Click is a compact add-on board providing wireless connectivity to end-point devices in ZigBee mesh networks. This board features the XB24CZ7PIS-004, a low-power Digi XBee® RF module delivering superior performance and interference immunity from Digi International. With its ultra-sensitive receiver, the XB24CZ7PIS-004 operates in the 2.4GHz ISM band (indoor/urban range of 60m and outdoor of 1200m), allowing the formation of robust mesh network optimized for use in the US, Canada, Europe, Australia, and Japan (worldwide acceptance). Alongside firmware updates, it supports commissioning and LED behaviors to aid device deployment and commissioning.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/xbee_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/xbee-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the XBEE Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for XBEE Click driver.

#### Standard key functions :

- `xbee_cfg_setup` Config Object Initialization function.
```c
void xbee_cfg_setup ( xbee_cfg_t *cfg );
```

- `xbee_init` Initialization function.
```c
err_t xbee_init ( xbee_t *ctx, xbee_cfg_t *cfg );
```

#### Example key functions :

- `xbee_get_serial_number` This function sends a get serial number command.
```c
err_t xbee_get_serial_number ( xbee_t *ctx );
```

- `xbee_set_device_name` This function sets the device name (node identifier).
```c
err_t xbee_set_device_name ( xbee_t *ctx, char *dev_name );
```

- `xbee_set_destination_address` This function sets the destination address high and low bytes.
```c
err_t xbee_set_destination_address ( xbee_t *ctx, char *dest_addr_high, char *dest_addr_low );
```

## Example Description

> This example demonstrates the use of an XBEE click board by showing the communication between the two click boards configured in transparent mode.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board by performing a factory reset, and setting the device name, destination address, and api mode to transparent.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xbee_cfg_t xbee_cfg;  /**< Click config object. */

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
    xbee_cfg_setup( &xbee_cfg );
    XBEE_MAP_MIKROBUS( xbee_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xbee_init( &xbee, &xbee_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    xbee_hw_reset ( &xbee );
    xbee_process( );
    xbee_clear_app_buf( );
    
    log_printf( &logger, " - Enter command mode -\r\n" );
    xbee_enter_command_mode ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    xbee_factory_reset ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Get serial number -\r\n" );
    xbee_get_serial_number ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    xbee_set_device_name ( &xbee, DEVICE_NAME );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Destination Address -\r\n" );
    xbee_set_destination_address ( &xbee, DESTINATION_ADDRESS_HIGH, DESTINATION_ADDRESS_LOW );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set API mode -\r\n" );
    xbee_set_api_mode ( &xbee, XBEE_MODE_TRANSPARENT );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Apply changes -\r\n" );
    xbee_apply_changes ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Save changes -\r\n" );
    xbee_save_changes ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Exit command mode -\r\n" );
    xbee_exit_command_mode ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 ); 
    
    app_buf_len = 0;
    
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
    xbee_generic_write( &xbee, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 3000 ); 
#else
    xbee_process( );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        xbee_clear_app_buf(  );
    }
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.XBEE

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
