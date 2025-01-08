
---
# BUZZ Click

> [BUZZ Click](https://www.mikroe.com/?pid_product=MIKROE-945) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-945&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of Buzz Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BUZZ

### Example Key Functions

- `buzz_cfg_setup` Config Object Initialization function.
```c
void buzz_cfg_setup ( buzz_cfg_t *cfg );
```

- `buzz_init` Initialization function.
```c
err_t buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );
```

- `buzz_default_cfg` Click Default Configuration function.
```c
void buzz_default_cfg ( buzz_t *ctx );
```

- `buzz_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ]).
```c
err_t buzz_set_duty_cycle ( buzz_t *ctx, float duty_cycle );
```

- `buzz_pwm_stop` This function stops the PWM moudle output.
```c
err_t buzz_pwm_stop ( buzz_t *ctx );
```

- `buzz_pwm_start` This function starts the PWM moudle output.
```c
err_t buzz_pwm_start ( buzz_t *ctx );
```

- `buzz_play_sound` This function plays sound on buzzer.
```c
void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzz_cfg_t buzz_cfg;  /**< Click config object. */

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

    buzz_cfg_setup( &buzz_cfg );
    BUZZ_MAP_MIKROBUS( buzz_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz_init( &buzz, &buzz_cfg );
    if ( init_flag == PWM_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz_set_duty_cycle ( &buzz, 0.0 );
    buzz_pwm_start( &buzz );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. So, in order to run this example and play all tones correctly, the user will need to decrease the MCU's main clock frequency in MCU Settings for the certain architectures in order to get the required PWM clock frequency.

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
