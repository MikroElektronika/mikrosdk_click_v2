
---
# LightHz click

> LightHz Click is a compact add-on board that effectively measures ambient light intensity. This board features the TL2L30BR, a programmable light-to-frequency converter from ams. The sensor outputs either a pulse train or a square wave (50% duty cycle) with a frequency directly proportional to light intensity (irradiance). It has programmable sensitivity and full-scale output frequency and could be used as a rough color detector with a selectable frequency range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lighthz_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lighthz-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the LightHz Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightHz Click driver.

#### Standard key functions :

- `lighthz_cfg_setup` Config Object Initialization function.
```c
void lighthz_cfg_setup ( lighthz_cfg_t *cfg );
```

- `lighthz_init` Initialization function.
```c
err_t lighthz_init ( lighthz_t *ctx, lighthz_cfg_t *cfg );
```

#### Example key functions :

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

## Example Description

> This example demonstrates the use of LightHz click board by measuring and displaying the frequency of clock output signal.
The higher the light intensity the higher the frequency.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightHz

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
