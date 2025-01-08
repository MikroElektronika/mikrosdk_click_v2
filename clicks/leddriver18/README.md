
---
# LED Driver 18 Click

> [LED Driver 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5560) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5560&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for LED Driver 18 Click driver. 
The library initializes and defines the I2C bus drivers to 
write and read data for setting constant current output, 
as well as the default configuration for a PWM output value 
of the OUT pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver18

### Example Key Functions

- `leddriver18_cfg_setup` Config Object Initialization function.
```c
void leddriver18_cfg_setup ( leddriver18_cfg_t *cfg );
```

- `leddriver18_init` Initialization function.
```c
err_t leddriver18_init ( leddriver18_t *ctx, leddriver18_cfg_t *cfg );
```

- `leddriver18_default_cfg` Click Default Configuration function.
```c
err_t leddriver18_default_cfg ( leddriver18_t *ctx );
```

- `leddriver18_set_output_pwm` LED Driver 18 set output channel PWM value function.
```c
err_t leddriver18_set_output_pwm ( uint8_t out_num, float pwm_val );
```

- `leddriver18_write_config` LED Driver 18 write config function.
```c
void leddriver18_write_config ( leddriver18_t *ctx );
```

- `leddriver18_set_cc_output` LED Driver 18 set constant current output function.
```c
err_t leddriver18_set_cc_output ( leddriver18_t *ctx, uint8_t current_limit );
```

### Application Init

> Initializes the driver and performs default configuration and sets 
the device in output enabled mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver18_cfg_t leddriver18_cfg;  /**< Click config object. */

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
    leddriver18_cfg_setup( &leddriver18_cfg );
    LEDDRIVER18_MAP_MIKROBUS( leddriver18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver18_init( &leddriver18, &leddriver18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER18_ERROR == leddriver18_default_cfg ( &leddriver18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the LED Driver 18 Click board by 
changing PWM values for all output from a minimum value to 
maximum value and back to minimum controlling the brightness of the 
LEDs in the process.

```c
void application_task ( void ) 
{
    float pwm_val;

    for ( int8_t  n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms ( 200 );
    }
    for ( int8_t  n_cnt = 100; n_cnt >= 10; n_cnt -= 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms ( 200 );
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
