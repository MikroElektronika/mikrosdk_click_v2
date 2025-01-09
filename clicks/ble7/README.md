
---
# BLE 7 Click

> [BLE 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3872) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3872&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from BLE 7 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble7

### Example Key Functions

- `ble7_cfg_setup` Config Object Initialization function. 
```c
void ble7_cfg_setup ( ble7_cfg_t *cfg );
``` 
 
- `ble7_init` Initialization function. 
```c
err_t ble7_init ( ble7_t *ctx, ble7_cfg_t *cfg );
```

- `ble7_reset` This function allows user to reset BGX module. 
```c
void ble7_reset ( ble7_t *ctx );
```

- `ble7_send_command` This function allows user to transmit data to the BGX module. 
```c
void ble7_send_command ( ble7_t *ctx, char *command );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ble7_cfg_t cfg;

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

    ble7_cfg_setup( &cfg );
    BLE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble7_init( &ble7, &cfg );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_1sec( );
    config_mode = 1;
    
    do 
    {
        ble7_reset( &ble7 );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_CLEAR_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_ECHO );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_PAIRING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_DEVICE_NAME );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_ON );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_HIGH_DURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SAVE_CONFIGURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SWITCH_TO_STREAM_MODE );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c
void application_task ( void )
{
    ble7_process(  );
}
```

### Note

> We have used the BLE Scanner smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages with each other.
> For more information about the BGX module commands, please refer to the following link:
> https://docs.silabs.com/gecko-os/1/bgx/latest/commands

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
