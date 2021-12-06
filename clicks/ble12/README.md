\mainpage Main Page

---
# BLE 12 click

> BLE 12 Click is a compact add-on board that provides BT/BLE connectivity for any embedded application. This board features the BM832A, a powerful and highly flexible, ultra low power Bluetooth Low Energy (BLE) module from Fanstel. Based on the Nordic nRF52 SoC, the BM832A supports Bluetooth 5.0 Low-Energy (BLE) connectivity while delivering RF range and performance, debugging and enhanced security features, and low power consumption. It also comes with an ARM Cortex™ M4(F) MCU up to 192kB flash and 24kB RAM, embedded 2.4GHz multi-protocol transceiver, and an integrated PCB trace antenna. This Click board™ is suitable for low-cost Bluetooth low energy applications such as building automation and sensor networks, portable medical, connected home, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BLE12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BLE12 Click driver.

#### Standard key functions :

- `ble12_cfg_setup` Config Object Initialization function.
```c
void ble12_cfg_setup ( ble12_cfg_t *cfg );
```

- `ble12_init` Initialization function.
```c
err_t ble12_init ( ble12_t *ctx, ble12_cfg_t *cfg );
```

- `ble12_default_cfg` Click Default Configuration function.
```c
err_t ble12_default_cfg ( ble12_t *ctx );
```

#### Example key functions :

- `ble12_set_device_name` BLE 12 set device name function.
```c
err_t ble12_set_device_name ( ble12_t *ctx, uint8_t *device_name );
```

- `ble12_set_op_mode` BLE 12 set operating mode function.
```c
err_t ble12_set_op_mode ( ble12_t *ctx, uint8_t op_mode );
```

- `ble12_send_cmd` BLE 12 sends the command function.
```c
err_t ble12_send_cmd ( ble12_t *ctx, char *cmd );
```

## Example Description

> This example reads and processes data from BLE 12 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART driver and logs UART. 
> After driver initialization, the app performs a wake-up module, 
> enters command mode, sets the device name and advertising time interval, 
> and disconnects all connections. 
> After that, the blinking of the yellow LED Indicates
> that the BLE 12 Click board™ is ready for connection. 
> After establishing the connection, the yellow LED is turned on.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble12_cfg_t ble12_cfg;  /**< Click config object. */

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
    ble12_cfg_setup( &ble12_cfg );
    BLE12_MAP_MIKROBUS( ble12_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ble12_init( &ble12, &ble12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE12_ERROR == ble12_default_cfg ( &ble12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  BLE 12 Click\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  Command mode\r\n" );
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_CMD );
    Delay_ms( 100 );
    
    ble12_event_startup( &ble12 );
    Delay_ms( 100 );
     
    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
    Delay_ms( 100 );
    
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Set device name:" );
    log_printf( &logger, " BLE 12 Click\r\n" );
    ble12_set_device_name( &ble12, "BLE 12 Click" );
    Delay_ms( 100 );
    
    log_printf( &logger, "> Set Adv. Interval: 99 ms\r\n" );
    ble12_set_adv_interval( &ble12, "0099" );
    Delay_ms( 100 );
    
    log_printf( &logger, "> Disconnect all connections\r\n" );
    ble12_disconnect( &ble12 );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "  Please connect your device\r\n" );
    
    do
    {
        ble12_process(); 
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
        Delay_ms( 50 );
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
        Delay_ms( 50 );
    }
    while ( !strstr( app_buf, BLE12_EVT_CONNECTED ) );
    Delay_ms( 100 );

    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\tDevice connected\r\n" );
    Delay_ms( 100 );
    
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_DATA );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t    Data mode\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms( 100 );
    
    ble12_process();
    ble12_clear_app_buf( );
    Delay_ms( 100 );
}

```

### Application Task

> This example demonstrates the use of the BLE 12 Click board™. 
> Reads the received data and parses it. 
> Results are being sent to the Usart Terminal, where you can track their changes.

```c

void application_task ( void ) 
{      
    ble12_process();
    
    if ( app_buf_len > 0 ) 
    { 
        log_printf( &logger, "%s", app_buf );
        ble12_clear_app_buf(  );    
    }
}

```

## Note

> We have used the Serial Bluetooth Terminal Android application for the test
> and you can find it at the link:
> https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
