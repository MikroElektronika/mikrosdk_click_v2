\mainpage Main Page

---
# AN to PWM 2 click

> AN to PWM 2 Click is a compact add-on board that contains an easy-to-use component that converts the value of the input analog signal to a fixed frequency PWM voltage output, with a duty cycle proportional to the input voltage. This board features the LTC6992CS6, a silicon oscillator with an easy-to-use analog voltage-controlled pulse width modulation (PWM) capability from Analog Devices. It features the PWM signal controlled by analog input in range of -2.5V to 2.5V, frequency range up to 1 MHz, frequency error less than 1.7%, and it has good temperature stability. It has many features that make it well suited for heater control, PWM servo loops, LED dimming, signal isolation, and other duty cycle control applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/antopwm2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/an-to-pwm-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the AN to PWM 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AN to PWM 2 Click driver.

#### Standard key functions :

- `antopwm2_cfg_setup` Config Object Initialization function.
```c
void antopwm2_cfg_setup ( antopwm2_cfg_t *cfg );
```

- `antopwm2_init` Initialization function.
```c
err_t antopwm2_init ( antopwm2_t *ctx, antopwm2_cfg_t *cfg );
```

#### Example key functions :

- `antopwm2_set_frequency` This function sets a frequency output in a range from 500kHz to 1MHz by setting the digipot resistance.
```c
err_t antopwm2_set_frequency ( antopwm2_t *ctx, uint32_t freq );
```

- `antopwm2_set_frequency_otp` This function sets a frequency output in a range from 500kHz to 1MHz by setting the digipot resistance in OTP mode.
```c
err_t antopwm2_set_frequency_otp ( antopwm2_t *ctx, uint32_t freq );
```

## Example Description

> This example demonstrates the use of AN to PWM 2 click board by changing the PWM output frequency from 500kHz to 1MHz in steps of 50kHz.

**The demo application is composed of two sections :**

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
    Delay_ms ( 5000 );
}
```

## Note

> Applying a voltage of -2.5 to 2.5V on the input will generate the PWM pulse train with a duty cycle linearly proportional to the input voltage.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ANtoPWM2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
