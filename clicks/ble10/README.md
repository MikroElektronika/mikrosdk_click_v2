
---
# BLE 10 Click

> [BLE 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5135) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5135&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from BLE 10 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE10

### Example Key Functions

- `ble10_cfg_setup` Config Object Initialization function.
```c
void ble10_cfg_setup ( ble10_cfg_t *cfg );
```

- `ble10_init` Initialization function.
```c
err_t ble10_init ( ble10_t *ctx, ble10_cfg_t *cfg );
```

- `ble10_default_cfg` Click Default Configuration function.
```c
void ble10_default_cfg ( ble10_t *ctx );
```

- `ble10_set_device_name` This function sets the local device name.
```c
err_t ble10_set_device_name ( ble10_t *ctx, char *dev_name );
```

- `ble10_factory_reset` This function factory resets the device.
```c
err_t ble10_factory_reset ( ble10_t *ctx );
```

- `ble10_get_temperature` This function executes get temperature command which returns the current temperature of the module's internal temperature sensor.
```c
err_t ble10_get_temperature ( ble10_t *ctx );
```

### Application Init

> Initializes the driver, then performs a factory reset and sets the local device name.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ble10_cfg_t ble10_cfg;  /**< Click config object. */

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

    ble10_cfg_setup( &ble10_cfg );
    BLE10_MAP_MIKROBUS( ble10_cfg, MIKROBUS_1 );
    err_t init_flag  = ble10_init( &ble10, &ble10_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ble10_default_cfg ( &ble10 );
    ble10_process( );
    ble10_clear_app_buf( );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, " - Factory Reset -\r\n" );
    ble10_factory_reset ( &ble10 );
    ble10_display_rsp ( EVT_RESET );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    ble10_set_device_name ( &ble10, DEVICE_NAME );
    ble10_display_rsp ( RSP_OK );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Logs all the received events/responses on the USB UART. 
> Then checks if there's a specific command string (defined by the GET_TEMP_COMMAND macro) 
> received from the GATT Server, and if so, it executes temperature reading command and logs the results.

```c
void application_task ( void )
{
    ble10_process( );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        ble10_process( );
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        if ( strstr( app_buf, EVT_GATT_VAL ) )
        {
            char get_temp_cmd[ ] = GET_TEMP_COMMAND;
            const char * __generic msg_ptr = strrchr ( app_buf, ',' ) + 1;
            uint8_t msg_len = *( msg_ptr - 2 ) - 48;
            
            if ( msg_len == strlen ( get_temp_cmd ) )
            {
                char get_temp_hex[ 64 ] = { 0 };
                uint8_t get_temp_hex_chr[ 3 ] = { 0 };
                uint8_t cnt = 0;
                for ( cnt = 0; cnt < strlen ( get_temp_cmd ); cnt++ )
                {
                    uint8_to_hex ( get_temp_cmd[ cnt ], get_temp_hex_chr );
                    strcat ( get_temp_hex, get_temp_hex_chr );
                }
            
                if ( 0 == memcmp ( get_temp_hex, msg_ptr, strlen ( get_temp_hex ) ) )
                {
                    ble10_clear_app_buf( );
                    log_printf( &logger, " - Get Temperature -\r\n" );
                    ble10_get_temperature ( &ble10 );
                    ble10_display_rsp ( RSP_OK );
                }
            }
        }
        ble10_clear_app_buf( );
    }
    Delay_ms ( 1 );
}
```

### Note

> We have used the nRF Connect smartphone application for the test. 
> Make sure to configure the GATT Server properly in the nRF Connect application, then you 
> will be able to send a desired command from it, once you connect to the Click board.
> You can use the Sample configuration for GATT Server which comes with the application installation
> and then send a command via Test Service from the Server.

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
