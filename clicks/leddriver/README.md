
---
# LED DRIVER Click

> [LED DRIVER Click](https://www.mikroe.com/?pid_product=MIKROE-2676) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2676&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains API for the LED Driver Click driver.
>  This application controls the brightness. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver

### Example Key Functions

- `leddriver_cfg_setup` Config Object Initialization function. 
```c
void leddriver_cfg_setup ( leddriver_cfg_t *cfg );
``` 
 
- `leddriver_init` Initialization function. 
```c
err_t leddriver_init ( leddriver_t *ctx, leddriver_cfg_t *cfg );
```

### Application Init

> PWM initialization set PWM duty cycle and PWM frequency and start PWM.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver_cfg_t cfg;

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

    leddriver_cfg_setup( &cfg );
    LEDDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( LEDDRIVER_OK != leddriver_init( &leddriver, &cfg ) )
    {
        log_info( &logger, "---- Init Error ----" );
        log_info( &logger, "---- Run program again ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Init Done ----\r\n" );
    leddriver_set_duty_cycle ( &leddriver, 0.0 );
    leddriver_pwm_start( &leddriver );
    Delay_ms ( 100 );
    log_info( &logger, "---- Application Task ----\r\n" );
}
```

### Application Task

> This is an example that demonstrates the use of the LED Driver Click board.
> LED Driver Click communicates with register via PWM interface.
> This example shows the automatic control halogen bulb light intensity,
> the first intensity of light is rising and then the intensity of light is falling.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver_set_duty_cycle ( &leddriver, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 100 );
    
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
