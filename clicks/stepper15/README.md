
---
# Stepper 15 Click

> [Stepper 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4639) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4639&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for the Stepper 15 Click driver.
> The library contains drivers for work control of the Stepper Motor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper15

### Example Key Functions

- `stepper15_cfg_setup` Config Object Initialization function.
```c
void stepper15_cfg_setup ( stepper15_cfg_t *cfg );
```

- `stepper15_init` Initialization function.
```c
err_t stepper15_init ( stepper15_t *ctx, stepper15_cfg_t *cfg );
```

- `stepper15_default_cfg` Click Default Configuration function.
```c
void stepper15_default_cfg ( stepper15_t *ctx );
```

- `stepper15_make_one_step` Stepper 15 make one step function.
```c
err_t stepper15_make_one_step ( stepper15_t *ctx, uint8_t step_speed );
```

- `stepper15_set_direction` Stepper 15 set direction function.
```c
err_t stepper15_set_direction ( stepper15_t *ctx, uint8_t direction );
```

- `stepper15_step_by_angle` Stepper 15 step by angle function.
```c
err_t stepper15_step_by_angle ( stepper15_t *ctx, uint8_t step_speed, float angle, uint16_t step_360 );
```

### Application Init

> Initializes I2C and SPI driver and set default configuration,
> enable the device and enable outputs mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    stepper15_cfg_t stepper15_cfg;  /**< Click config object. */

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

    stepper15_cfg_setup( &stepper15_cfg );
    STEPPER15_MAP_MIKROBUS( stepper15_cfg, MIKROBUS_1 );
    err_t init_flag  = stepper15_init( &stepper15, &stepper15_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    stepper15_default_cfg ( &stepper15 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------------\r\n" );
    
    stepper15_set_work_mode( &stepper15, STEPPER15_WORK_MODE_ENABLE_DEVICE );
    Delay_ms ( 100 );
    stepper15_set_output_mode( &stepper15, STEPPER15_OUTPUT_MODE_OUTPUTS_ENABLE );
    Delay_ms ( 100 );
    
    if ( stepper15_get_fault_condition( &stepper15 ) == STEPPER15_FAULT_CONDITION ) {
        log_printf( &logger, "         Fault condition         \r\n" );   
    } else {
        log_printf( &logger, "        Correct condition        \r\n" );
    }
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "      Stop the stepper motor     \r\n" );
    stepper15_motor_stop( &stepper15 );
    Delay_ms ( 1000 );
}
```

### Application Task

> The application task represents an example that demonstrates 
> the use of the Stepper 15 Click board&trade; 
> with which the user can sequentially move the motor. 
> The first part of the sequence executes the clockwise/counterclockwise motor movement
> for an angle of 90-degrees with a step speed of 85/100%, 
> all the way to the last sequence of the same movement routine of 360-degree angle
> with a step speed of 85/100%. 
> Results are sent to the USART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees \r\n" );
    log_printf( &logger, " Step speed        :  85 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 15, 90, step_360 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "     Counterclockwise motion     \r\n" );
    log_printf( &logger, " Angle of rotation : 180 degrees \r\n" );
    log_printf( &logger, " Step speed        :  85 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_COUNTERCLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 15, 180, step_360 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation : 270 degrees \r\n" );
    log_printf( &logger, " Step speed        :  90 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 10, 270, step_360 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "     Counterclockwise motion     \r\n" );
    log_printf( &logger, " Angle of rotation : 360 degrees \r\n" );
    log_printf( &logger, " Step speed        : 100 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_COUNTERCLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed, 360, step_360 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation : 360 degrees \r\n" );
    log_printf( &logger, " Step speed        : 100 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed, 360, step_360 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
