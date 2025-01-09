
---
# Vibro Motor Click

> [Vibro Motor Click](https://www.mikroe.com/?pid_product=MIKROE-2826) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2826&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This application contorl the speed of vibro motor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VibroMotor

### Example Key Functions

- `vibromotor_cfg_setup` Config Object Initialization function.
```c
void vibromotor_cfg_setup ( vibromotor_cfg_t *cfg );
```

- `vibromotor_init` Initialization function.
```c
err_t vibromotor_init ( vibromotor_t *ctx, vibromotor_cfg_t *cfg );
```

- `vibromotor_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t vibromotor_set_duty_cycle ( vibromotor_t *ctx, float duty_cycle );
```

- `vibromotor_pwm_stop` This function stops the PWM moudle output.
```c
err_t vibromotor_pwm_stop ( vibromotor_t *ctx );
```

- `vibromotor_pwm_start` This function starts the PWM moudle output.
```c
err_t vibromotor_pwm_start ( vibromotor_t *ctx );
```

### Application Init

> Configures PWM to 5kHz frequency, calculates maximum duty ratio and starts PWM with duty ratio value 0.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor_cfg_t vibromotor_cfg;  /**< Click config object. */

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

    vibromotor_cfg_setup( &vibromotor_cfg );
    VIBROMOTOR_MAP_MIKROBUS( vibromotor_cfg, MIKROBUS_1 );
    err_t init_flag  = vibromotor_init( &vibromotor, &vibromotor_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor_set_duty_cycle ( &vibromotor, 0.0 );
    vibromotor_pwm_start( &vibromotor );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Allows user to enter desired command to control Vibro Motor Click board.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor_set_duty_cycle ( &vibromotor, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
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
