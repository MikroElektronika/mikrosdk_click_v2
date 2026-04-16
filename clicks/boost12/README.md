
---
# Boost 12 Click

> [Boost 12 Click](https://www.mikroe.com/?pid_product=MIKROE-6861) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6861&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Boost 12 Click board, changing
the output voltage by generating a PWM signal whose duty cycle is gradually
increased and decreased between 10% and 100%.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost12

### Example Key Functions

- `boost12_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void boost12_cfg_setup ( boost12_cfg_t *cfg );
```

- `boost12_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t boost12_init ( boost12_t *ctx, boost12_cfg_t *cfg );
```

- `boost12_default_cfg` This function executes a default configuration of Boost 12 Click board.
```c
err_t boost12_default_cfg ( boost12_t *ctx );
```

- `boost12_pwm_start` This function starts the PWM module output.
```c
err_t boost12_pwm_start ( boost12_t *ctx );
```

- `boost12_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t boost12_set_duty_cycle ( boost12_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the logger and Boost 12 Click driver and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost12_cfg_t boost12_cfg;  /**< Click config object. */

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
    boost12_cfg_setup( &boost12_cfg );
    BOOST12_MAP_MIKROBUS( boost12_cfg, MIKROBUS_POSITION_BOOST12 );
    if ( PWM_ERROR == boost12_init( &boost12, &boost12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BOOST12_ERROR == boost12_default_cfg ( &boost12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Adjusts the PWM duty cycle in 1% steps, logs the current value, and smoothly oscillates the duty between minimum and maximum levels. 

```c
void application_task ( void )
{
    static int8_t duty_cnt = 10;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 100.0;
    
    boost12_set_duty_cycle ( &boost12, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( int16_t ) duty_cnt );
    
    duty_cnt += duty_inc;
    if ( ( duty_cnt < 10 ) || ( duty_cnt > 100 ) ) 
    {
        duty_inc = -duty_inc;
        duty_cnt += duty_inc;
        duty_cnt += duty_inc;
    }
    Delay_ms ( 1000 );
}
```

### Note

> The higher the duty cycle the higher the output voltage. The output voltage range is from VIN to 12V.

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
