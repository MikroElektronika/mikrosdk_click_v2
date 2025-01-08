
---
# BT Click

> [BT Click](https://www.mikroe.com/?pid_product=MIKROE-4384) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4384&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BT Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BT

### Example Key Functions

- `bt_cfg_setup` Config Object Initialization function.
```c
void bt_cfg_setup ( bt_cfg_t *cfg );
```

- `bt_init` Initialization function.
```c
err_t bt_init ( bt_t *ctx, bt_cfg_t *cfg );
```

- `bt_default_cfg` Click Default Configuration function.
```c
err_t bt_default_cfg ( bt_t *ctx );
```

- `bt_set_local_name` This function sets the local name of the device.
```c
err_t bt_set_local_name ( bt_t *ctx, char *name );
```

- `bt_send_package` This function sends a data package to the Click board.
```c
err_t bt_send_package ( bt_t *ctx, bt_package_t pkg );
```

- `bt_read_package` This function waits for the command or event type of message to arrive and then reads the complete message and stores it to pkg structure.
```c
err_t bt_read_package ( bt_t *ctx, bt_package_t *pkg );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bt_cfg_t bt_cfg;    /**< Click config object. */

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

    bt_cfg_setup( &bt_cfg );
    BT_MAP_MIKROBUS( bt_cfg, MIKROBUS_1 );
    err_t init_flag  = bt_init( &bt, &bt_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, " Default Config : %s\r\n\n", ( char * )
                         ( BT_OK == bt_default_cfg ( &bt ) ? "OK" : "FAIL" ) );

    log_printf( &logger, " Set Local Name : %s\r\n\n", ( char * )
                        ( BT_OK == bt_set_local_name ( &bt, "MikroE - BT Click" ) ? "OK" : "FAIL" ) );
    
    log_printf( &logger, " Delete Bondings : %s\r\n\n", ( char * )
                        ( BT_OK == bt_delete_bondings ( &bt ) ? "OK" : "FAIL" ) );
    
    log_printf( &logger, " Set Bondable Mode : %s\r\n\n", ( char * )
                        ( BT_OK == bt_set_bondable_mode ( &bt, BT_SM_SET_BONDABLE_ALLOWED ) ? "OK" : "FAIL" ) );
    
    log_printf( &logger, " Set GAP Mode : %s\r\n\n", ( char * )
                        ( BT_OK == bt_set_gap_mode ( &bt, BT_GAP_MODE_CONNECTABLE, 
                                                          BT_GAP_MODE_DISCOVERABLE, 
                                                          BT_GAP_MODE_NOT_LIMITED ) ? "OK" : "FAIL" ) );
    
    log_printf( &logger, " RFCOMM Start Server : %s\r\n\n", ( char * )
                        ( BT_OK == bt_rfcomm_start_server ( &bt, BT_RFCOMM_SERVER_DEF_SDP_ID, 
                                                                 BT_RFCOMM_SERVER_DEF_STREAM_DEST ) ? "OK" : "FAIL" ) );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Handles most of the events required for this example, the packages of events not 
> supported in this example will be just displayed on the USB UART.
> The event handler will display all messages sent from the remote device on the USB UART and 
> send back the predefined response message "DONE".
> There are two specific commands which can be sent from the remote device:
> "led blink" - calls bt_led_blink function for a 5 seconds time period.
> "check buttons" - calls bt_check_buttons function.

```c
void application_task ( void )
{
    bt_event_handler( &bt );
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
