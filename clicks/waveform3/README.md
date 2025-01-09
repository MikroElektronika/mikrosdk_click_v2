
---
# Waveform 3 Click

> [Waveform 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4432) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4432&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo app shows the basic capabilities of Waveform 3
Click board. First, the sinusoidal wave is incremented
to targeted frequency for visually pleasing introduction
after which it changes between 4 modes of output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform3

### Example Key Functions

- `waveform3_cfg_setup` Config Object Initialization function.
```c
void waveform3_cfg_setup ( waveform3_cfg_t *cfg );
```

- `waveform3_init` Initialization function.
```c
err_t waveform3_init ( waveform3_t *ctx, waveform3_cfg_t *cfg );
```

- `waveform3_default_cfg` Click Default Configuration function.
```c
void waveform3_default_cfg ( waveform3_t *ctx );
```

- `waveform3_set_mode` This function sets output mode, freq and phase channels of AD9837 waveform generator.
```c
void waveform3_set_mode ( waveform3_t *ctx, uint8_t mode, uint8_t freq_reg, uint8_t phase_reg );
```

- `waveform3_set_freq` This function sets desired frequency ( in Hz ) on desired freq channel.
```c
uint32_t waveform3_set_freq ( waveform3_t *ctx, uint32_t frequency, uint8_t freq_reg );
```

- `waveform3_set_phase` This function sets desired phase shift ( in degrees ) on desired phase channel.
```c
uint16_t waveform3_set_phase ( waveform3_t *ctx, float phase, uint8_t phase_reg );
```

### Application Init

> Application initializes the UART LOG and SPI drivers,
resets the device and sets frequency and phase shift to
default values. In the end, the mode is set with the 
preferred freq and phase channel.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    waveform3_cfg_t waveform3_cfg;  /**< Click config object. */

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

    waveform3_cfg_setup( &waveform3_cfg );
    WAVEFORM3_MAP_MIKROBUS( waveform3_cfg, MIKROBUS_1 );
    err_t init_flag  = waveform3_init( &waveform3, &waveform3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    waveform3_default_cfg( &waveform3 );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
    waveform3_set_mode( &waveform3, WAVEFORM3_CFG_MODE_SINUSOIDAL, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
}
```

### Application Task

> Task commences with the start frequency rising up to
the targeted one. When it reaches desired frequency,
the mode changes every 5 seconds which includes: 
sinusoidal, triangular, DAC divided by 2 and DAC
outputs respectively.

```c
void application_task ( void ) 
{
    uint8_t cfg_mode_switch;
    
    if ( start_frequency < target_frequency ) {
        if ( start_frequency / rising_factor < 100 ) {
            start_frequency += rising_factor;
            waveform3_set_freq( &waveform3, start_frequency, WAVEFORM3_CFG_FREQ_REG0 );
            Delay_ms ( 5 );
        } else {
            rising_factor += 10;
        }
    } else {
        for ( cfg_mode_switch = 0 ; cfg_mode_switch < 4 ; cfg_mode_switch++ ) {
        waveform3_set_mode( &waveform3, cfg_mode_switch, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        }
    }
}
```

### Note

> Waveform 3 Click might not provide a high enough peak to peak signal on higher frequencies.
The user can freely implement custom buffer for the output stage.

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
