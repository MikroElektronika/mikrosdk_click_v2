
---
# XBEE 3 Click

> [XBEE 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5299) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5299&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an XBEE 3 Click board by showing the communication between the two Click boards configured in transparent mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.XBEE3

### Example Key Functions

- `xbee3_cfg_setup` Config Object Initialization function.
```c
void xbee3_cfg_setup ( xbee3_cfg_t *cfg );
```

- `xbee3_init` Initialization function.
```c
err_t xbee3_init ( xbee3_t *ctx, xbee3_cfg_t *cfg );
```

- `xbee3_get_serial_number` This function sends a get serial number command.
```c
err_t xbee3_get_serial_number ( xbee3_t *ctx );
```

- `xbee3_set_device_name` This function sets the device name (node identifier).
```c
err_t xbee3_set_device_name ( xbee3_t *ctx, char *dev_name );
```

- `xbee3_set_destination_address` This function sets the destination address high and low bytes.
```c
err_t xbee3_set_destination_address ( xbee3_t *ctx, char *dest_addr_high, char *dest_addr_low );
```

### Application Init

> Initializes the driver and configures the Click board by performing a factory reset, and setting the device name, destination address, and api mode to transparent.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xbee3_cfg_t xbee3_cfg;  /**< Click config object. */

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
    xbee3_cfg_setup( &xbee3_cfg );
    XBEE3_MAP_MIKROBUS( xbee3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xbee3_init( &xbee3, &xbee3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    xbee3_hw_reset ( &xbee3 );
    xbee3_process( );
    xbee3_clear_app_buf( );
    
    log_printf( &logger, " - Enter command mode -\r\n" );
    xbee3_enter_command_mode ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    xbee3_factory_reset ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Get serial number -\r\n" );
    xbee3_get_serial_number ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    xbee3_set_device_name ( &xbee3, DEVICE_NAME );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Destination Address -\r\n" );
    xbee3_set_destination_address ( &xbee3, DESTINATION_ADDRESS_HIGH, DESTINATION_ADDRESS_LOW );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set API mode -\r\n" );
    xbee3_set_api_mode ( &xbee3, XBEE3_MODE_TRANSPARENT );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Apply changes -\r\n" );
    xbee3_apply_changes ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Save changes -\r\n" );
    xbee3_save_changes ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 );
    
    log_printf( &logger, " - Exit command mode -\r\n" );
    xbee3_exit_command_mode ( &xbee3 );
    Delay_ms ( 100 );
    xbee3_display_rsp ( 1000 ); 
    
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
    xbee3_generic_write( &xbee3, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    xbee3_process( );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        xbee3_clear_app_buf(  );
    }
#endif
}
```

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
