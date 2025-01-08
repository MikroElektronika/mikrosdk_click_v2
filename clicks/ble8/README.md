
---
# BLE 8 Click

> [BLE 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3674) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3674&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from BLE 8 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble8

### Example Key Functions

- `ble8_cfg_setup` Config Object Initialization function. 
```c
void ble8_cfg_setup ( ble8_cfg_t *cfg );
``` 
 
- `ble8_init` Initialization function. 
```c
err_t ble8_init ( ble8_t *ctx, ble8_cfg_t *cfg );
```

- `ble8_reset` This function allows user to reset a module. 
```c
void ble8_reset ( ble8_t *ctx );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ble8_cfg_t cfg;

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

    ble8_cfg_setup( &cfg );
    BLE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble8_init( &ble8, &cfg );

    ble8_reset( &ble8 );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    ble8_set_dsr_pin( &ble8, 1 );
    Delay_ms ( 20 );

    do {
        ble8_set_echo_cmd( &ble8, 1 );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_set_local_name_cmd( &ble8, "BLE 8 Click" );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_connectability_en_cmd( &ble8, BLE8_GAP_CONNECTABLE_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_discoverability_en_cmd( &ble8, BLE8_GAP_GENERAL_DISCOVERABLE_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_enter_mode_cmd( &ble8, BLE8_DATA_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    ble8_set_dsr_pin( &ble8, 0 );
    Delay_ms ( 20 );
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
    ble8_process( );
}
```

### Note

> <pre>
> The all possible commands, module configuration and specification can be found in the 
> related documents:
>     [1] ANNA-B112 System Integration Manual, document number UBX-18009821 
>     [2] u-blox Short Range AT Commands Manual, document number UBX-14044127 
>     [3] ANNA-B112 Getting Started Guide, document number UBX-18020387 
>     [4] ANNA-B112 Declaration of Conformity, document number UBX-18058993
> </pre>

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
