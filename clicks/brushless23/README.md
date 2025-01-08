
---
# Brushless 23 Click

> [Brushless 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5100) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5100&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 23 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless23

### Example Key Functions

- `brushless23_cfg_setup` Config Object Initialization function.
```c
void brushless23_cfg_setup ( brushless23_cfg_t *cfg );
```

- `brushless23_init` Initialization function.
```c
err_t brushless23_init ( brushless23_t *ctx, brushless23_cfg_t *cfg );
```

- `brushless23_default_cfg` Click Default Configuration function.
```c
err_t brushless23_default_cfg ( brushless23_t *ctx );
```

- `brushless23_pwm_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless23_pwm_set_duty_cycle ( brushless23_t *ctx, float duty_cycle );
```

- `brushless23_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless23_switch_direction ( brushless23_t *ctx );
```

- `brushless23_get_motor_speed` This function reads the motor speed in Hz.
```c
err_t brushless23_get_motor_speed ( brushless23_t *ctx, float *motor_speed_hz );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless23_cfg_t brushless23_cfg;  /**< Click config object. */

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
    brushless23_cfg_setup( &brushless23_cfg );
    BRUSHLESS23_MAP_MIKROBUS( brushless23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless23_init( &brushless23, &brushless23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS23_ERROR == brushless23_default_cfg ( &brushless23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 2 seconds.
The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    brushless23_pwm_set_duty_cycle ( &brushless23, duty );
    log_printf( &logger, "\r\n Duty cycle: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
    float motor_speed_hz = 0;
    if ( BRUSHLESS23_OK == brushless23_get_motor_speed ( &brushless23, &motor_speed_hz ) )
    {
        log_printf( &logger, " Speed: %.1f Hz\r\n", motor_speed_hz );
    }
    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {
        duty_cnt = 7;
        duty_inc = -1;
    }
    else if ( duty_cnt < 2 ) 
    {
        duty_cnt = 2;
        duty_inc = 1;
        log_printf( &logger, "\r\n Switch direction\r\n" );
        brushless23_pwm_set_duty_cycle ( &brushless23, BRUSHLESS23_DUTY_CYCLE_MIN_PCT );
        Delay_ms ( 500 );
        brushless23_switch_direction ( &brushless23 );
    }
    Delay_ms ( 500 );
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
