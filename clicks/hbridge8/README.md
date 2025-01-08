
---
# H-Bridge 8 Click

> [H-Bridge 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4775) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4775&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This library contains an API for the H-Bridge 8 Click driver.
> This demo application shows the use of a H-Bridge 8 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge8

### Example Key Functions

- `hbridge8_cfg_setup` Config Object Initialization function.
```c
void hbridge8_cfg_setup ( hbridge8_cfg_t *cfg );
```

- `hbridge8_init` Initialization function.
```c
err_t hbridge8_init ( hbridge8_t *ctx, hbridge8_cfg_t *cfg );
```

- `hbridge8_default_cfg` Click Default Configuration function.
```c
void hbridge8_default_cfg ( hbridge8_t *ctx );
```

- `hbridge8_set_mode` H-Bridge 8 set operating mode function.
```c
err_t hbridge8_set_mode ( hbridge8_t *ctx, uint8_t mode );
```

- `hbridge8_enable` H-Bridge 8 set IC enable function.
```c
err_t hbridge8_enable ( hbridge8_t *ctx );
```

- `hbridge8_set_duty_cycle` H-Bridge 8 sets PWM duty cycle.
```c
err_t hbridge8_set_duty_cycle ( hbridge8_t *ctx, float duty_cycle );
```

### Application Init

> Initialization of PWM module and log UART.
> After driver initialization, the app set duty cycle, start PWM and
> set motor drive the forward.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge8_cfg_t hbridge8_cfg;  /**< Click config object. */

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

    hbridge8_cfg_setup( &hbridge8_cfg );
    HBRIDGE8_MAP_MIKROBUS( hbridge8_cfg, MIKROBUS_1 );
    err_t init_flag  = hbridge8_init( &hbridge8, &hbridge8_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hbridge8_default_cfg ( &hbridge8 );
    Delay_ms ( 100 );
   
    hbridge8_set_mode( &hbridge8, HBRIDGE8_MODE_FORWARD );
    log_printf( &logger, "\r\n>>> Forward\r\n\r\n" );
    hbridge8_set_duty_cycle ( &hbridge8, 0.1 );
    hbridge8_pwm_start( &hbridge8 );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of an H-Bridge 8 Click board&trade;.
> In this example, the app drives the motor forward/reverse and switched the PWM signal back and forth 
> from 3% duty cycle to 8% duty cycle every 3000 milliseconds and back.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 3;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 100.0;
    
    hbridge8_set_duty_cycle ( &hbridge8, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt ) );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
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
