
---
# Haptic 5 Click

> [Haptic 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6576) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6576&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the control of the Haptic 5 Click board.
In I2C mode, the example toggles the haptic trigger pin periodically to generate vibration pulses.
In PWM mode, it gradually increases and decreases the output duty cycle to modulate the vibration intensity,
while toggling the direction when the duty reaches 0%.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic5

### Example Key Functions

- `haptic5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void haptic5_cfg_setup ( haptic5_cfg_t *cfg );
```

- `haptic5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t haptic5_init ( haptic5_t *ctx, haptic5_cfg_t *cfg );
```

- `haptic5_default_cfg` This function executes a default configuration of Haptic 5 Click board.
```c
err_t haptic5_default_cfg ( haptic5_t *ctx );
```

- `haptic5_set_duty_cycle` This function sets the PWM duty cycle.
```c
err_t haptic5_set_duty_cycle ( haptic5_t *ctx, float duty_cycle );
```

- `haptic5_toggle_dir` This function toggles the state of the DIR pin.
```c
void haptic5_toggle_dir ( haptic5_t *ctx );
```

### Application Init

> Initializes the logger and the Click board driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic5_cfg_t haptic5_cfg;  /**< Click config object. */

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
    haptic5_cfg_setup( &haptic5_cfg );
    HAPTIC5_MAP_MIKROBUS( haptic5_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == haptic5_init( &haptic5, &haptic5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC5_ERROR == haptic5_default_cfg ( &haptic5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected communication interface (I2C or PWM), toggles the haptic trigger (I2C),
or changes PWM duty cycle and direction (PWM).

```c
void application_task ( void )
{
#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )
    log_printf( &logger, " Haptic state: Active\r\n\n" );
    haptic5_set_trg_high ( &haptic5 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Haptic state: Idle\r\n\n" );
    haptic5_set_trg_low ( &haptic5 );
    Delay_ms ( 1000 );
#else
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    haptic5_set_duty_cycle ( &haptic5, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        haptic5_toggle_dir ( &haptic5 );
    }
    duty_cnt += duty_inc;
#endif
}
```

### Note

> The mode is selected via the @b HAPTIC5_DEFAULT_COM macro. Ensure proper configuration and wiring 
based on the selected mode before running the example.

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
