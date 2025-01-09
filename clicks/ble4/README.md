
---
# BLE 4  Click

> [BLE 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3773) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3773&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from BLE 4 Clicks. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE4

### Example Key Functions

- `ble4_cfg_setup` Config Object Initialization function. 
```c
void ble4_cfg_setup ( ble4_cfg_t *cfg );
``` 
 
- `ble4_init` Initialization function. 
```c
err_t ble4_init ( ble4_t *ctx, ble4_cfg_t *cfg );
```

- `ble4_reset` This function allows user to reset a module. 
```c
void ble4_reset ( ble4_t *ctx );
```

### Application Init

> Initializes driver and wake-up module. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ble4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble4_cfg_setup( &cfg );
    BLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble4_init( &ble4, &cfg );

    ble4_reset( &ble4 );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    ble4_set_dsr_pin( &ble4, 1 );
    Delay_ms ( 20 );

    do {
        ble4_set_echo_cmd( &ble4, 1 );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_set_local_name_cmd( &ble4, "BLE 4 Click" );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_connectability_en_cmd( &ble4, BLE4_GAP_CONNECTABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_discoverability_en_cmd( &ble4, BLE4_GAP_GENERAL_DISCOVERABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_enter_mode_cmd( &ble4, BLE4_DATA_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    ble4_set_dsr_pin( &ble4, 0 );
    Delay_ms ( 20 );
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
```

### Application Task

> Reads the received data and parses it. 

```c
void application_task ( void )
{
    ble4_process( );
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
