
---
# RN4678 Click

> [RN4678 Click](https://www.mikroe.com/?pid_product=MIKROE-2545) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2545&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RN4678 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4678

### Example Key Functions

- `rn4678_cfg_setup` Config Object Initialization function. 
```c
void rn4678_cfg_setup ( rn4678_cfg_t *cfg );
``` 
 
- `rn4678_init` Initialization function. 
```c
err_t rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg );
```

- `rn4678_enable` Enable device function. 
```c
void rn4678_enable ( rn4678_t *ctx );
```

- `rn4678_enter_command_mode` Enter the command mode function. 
```c
void rn4678_enter_command_mode ( rn4678_t *ctx );
```
 
- `rn4678_exit_command_mode` Exit the command mode function. 
```c
void rn4678_exit_command_mode ( rn4678_t *ctx );
```

- `rn4678_set_device_name` Set the device name function. 
```c
void rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4678_cfg_t cfg;

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

    rn4678_cfg_setup( &cfg );
    RN4678_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4678_init( &rn4678, &cfg );

    rn4678_enable ( &rn4678 );
    Delay_ms ( 1000 );
    rn4678_hw_reset ( &rn4678 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Configuring the module...\n" );
    
    do
    {    
        log_printf( &logger, " --- Command mode --- \r\n" );
        rn4678_enter_command_mode( &rn4678 );
    }
    while( rn4678_process( "CMD" ) != 1 );
    
    do
    {
        log_printf( &logger, " --- Device name --- \r\n" );
        rn4678_set_device_name( &rn4678, &DEVICE_NAME_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Status string --- \r\n" );
        rn4678_set_extended_status_string( &rn4678, &EXTENDED_STRING_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Operating mode --- \r\n" );
        rn4678_set_operating_mode( &rn4678, 0 );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Authentication --- \r\n" );
        rn4678_set_authentication( &rn4678, 1 );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Pin code --- \r\n" );
        rn4678_set_security_pin_code( &rn4678, &PIN_CODE_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Exit command mode --- \r\n" );
        rn4678_exit_command_mode( &rn4678 );
    }
    while( rn4678_process( "END" ) != 1 );
    
    log_printf( &logger, "The module has been configured.\n" );
    
    rn4678_set_cts_pin( &rn4678, 0 );
}
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c
void application_task ( void )
{
    rn4678_process( PROCESS_LOG_RSP );
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
