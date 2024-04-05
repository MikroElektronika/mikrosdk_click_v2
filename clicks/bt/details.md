
---
# BT click

BT Click is a compact add-on board targeted for applications that require both Bluetooth Smart and Classic connectivity. This board features the BT121, a dual-mode Bluetooth Smart Ready module solution that gives unparalleled flexibility to integrate both Bluetooth Smart and Bluetooth Basic Rate/Enhanced Data Rate (BR/EDR) wireless technologies from Silicon Labs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bt_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bt-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BT Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BT Click driver.

#### Standard key functions :

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

#### Example key functions :

- `bt_set_local_name` This function sets the local name of the device.
```c
err_t bt_set_local_name ( bt_t *ctx, char *name );
```

- `bt_send_package` This function sends a data package to the click board.
```c
err_t bt_send_package ( bt_t *ctx, bt_package_t pkg );
```

- `bt_read_package` This function waits for the command or event type of message to arrive and then reads the complete message and stores it to pkg structure.
```c
err_t bt_read_package ( bt_t *ctx, bt_package_t *pkg );
```

## Example Description

> This example demonstrates the use of BT click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board.

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
                        ( BT_OK == bt_set_local_name ( &bt, "MikroE - BT click" ) ? "OK" : "FAIL" ) );
    
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

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the click board must be paired in order to exchange messages with each other.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BT

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
