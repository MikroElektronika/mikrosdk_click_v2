
---
# Fan 9 Click

> [Fan 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6103) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6103&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of FAN 9 Click board, by changing speed of the fan from 0 to 100 percent, then decreasing it back to 0.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan9

### Example Key Functions

- `fan9_cfg_setup` Config Object Initialization function.
```c
void fan9_cfg_setup ( fan9_cfg_t *cfg );
```

- `fan9_init` Initialization function.
```c
err_t fan9_init ( fan9_t *ctx, fan9_cfg_t *cfg );
```

- `fan9_default_cfg` Click Default Configuration function.
```c
err_t fan9_default_cfg ( fan9_t *ctx );
```

- `fan9_set_direction` This function is used to set direction of Fan 9 Click board.
```c
void fan9_set_direction ( fan9_t *ctx, uint8_t dir );
```

- `fan9_write_reg` This function reads a data bytes from the selected register by using I2C serial interface.
```c
err_t fan9_write_reg ( fan9_t *ctx, uint8_t reg, uint16_t data_in );
```

- `fan9_set_pwm` This function is used to get PWM value of Fan 9 Click board.
```c
err_t fan9_set_pwm ( fan9_t *ctx, uint8_t pwm_val );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fan9_cfg_t fan9_cfg;  /**< Click config object. */

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
    fan9_cfg_setup( &fan9_cfg );
    FAN9_MAP_MIKROBUS( fan9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fan9_init( &fan9, &fan9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FAN9_ERROR == fan9_default_cfg ( &fan9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    fan9_set_pwm( &fan9, 10 );
    // Waiting for motor to start.
    while ( 0 == fan9_get_rd_pin( &fan9 ) );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the speed of fans by changing the PWM duty cycle.
  The results are being displayed via USB UART where you can track their changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 10;
    static int8_t duty_inc = 10;
    uint8_t direction = FAN9_DIRECTION_CW;

    fan9_set_pwm( &fan9, duty_cnt );
    log_printf( &logger, " Set PWM: %d%% \r\n", ( uint16_t ) duty_cnt );
    
    if ( 100 == duty_cnt ) 
    {
        duty_inc = -10;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 10;
    }
    duty_cnt += duty_inc;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
