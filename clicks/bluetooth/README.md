
---
# Bluetooth Click

> [Bluetooth Click](https://www.mikroe.com/?pid_product=MIKROE-958) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-958&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from Bluetooth Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Bluetooth

### Example Key Functions

- `bluetooth_cfg_setup` Config Object Initialization function. 
```c
void bluetooth_cfg_setup ( bluetooth_cfg_t *cfg );
``` 
 
- `bluetooth_init` Initialization function. 
```c
err_t bluetooth_init ( bluetooth_t *ctx, bluetooth_cfg_t *cfg );
```

- `bluetooth_enter_command_mode` The function enter the command mode of the RN-41 Bluetooth module on Bluetooth Click board. 
```c
void bluetooth_enter_command_mode ( bluetooth_t *ctx );
```
 
- `bluetooth_set_authentication` The function set the authentication value to the RN-41 Bluetooth module on Bluetooth Click board. 
```c
void bluetooth_set_authentication ( bluetooth_t *ctx, uint8_t auth_value );
```

- `bluetooth_set_security_pin_code` The function set security pin code string to the RN-41 Bluetooth module on Bluetooth Click board. 
```c
err_t bluetooth_set_security_pin_code ( bluetooth_t *ctx, uint8_t *sp_code );
```

### Application Init

> Initializes driver and wake-up module. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    bluetooth_cfg_t cfg;

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

    bluetooth_cfg_setup( &cfg );
    BLUETOOTH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bluetooth_init( &bluetooth, &cfg );

    Delay_ms ( 500 );
   
    log_printf( &logger, "Configuring the module...\n" );
    
    do
    {    
        log_printf( &logger, " --- Command mode --- \r\n" );
        bluetooth_enter_command_mode( &bluetooth );
    }
    while( bluetooth_process( "CMD" ) != 1 );
    
    do
    {
        log_printf( &logger, " --- Device name --- \r\n" );
        bluetooth_set_device_name( &bluetooth, &DEVICE_NAME_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Status string --- \r\n" );
        bluetooth_set_extended_status_string( &bluetooth, &EXTENDED_STRING_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Operating mode --- \r\n" );
        bluetooth_set_operating_mode( &bluetooth, 0 );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Authentication --- \r\n" );
        bluetooth_set_authentication( &bluetooth, 1 );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Pin code --- \r\n" );
        bluetooth_set_security_pin_code( &bluetooth, &PIN_CODE_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Exit command mode --- \r\n" );
        bluetooth_exit_command_mode( &bluetooth );
    }
    while( bluetooth_process( "END" ) != 1 );
    
    log_printf( &logger, "The module has been configured.\n" );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
    bluetooth_process( "AOK" );
}
```

### Note

> Before starting to use this Click, it must be paired with other device.

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
