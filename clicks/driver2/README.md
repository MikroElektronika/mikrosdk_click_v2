
---
# Driver 2 Click

> [Driver 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4352) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4352&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Driver 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Driver2

### Example Key Functions

- `driver2_cfg_setup` Config Object Initialization function.
```c
void driver2_cfg_setup ( driver2_cfg_t *cfg );
```

- `driver2_init` Initialization function.
```c
err_t driver2_init ( driver2_t *ctx, driver2_cfg_t *cfg );
```

- `driver2_default_cfg` Click Default Configuration function.
```c
err_t driver2_default_cfg ( driver2_t *ctx );
```

- `driver2_set_sd_pin` Set SD pin.
```c
void driver2_set_sd_pin ( driver2_t *ctx, uint8_t state );
```

- `driver2_set_pwm_pin` Set PWM pin.
```c
void driver2_set_pwm_pin ( driver2_t *ctx, uint8_t state );
```

- `driver2_get_fb_pin` Get FB pin
```c
uint8_t driver2_get_fb_pin ( driver2_t *ctx );
```

### Application Init

> Initializes driver module and sets PWM.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    driver2_cfg_t driver2_cfg;  /**< Click config object. */

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

    driver2_cfg_setup( &driver2_cfg );
    DRIVER2_MAP_MIKROBUS( driver2_cfg, MIKROBUS_1 );
    err_t init_flag  = driver2_init( &driver2, &driver2_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    driver2_default_cfg ( &driver2 );

    driver2_set_duty_cycle ( &driver2, 0.0 );
    driver2_pwm_start( &driver2 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Start motor example with change in motor speed using changes in PWM duty cycle.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    driver2_set_duty_cycle ( &driver2, duty );
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
