
---
# LED Driver 9 Click

> [LED Driver 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4595) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4595&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This app demonstrates the configuration and control of the LED Driver 9 Click board resulting in a nice breathing effect.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver9

### Example Key Functions

- `leddriver9_cfg_setup` Config Object Initialization function.
```c
void leddriver9_cfg_setup ( leddriver9_cfg_t *cfg );
```

- `leddriver9_init` Initialization function.
```c
err_t leddriver9_init ( leddriver9_t *ctx, leddriver9_cfg_t *cfg );
```

- `leddriver9_default_cfg` Click Default Configuration function.
```c
void leddriver9_default_cfg ( leddriver9_t *ctx );
```

- `leddriver9_ledout_state` This function configures the LEDOUTx registers from the defined config structure.
```c
err_t leddriver9_ledout_state ( leddriver9_t *ctx, leddriver9_output_state_t *output_state );
```

- `leddriver9_set_pwm` This function sets the PWM duty cycle on selected ledout channel.
```c
err_t leddriver9_set_pwm ( leddriver9_t *ctx, leddriver9_channel_sel_t ch_out, float duty_cycle );
```

- `leddriver9_set_dimmer_pwm` This function sets the group PWM duty cycle ( GRPPWM ) which can be used for dimming already set PWM channels.
```c
err_t leddriver9_set_dimmer_pwm ( leddriver9_t *ctx, float duty_cycle );
```

### Application Init

> The initialization configures the UART LOG and I2C drivers and adjusts the Led Driver 9 Click general register settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    leddriver9_cfg_t leddriver9_cfg;  /**< Click config object. */

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

    leddriver9_cfg_setup( &leddriver9_cfg );
    LEDDRIVER9_MAP_MIKROBUS( leddriver9_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver9_init( &leddriver9, &leddriver9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver9_default_cfg( &leddriver9 );
    log_info( &logger, " Application Task " );
    
    mode1_register_settings( );
    mode2_register_settings( );
    Delay_ms ( 100 );
    
    led_output_state( );
    Delay_ms ( 100 );
}
```

### Application Task

> The application task is a simple breathing effect on all LED out channels.

```c
void application_task ( void ) 
{
    float duty_cnt = min_duty;
    
    while ( duty_cnt <= max_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt += duty_gradient;
        Delay_ms ( breathing_speed );
    }
    while ( duty_cnt > min_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt -= duty_gradient;
        Delay_ms ( breathing_speed );
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
