
---
# Buzzer Click

> [Buzzer Click](https://www.mikroe.com/?pid_product=MIKROE-6370) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6370&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of Buzzer Click board by playing the Imperial March melody on the buzzer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzzer

### Example Key Functions

- `buzzer_cfg_setup` Config Object Initialization function.
```c
void buzzer_cfg_setup ( buzzer_cfg_t *cfg );
```

- `buzzer_init` Initialization function.
```c
err_t buzzer_init ( buzzer_t *ctx, buzzer_cfg_t *cfg );
```

- `buzzer_play_sound` This function plays sound on the buzzer.
```c
err_t buzzer_play_sound ( buzzer_t *ctx, uint16_t freq, uint8_t level, uint16_t duration );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzzer_cfg_t buzzer_cfg;  /**< Click config object. */

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
    buzzer_cfg_setup( &buzzer_cfg );
    BUZZER_MAP_MIKROBUS( buzzer_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == buzzer_init( &buzzer, &buzzer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " Playing the Imperial March melody...\r\n" );
    buzzer_imperial_march( BUZZER_VOLUME_MAX ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
So, in order to run this example and play all tones correctly, the user will need to decrease 
the MCU's main clock frequency in MCU Settings for the certain architectures
in order to get the required PWM clock frequency.

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
