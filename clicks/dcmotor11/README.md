
---
# DC Motor 11 Click

> [DC Motor 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3649) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3649&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is motor driver with the current limiting and current sensing.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor11

### Example Key Functions

- `dcmotor11_cfg_setup` Config Object Initialization function. 
```c
void dcmotor11_cfg_setup ( dcmotor11_cfg_t *cfg );
``` 
 
- `dcmotor11_init` Initialization function. 
```c
err_t dcmotor11_init ( dcmotor11_t *ctx, dcmotor11_cfg_t *cfg );
```

- `dcmotor11_control` Motor Control. 
```c
void dcmotor11_control( dcmotor11_t *ctx, uint8_t dir, uint8_t speed );
```
 
- `dcmotor11_get_fault` Get Fault. 
```c
uint8_t dcmotor11_get_fault( dcmotor11_t *ctx );
```

- `dcmotor11_get_interrupt_state` Interrupt state on the INT pin. 
```c
uint8_t dcmotor11_get_interrupt_state( dcmotor11_t *ctx );
```

### Application Init

> Initialization driver init and sets first motor settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor11_cfg_t cfg;

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

    dcmotor11_cfg_setup( &cfg );
    DCMOTOR11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor11_init( &dcmotor11, &cfg );

   dcmotor11_get_fault( &dcmotor11 );
    
    /* Start settings */
    motor_dir = DCMOTOR11_DIRECTION_FORWARD;
    motor_speed = DCMOTOR11_VSET_480mV;
    dcmotor11_control( &dcmotor11, DCMOTOR11_DIRECTION_FORWARD, motor_speed );
}
```

### Application Task

> Waits for valid user input and executes functions based on set of valid commands.

```c
void application_task ( void )
{
    /* Speed increase */
    motor_speed += 4;
    if ( motor_speed >= DCMOTOR11_VSET_4820mV )
    {
        log_printf( &logger, "---- MAX SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_4820mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger, "---- Speed increase ---- \r\n" );
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    /* Speed decrease */
    motor_speed -= 4;
    if ( motor_speed < DCMOTOR11_VSET_480mV )
    {
        log_printf( &logger, "---- MIN SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_480mV;
    }
    else
    {
        log_printf( &logger, "---- Speed decrease ---- \r\n");
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    /* Stop / Start */
    if( f_motor_state == 1 )
    {
        log_printf( &logger,"---- Stop Motor!!! ---- \r\n" );
        f_motor_state = 0;
        dcmotor11_stop( &dcmotor11 );
    }
    else
    {
        log_printf( &logger,"---- Start Motor ---- \r\n" );
        f_motor_state = 1;
        motor_speed = DCMOTOR11_VSET_480mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    /* Direction - Forward / Backword */
    if ( motor_dir == 2 )
    {
        log_printf( &logger,"---- Direction - [FORWARD] ---- \r\n" );
        motor_dir = 1;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger,"---- Direction - [BACKWARD] ---- \r\n" );
        motor_dir = 2;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
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
