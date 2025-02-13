
---
# BT122-A Click

> [BT122-A Click](https://www.mikroe.com/?pid_product=MIKROE-6432) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6432&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BT122-A Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BT122A

### Example Key Functions

- `bt122a_cfg_setup` Config Object Initialization function.
```c
void bt122a_cfg_setup ( bt122a_cfg_t *cfg );
```

- `bt122a_init` Initialization function.
```c
err_t bt122a_init ( bt122a_t *ctx, bt122a_cfg_t *cfg );
```

- `bt122a_set_local_name` This function sets the local name of the device.
```c
err_t bt122a_set_local_name ( bt122a_t *ctx, uint8_t *name );
```

- `bt122a_send_package` This function sends a data package to the Click board.
```c
void bt122a_send_package ( bt122a_t *ctx, bt122a_package_t pkg );
```

- `bt122a_read_package` This function waits for the command or event type of message to arrive and then reads the complete message and stores it to the pkg structure.
```c
err_t bt122a_read_package ( bt122a_t *ctx, bt122a_package_t *pkg );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bt122a_cfg_t bt122a_cfg;  /**< Click config object. */

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
    bt122a_cfg_setup( &bt122a_cfg );
    BT122A_MAP_MIKROBUS( bt122a_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bt122a_init( &bt122a, &bt122a_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Set Local Name to \"%s\"\r\n", ( char * ) DEVICE_NAME );
    error_flag = bt122a_set_local_name ( &bt122a, DEVICE_NAME );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Delete Bondings\r\n" );
    error_flag = bt122a_delete_bondings ( &bt122a );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Set Bondable Mode\r\n" );
    error_flag = bt122a_set_bondable_mode ( &bt122a, BT122A_SM_SET_BONDABLE_ALLOWED );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Set GAP Mode\r\n" );
    error_flag = bt122a_set_gap_mode ( &bt122a, BT122A_GAP_MODE_CONNECTABLE, 
                                                BT122A_GAP_MODE_DISCOVERABLE, 
                                                BT122A_GAP_MODE_NOT_LIMITED );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> RFCOMM Start Server\r\n" );
    error_flag = bt122a_rfcomm_start_server ( &bt122a, BT122A_RFCOMM_SERVER_DEF_SDP_ID, 
                                                       BT122A_RFCOMM_SERVER_DEF_STREAM_DEST );
    bt122a_check_response ( error_flag );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Handles most of the events required for this example, the packages of events not supported in this example will just be displayed on the USB UART.
The event handler will display all messages received from the remote device on the USB UART and echo the same message to the connected device.

```c
void application_task ( void )
{
    bt122a_event_handler( &bt122a );
}
```

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
A smartphone and the Click board must be paired in order to exchange messages with each other.

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
