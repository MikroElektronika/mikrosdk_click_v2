
---
# Brushless Click

> [Brushless Click](https://www.mikroe.com/?pid_product=MIKROE-2441) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2441&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This example showcases how to initialize and use the Brushless Click. 
>  The Click has a brushless motor driver which controls the work 
>  of the motor through the BLDC terminal. 
>  In order for this example to work a motor and a power supply are needed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless

### Example Key Functions

- `brushless_cfg_setup` Config Object Initialization function. 
```c
void brushless_cfg_setup ( brushless_cfg_t *cfg );
``` 
 
- `brushless_init` Initialization function. 
```c
err_t brushless_init ( brushless_t *ctx, brushless_cfg_t *cfg );
```

- `brushless_default_cfg` Click Default Configuration function. 
```c
void brushless_default_cfg ( brushless_t *ctx );
```

- `brushless_spin_clockwise` This function sets the spin direction of the motor to clockwise. 
```c
void brushless_spin_clockwise ( brushless_t *ctx );
```
 
- `brushless_spin_counter_clockwise` This function sets the spin direction of the motor to counter clockwise. 
```c
void brushless_spin_counter_clockwise ( brushless_t *ctx );
```

- `brushless_read_rotation_speed_sensor_output` This function reads the digital input of the INT pin. 
```c
uint8_t brushless_read_rotation_speed_sensor_output ( brushless_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    brushless_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.
    brushless_cfg_setup( &cfg );
    BRUSHLESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms ( 100 );
    
    brushless_init( &brushless, &cfg );
    brushless_pwm_start( &brushless );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

>  This is an example that demonstrates the use of a Brushless Click board.
>  Brushless Click communicates with the register via the PWM interface.
>  It shows moving in the left direction from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( brushless_direction == 1 )
    {
        brushless_spin_clockwise ( &brushless );
        log_printf( &logger, "<<<< " );
    }
    else
    {
        brushless_spin_counter_clockwise ( &brushless );
        log_printf( &logger, ">>>> " );
    }

    brushless_set_duty_cycle ( &brushless, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
                
        if ( brushless_direction == 1 )
        {
            brushless_direction = 0;
        }
        else if ( brushless_direction == 0 )
        {
            brushless_direction = 1;
        }
    }
    duty_cnt += duty_inc;
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
