\mainpage Main Page

---
# LED Driver 12 click

> LED Driver 12 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the PCA9532, a 16-bit I2C-configurable I/O expander optimized for dimming LEDs in 256 discrete Red/Green/Blue (RGB) steps from NXP Semiconductors. The PCA9532 offers high efficiency, supporting up to 16 LED channels and delivering a maximum of up to 25mA of LED current per channel. It contains an internal oscillator with two user-programmable blink rates and duty cycles coupled to the output PWM. Any bits not used for controlling the LEDs can be used for GPIO expansion, which provides a simple solution when additional I/O is needed for some sensors, push-buttons, or alarm monitoring. This Click board™ is suitable for color mixing and backlight application for amusement products, LED status signalization, home automation projects, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Driver 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 12 Click driver.

#### Standard key functions :

- `leddriver12_cfg_setup` Config Object Initialization function.
```c
void leddriver12_cfg_setup ( leddriver12_cfg_t *cfg );
```

- `leddriver12_init` Initialization function.
```c
err_t leddriver12_init ( leddriver12_t *ctx, leddriver12_cfg_t *cfg );
```

- `leddriver12_default_cfg` Click Default Configuration function.
```c
err_t leddriver12_default_cfg ( leddriver12_t *ctx );
```

#### Example key functions :

- `leddriver12_set_led_config` This function sets the specified LED config.
```c
err_t leddriver12_set_led_config ( leddriver12_t *ctx, uint8_t led_number, uint8_t led_cfg );
```

- `leddriver12_set_led_port_config` This function sets the specified LED port config.
```c
err_t leddriver12_set_led_port_config ( leddriver12_t *ctx, uint8_t led_port_number, uint8_t led_cfg );
```

- `leddriver12_set_blink_period_pwm_0` This function sets the blink period of PWM 0 function.
```c
err_t leddriver12_set_blink_period_pwm_0 ( leddriver12_t *ctx, float blink_period );
```

## Example Description

> This example demonstrates the use of LED Driver 12 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which turns OFF
the LEDs 0 to 7, configures LEDs 8 to 11 for PWM0, and LEDs 12 to 15 for PWM1 settings.
PWM0 is set at half duty cycle with a one-second blinking period, while PWM1 is configured
for a quarter of duty cycle with a half-second blinking period.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver12_cfg_t leddriver12_cfg;  /**< Click config object. */

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
    leddriver12_cfg_setup( &leddriver12_cfg );
    LEDDRIVER12_MAP_MIKROBUS( leddriver12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver12_init( &leddriver12, &leddriver12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER12_ERROR == leddriver12_default_cfg ( &leddriver12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles the LEDs 0-7 every 2 seconds and displays their state on the USB UART.

```c
void application_task ( void )
{
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED0_TO_3, LEDDRIVER12_LED_ON );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED4_TO_7, LEDDRIVER12_LED_ON );
    log_printf ( &logger, " LEDs 0-7 turns ON \r\n" );
    Delay_ms( 2000 );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED0_TO_3, LEDDRIVER12_LED_OFF );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED4_TO_7, LEDDRIVER12_LED_OFF );
    log_printf ( &logger, " LEDs 0-7 turns OFF \r\n\n" );
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
