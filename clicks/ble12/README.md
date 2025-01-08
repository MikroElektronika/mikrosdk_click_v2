
---
# BLE 12 Click

> [BLE 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4874) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4874&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from BLE 12 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE12

### Example Key Functions

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

### Application Init

> Initializes UART driver and logs UART. 
> After driver initialization, the app performs a wake-up module, 
> enters command mode, sets the device name and advertising time interval, 
> and disconnects all connections. 
> After that, the blinking of the yellow LED Indicates
> that the BLE 12 Click board&trade; is ready for connection. 
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
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  BLE 12 Click\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  Command mode\r\n" );
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_CMD );
    Delay_ms ( 100 );
    
    ble12_event_startup( &ble12 );
    Delay_ms ( 100 );
     
    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
    Delay_ms ( 100 );
    
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Set device name:" );
    log_printf( &logger, " BLE 12 Click\r\n" );
    ble12_set_device_name( &ble12, "BLE 12 Click" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "> Set Adv. Interval: 99 ms\r\n" );
    ble12_set_adv_interval( &ble12, "0099" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "> Disconnect all connections\r\n" );
    ble12_disconnect( &ble12 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "  Please connect your device\r\n" );
    
    do
    {
        ble12_process(); 
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
        Delay_ms ( 50 );
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
        Delay_ms ( 50 );
    }
    while ( !strstr( app_buf, BLE12_EVT_CONNECTED ) );
    Delay_ms ( 100 );

    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\tDevice connected\r\n" );
    Delay_ms ( 100 );
    
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_DATA );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t    Data mode\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );
    
    ble12_process();
    ble12_clear_app_buf( );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the BLE 12 Click board&trade;. 
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

### Note

> We have used the Serial Bluetooth Terminal Android application for the test
> and you can find it at the link:
> https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
