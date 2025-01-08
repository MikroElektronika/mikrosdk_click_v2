
---
# DC Motor 27 Click

> [DC Motor 27 Click](https://www.mikroe.com/?pid_product=MIKROE-5806) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5806&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the DC Motor 27 Click board by driving 
  the motor at different speeds, enabling brake and coast modes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor27

### Example Key Functions

- `dcmotor27_cfg_setup` Config Object Initialization function.
```c
void dcmotor27_cfg_setup ( dcmotor27_cfg_t *cfg );
```

- `dcmotor27_init` Initialization function.
```c
err_t dcmotor27_init ( dcmotor27_t *ctx, dcmotor27_cfg_t *cfg );
```

- `dcmotor27_default_cfg` Click Default Configuration function.
```c
err_t dcmotor27_default_cfg ( dcmotor27_t *ctx );
```

- `dcmotor27_set_duty_cycle` DC Motor 27 sets PWM duty cycle.
```c
err_t dcmotor27_set_duty_cycle ( dcmotor27_t *ctx, float duty_cycle );
```

- `dcmotor27_get_flt_pin` DC Motor 27 get flt pin state.
```c
uint8_t dcmotor27_get_flt_pin ( dcmotor27_t *ctx );
```

- `dcmotor27_set_coast` DC Motor 27 set coast mode funtion.
```c
void dcmotor27_set_coast ( dcmotor27_t *ctx, uint8_t coast_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor27_cfg_t dcmotor27_cfg;  /**< Click config object. */

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
    dcmotor27_cfg_setup( &dcmotor27_cfg );
    DCMOTOR27_MAP_MIKROBUS( dcmotor27_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == dcmotor27_init( &dcmotor27, &dcmotor27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    if ( DCMOTOR27_ERROR == dcmotor27_default_cfg ( &dcmotor27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every second, 
  places the motor into coast or braking mode.

```c
void application_task ( void ) 
{
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor coasting \r\n" );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_OFF );
    
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    dcmotor27_pwm_stop( &dcmotor27 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor27_pwm_start( &dcmotor27 );
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
