
---
# Brushless 7 Click

> [Brushless 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4182) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4182&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Brushless 7 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless7

### Example Key Functions

- `brushless7_cfg_setup` Config Object Initialization function. 
```c
void brushless7_cfg_setup ( brushless7_cfg_t *cfg );
``` 
 
- `brushless7_init` Initialization function. 
```c
err_t brushless7_init ( brushless7_t *ctx, brushless7_cfg_t *cfg );
```

- `brushless7_default_cfg` Click Default Configuration function. 
```c
void brushless7_default_cfg ( brushless7_t *ctx );
```

- `brushless7_change_duty` Function for changeing duty of device. 
```c
uint8_t brushless7_change_duty( brushless7_t *ctx, float duty_ptc );
```
 
- `brushless7_max_speed_rpm` Function for setting max rpm parameter of device. 
```c
uint8_t brushless7_max_speed_rpm( brushless7_t *ctx, uint8_t max_speed_rpm );
```

- `brushless7_control_mode_set` Function for setting type of device control. 
```c
uint8_t brushless7_control_mode_set( brushless7_t *ctx, uint8_t ctrl_type );
```

### Application Init

> Sets the default configuration and then configures the Click board for the selected mode. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless7_cfg_t cfg;
    uint8_t error_flag = 0;

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

    brushless7_cfg_setup( &cfg );
    BRUSHLESS7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless7_init( &brushless7, &cfg );
    Delay_ms ( 100 );

    brushless7_default_cfg( &brushless7 );
    Delay_ms ( 100 );
    
    demo_type_data = BRUSHLESS7_CTRL_TYPE_DUTY;

    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        error_flag |= brushless7_max_duty( &brushless7, 95.0 );
        error_flag |= brushless7_start_duty( &brushless7, 5.0 );
        error_flag |= brushless7_stop_duty( &brushless7, 2.0 );
        log_printf( &logger, " ----- DUTY CONTROL ----- \r\n" );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        error_flag |= brushless7_max_speed_rpm( &brushless7, BRUSHLESS7_MAX_SPEED_4096 );
        log_printf( &logger, " ----- RPM CONTROL ----- \r\n" );
    }
    
    if ( BRUSHLESS7_DEV_ERROR == error_flag )
    {
        log_printf( &logger, " ----- ERROR ----- \r\n" );
        for( ; ; );
    }
}
```

### Application Task

> Increases and decreases the speed of the motor rotation by setting the duty cycle or 
> rpm values depending on which mode is previously selected. 
> It also switches the direction of rotation at the beginning of each cycle. 
> All data is being logged on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    brushless7_control_mode_set( &brushless7, BRUSHLESS7_CTRL_TYPE_STOP );
    brushless7_toggle_dir_pin_state ( &brushless7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    brushless7_control_mode_set( &brushless7, demo_type_data );
    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        log_printf( &logger, " The motor is accelerating...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_change_duty( &brushless7, 70.0 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        log_printf( &logger, " The motor is slowing down...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_change_duty( &brushless7, 8.0 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        log_printf( &logger, " The motor is accelerating...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_start_rpm( &brushless7, 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
       
        log_printf( &logger, " The motor is slowing down...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_start_rpm( &brushless7, 100 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
