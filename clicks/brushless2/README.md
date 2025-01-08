
---
# Brushless 2 Click

> [Brushless 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2754) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2754&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola peric
- **Date**          : Mar 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This application controlled speed motor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless2

### Example Key Functions

- `brushless2_cfg_setup` Config Object Initialization function. 
```c
void brushless2_cfg_setup ( brushless2_cfg_t *cfg );
``` 
 
- `brushless2_init` Initialization function. 
```c
err_t brushless2_init ( brushless2_t *ctx, brushless2_cfg_t *cfg );
```

- `brushless2_counter_clockwise` Set the direction of rotation in the counterclockwise direction function. 
```c
void brushless2_counter_clockwise( brushless2_t *ctx );
```
 
- `brushless2_clockwise` Set the direction of rotation in the clockwise direction function. 
```c
void brushless2_clockwise( brushless2_t *ctx );
```

- `brushless2_get_interrupt_status` Get Interrupt pin state function. 
```c
uint8_t brushless2_get_interrupt_status( brushless2_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO, PWM initialization

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless2_cfg_t cfg;

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

    brushless2_cfg_setup( &cfg );
    BRUSHLESS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless2_init( &brushless2, &cfg );
    
    log_printf( &logger, "---------------------- \r\n" );
    
    brushless2_set_duty_cycle ( &brushless2, 0.0 );
    brushless2_pwm_start ( &brushless2 );
    Delay_ms ( 500 );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

>  This is a example which demonstrates the use of Brushless 2 Click board.
>  Brushless 2 Click communicates with register via PWM interface.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless2_set_duty_cycle ( &brushless2, duty );
    brushless2_clockwise ( &brushless2 );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
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
