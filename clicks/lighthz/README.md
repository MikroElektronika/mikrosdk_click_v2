
---
# LightHz Click

> [LightHz Click](https://www.mikroe.com/?pid_product=MIKROE-990) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-990&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of LightHz Click board by measuring and displaying the frequency of clock output signal.
The higher the light intensity the higher the frequency.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightHz

### Example Key Functions

- `lighthz_cfg_setup` Config Object Initialization function.
```c
void lighthz_cfg_setup ( lighthz_cfg_t *cfg );
```

- `lighthz_init` Initialization function.
```c
err_t lighthz_init ( lighthz_t *ctx, lighthz_cfg_t *cfg );
```

- `lighthz_set_sensitivity` This function sets the sensor sensitivity.
```c
void lighthz_set_sensitivity ( lighthz_t *ctx, uint8_t mode );
```

- `lighthz_set_frequency_scaling` This function sets the sensor frequency scaling.
```c
void lighthz_set_frequency_scaling ( lighthz_t *ctx, uint8_t mode );
```

- `lighthz_get_freq_pin` This function returns the freq pin logic state.
```c
uint8_t lighthz_get_freq_pin ( lighthz_t *ctx );
```

### Application Init

> Initializes the driver and sets the sensitivity mode and frequency scaling in case the onboard jumpers are set to MCU instead to ON-BRD.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lighthz_cfg_t lighthz_cfg;  /**< Click config object. */

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
    lighthz_cfg_setup( &lighthz_cfg );
    LIGHTHZ_MAP_MIKROBUS( lighthz_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == lighthz_init( &lighthz, &lighthz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lighthz_set_sensitivity ( &lighthz, LIGHTHZ_SENS_100X );
    lighthz_set_frequency_scaling ( &lighthz, LIGHTHZ_FSCALE_100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures the clock output frequency using the polling method and delays. The results are being sent to the USB UART.

```c
void application_task ( void )
{
    uint32_t freq_cnt = 0;
    uint16_t sample_cnt = 0;

    // Wait for the clock rising edge signal
    while ( !hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) );

    // A loop for measuring the clock frequency counts. It's not an ideal implementation.
    // Here we should use an external interrupt on the clock pin rising edge and a timer interrupt
    // for the best accuracy, however, those interrupt features have not yet been implemented in the SDK. 
    while ( ( sample_cnt < LIGHTHZ_SAMPLE_COUNTS ) && ( freq_cnt < LIGHTHZ_MAX_COUNTS_PER_S ) )
    {
        // A single iteration in the loops below should take as close to 10us as possible
        // So to improve the measurement accuracy adjust the delay below for your system
        while ( hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) )
        {
            freq_cnt++;
            Delay_us ( LIGHTHZ_DELAY_US );
        }
        while ( !hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) )
        {
            freq_cnt++;
            Delay_us ( LIGHTHZ_DELAY_US );
        }
        sample_cnt++;
    }
    freq_cnt /= sample_cnt;

    // The higher the light intensity the higher the frequency.
    log_printf( &logger, " Frequency: %.1f Hz\r\n\n", ( float ) LIGHTHZ_MAX_COUNTS_PER_S / freq_cnt );

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
