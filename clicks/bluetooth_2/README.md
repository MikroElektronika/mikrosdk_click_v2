
---
# Bluetooth 2 Click

> [Bluetooth 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4087) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4087&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Bluetooth 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Bluetooth2

### Example Key Functions

- `bluetooth2_cfg_setup` Config Object Initialization function.
```c
void bluetooth2_cfg_setup ( bluetooth2_cfg_t *cfg );
```

- `bluetooth2_init` Initialization function.
```c
err_t bluetooth2_init ( bluetooth2_t *ctx, bluetooth2_cfg_t *cfg );
```

- `bluetooth2_default_cfg` Click Default Configuration function.
```c
void bluetooth2_default_cfg ( bluetooth2_t *ctx );
```

- `bluetooth2_factory_reset` This function factory resets the device.
```c
err_t bluetooth2_factory_reset ( bluetooth2_t *ctx );
```

- `bluetooth2_set_device_name` This function sets the local device name.
```c
err_t bluetooth2_set_device_name ( bluetooth2_t *ctx, char *dev_name );
```

- `bluetooth2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t bluetooth2_generic_write ( bluetooth2_t *ctx, char *data_buf, uint16_t len );
```

### Application Init

> Initializes the driver, then performs a factory reset, removes all pairings, and sets the local device name.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    bluetooth2_cfg_t bluetooth2_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bluetooth2_cfg_setup( &bluetooth2_cfg );
    BLUETOOTH2_MAP_MIKROBUS( bluetooth2_cfg, MIKROBUS_1 );
    err_t init_flag  = bluetooth2_init( &bluetooth2, &bluetooth2_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bluetooth2_default_cfg ( &bluetooth2 );
    bluetooth2_process( );
    bluetooth2_clear_app_buf( );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    bluetooth2_factory_reset ( &bluetooth2 );
    bluetooth2_display_rsp ( 2000 ); 
    
    log_printf( &logger, " - Enable OK response -\r\n" );
    bluetooth2_enable_ok_response ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Remove Pairings -\r\n" );
    bluetooth2_remove_pairings ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    bluetooth2_set_device_name ( &bluetooth2, DEVICE_NAME );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Logs all the received messages/responses on the USB UART, and if there's any device
> connected to the Click board the module sends a desired message every 5 seconds back to it.

```c
void application_task ( void )
{
    bluetooth2_process();
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 200 );
        bluetooth2_process();
        
        if ( strstr( app_buf, RSP_RING ) )
        {
            connection_flag = 1;
            send_cnt = 0;
        }
        if ( strstr( app_buf, RSP_NO_CARRIER ) )
        {
            connection_flag = 0;
            send_cnt = 0;
        }
        log_printf( &logger, "%s", app_buf );
        bluetooth2_clear_app_buf(  );
    }
    
    if ( connection_flag == 1 && send_cnt++ > SENDING_FREQ )
    {
        bluetooth2_generic_write( &bluetooth2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
        send_cnt = 0;
    }
    
    Delay_ms ( 1 );
}
```

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages with each other.

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
