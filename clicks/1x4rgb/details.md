
---
# 1x4 RGB click

> 1x4 RGB Click is a compact add-on board that creates vivid and dynamic lighting effects. This board features the LP5812, an advanced RGB LED driver from Texas Instruments. It features ultra-low operation current, an autonomous animation engine, and support for both analog and PWM dimming. The board operates with 3.3V or 5V logic voltage levels and communicates with the host MCU via a standard 2-wire I2C interface. It is suitable for portable and wearable electronics, gaming, home entertainment, IoT, networking, industrial HMI, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/1x4rgb_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/1x4-rgb-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the 1x4 RGB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 1x4 RGB Click driver.

#### Standard key functions :

- `c1x4rgb_cfg_setup` Config Object Initialization function.
```c
void c1x4rgb_cfg_setup ( c1x4rgb_cfg_t *cfg );
```

- `c1x4rgb_init` Initialization function.
```c
err_t c1x4rgb_init ( c1x4rgb_t *ctx, c1x4rgb_cfg_t *cfg );
```

- `c1x4rgb_default_cfg` Click Default Configuration function.
```c
err_t c1x4rgb_default_cfg ( c1x4rgb_t *ctx );
```

#### Example key functions :

- `c1x4rgb_set_rgb_color` This function sets the desired values of RGB colors for the selected LED by using the I2C serial interface.
```c
err_t c1x4rgb_set_rgb_color ( c1x4rgb_t *ctx, uint8_t led_pos, uint8_t red, uint8_t green, uint8_t blue );
```

- `c1x4rgb_enable_leds` This function turns on the desired LEDs by using the I2C serial interface.
```c
err_t c1x4rgb_enable_leds ( c1x4rgb_t *ctx, uint16_t led_bitmask );
```

- `c1x4rgb_set_tmc_mode` This function configures the desired LED drive mode as TCM 1/2/3/4 scans using the I2C serial interface.
```c
err_t c1x4rgb_set_tmc_mode ( c1x4rgb_t *ctx, uint8_t dev_cfg, uint8_t mode );
```

## Example Description

> This example demonstrates the use of the 1x4 RGB Click board
> by controlling the color of the LEDs [LD1-LD4].

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1x4rgb_cfg_t c1x4rgb_cfg;  /**< Click config object. */

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
    c1x4rgb_cfg_setup( &c1x4rgb_cfg );
    C1X4RGB_MAP_MIKROBUS( c1x4rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c1x4rgb_init( &c1x4rgb, &c1x4rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1X4RGB_ERROR == c1x4rgb_default_cfg ( &c1x4rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> The demo example shows the color change of four RGB LEDs, 
> starting with red color, through green and blue, and ending with white.
> These LEDs actually consist of three single-colored LEDs 
> (Red-Green-Blue) in a single package. 
> Various colors can be reproduced by mixing the intensity of each LED.

```c
void application_task ( void ) 
{
    log_printf( &logger, "\r\n\n RED: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n GREEN: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n BLUE: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n WHITE:" );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.1x4RGB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
