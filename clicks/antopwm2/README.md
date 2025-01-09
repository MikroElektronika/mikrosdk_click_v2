
---
# AN to PWM 2 Click

> [AN to PWM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4221) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4221&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of AN to PWM 2 Click board by changing the PWM output frequency from 500kHz to 1MHz in steps of 50kHz.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ANtoPWM2

### Example Key Functions

- `antopwm2_cfg_setup` Config Object Initialization function.
```c
void antopwm2_cfg_setup ( antopwm2_cfg_t *cfg );
```

- `antopwm2_init` Initialization function.
```c
err_t antopwm2_init ( antopwm2_t *ctx, antopwm2_cfg_t *cfg );
```

- `antopwm2_set_frequency` This function sets a frequency output in a range from 500kHz to 1MHz by setting the digipot resistance.
```c
err_t antopwm2_set_frequency ( antopwm2_t *ctx, uint32_t freq );
```

- `antopwm2_set_frequency_otp` This function sets a frequency output in a range from 500kHz to 1MHz by setting the digipot resistance in OTP mode.
```c
err_t antopwm2_set_frequency_otp ( antopwm2_t *ctx, uint32_t freq );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    antopwm2_cfg_t antopwm2_cfg;  /**< Click config object. */

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
    antopwm2_cfg_setup( &antopwm2_cfg );
    ANTOPWM2_MAP_MIKROBUS( antopwm2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == antopwm2_init( &antopwm2, &antopwm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the PWM output frequency every 5 seconds in steps of 50kHz going through the full range from 500kHz to 1MHz. The currently set frequency will be displayed on the USB UART.

```c
void application_task ( void )
{
    static uint32_t freq = ANTOPWM2_FREQ_MIN;
    if ( ANTOPWM2_OK == antopwm2_set_frequency ( &antopwm2, freq ) )
    {
        log_printf ( &logger, " Frequency: %lu Hz\r\n\n", freq );
    }
    freq += 50000;
    if ( freq > ANTOPWM2_FREQ_MAX )
    {
        freq = ANTOPWM2_FREQ_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Applying a voltage of -2.5 to 2.5V on the input will generate the PWM pulse train with a duty cycle linearly proportional to the input voltage.

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
