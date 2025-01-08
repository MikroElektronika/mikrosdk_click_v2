
---
# Buzz 3 Click

> [Buzz 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4390) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4390&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of Buzz 3 Click boards with PAM8904 for play the Imperial March.
PAM8904 is piezo-sounder driver with an integrated Multi-Mode charge pump boost converter from Diodes Incorporated. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzz3

### Example Key Functions

- `buzz3_cfg_setup` Config Object Initialization function.
```c
void buzz3_cfg_setup ( buzz3_cfg_t *cfg );
```

- `buzz3_init` Initialization function.
```c
err_t buzz3_init ( buzz3_t *ctx, buzz3_cfg_t *cfg );
```

- `buzz3_default_cfg` Click Default Configuration function.
```c
err_t buzz3_default_cfg ( buzz3_t *ctx );
```

- `buzz3_pwm_start` This function starts the PWM module output.
```c
err_t buzz3_pwm_start ( buzz3_t *ctx );
```

- `buzz3_set_gain_operating_mode` The function set gain operating mode of the PAM8904 piezo sounder driver with integrated charge pump boost converter on Buzz 3 Click board.
```c
err_t buzz3_set_gain_operating_mode ( buzz3_t *ctx, uint8_t op_mode );
```

- `buzz3_play_sound` This function plays sound on buzzer.
```c
void buzz3_play_sound ( buzz3_t *ctx, uint16_t freq, uint16_t duration );
```

### Application Init

> Initializes GPIO, set AN and RST pin as outputs, begins to write a log. 
> Initialization driver enables - GPIO and configures the appropriate MCU pin for 
> sound generation, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buzz3_cfg_t buzz3_cfg;      /**< Click config object. */

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

    buzz3_cfg_setup( &buzz3_cfg );
    BUZZ3_MAP_MIKROBUS( buzz3_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz3_init( &buzz3, &buzz3_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz3_default_cfg ( &buzz3 );
    buzz3_set_duty_cycle ( &buzz3, 0.0 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " Set the gain to x1  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    buzz3_pwm_start( &buzz3 );
    buzz3_set_gain_operating_mode( &buzz3, BUZZ3_OP_MODE_GAIN_x1 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, "   Play the music    \r\n" );
    buzz3_melody( );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
> So, in order to run this example and play all tones correctly, the user will need to decrease 
> the MCU's main clock frequency in MCU Settings for the certain architectures
> in order to get the required PWM clock frequency.

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
