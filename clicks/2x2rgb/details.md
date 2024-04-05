
---
# 2x2 RGB click

> 2x2 RGB Click is a compact add-on board that contains a matrix of 4 “intelligent” RGB elements, forming a 2x2 display screen. This board features the KTD2052A, a 12-channel RGB LED driver from Kinetic Technologies. It is a fully programmable current regulator for up to four RGB LEDs (12 LEDs in total). The LED matrix consists of four LRTB GFTG, a 6-lead in-line MULTILEDs, from ams OSRAM. The LEDs have a 120-degree viewing angle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/2x2rgb_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/2x2-rgb-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the 2x2 RGB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 2x2 RGB Click driver.

#### Standard key functions :

- `c2x2rgb_cfg_setup` Config Object Initialization function.
```c
void c2x2rgb_cfg_setup ( c2x2rgb_cfg_t *cfg );
```

- `c2x2rgb_init` Initialization function.
```c
err_t c2x2rgb_init ( c2x2rgb_t *ctx, c2x2rgb_cfg_t *cfg );
```

- `c2x2rgb_default_cfg` Click Default Configuration function.
```c
err_t c2x2rgb_default_cfg ( c2x2rgb_t *ctx );
```

#### Example key functions :

- `c2x2rgb_set_rgb_led` 2x2 RGB set RGB LED function.
```c
err_t c2x2rgb_set_rgb_led ( c2x2rgb_t *ctx, uint8_t led_num, uint16_t ired, uint16_t igrn, uint16_t iblu );
```

- `c2x2rgb_set_control` 2x2 RGB set control function.
```c
err_t c2x2rgb_set_control ( c2x2rgb_t *ctx, uint8_t en_mode, uint8_t be_en, 
                                            uint8_t ce_temp, uint8_t fade_rate );
```

## Example Description

> This example demonstrates the use of the 2x2 RGB Click board™ 
> by controlling the color of the LEDs [1-4].

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2x2rgb_cfg_t c2x2rgb_cfg;  /**< Click config object. */

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
    c2x2rgb_cfg_setup( &c2x2rgb_cfg );
    C2X2RGB_MAP_MIKROBUS( c2x2rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c2x2rgb_init( &c2x2rgb, &c2x2rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C2X2RGB_ERROR == c2x2rgb_default_cfg ( &c2x2rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------" );
    Delay_ms ( 100 );
}
```

### Application Task

> This simple example shows all LEDs in different colors.
> These LEDs actually consist of three single-colored LEDs (Red, Green and Blue) in a single package. 
> Various colors can be reproduced by mixing the intensity of each LED.

```c
void application_task ( void ) 
{
    log_printf( &logger, "\r\nRED: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT,
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nGREEN: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nBLUE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nWHITE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    log_printf( &logger, "\r\n----------------" );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.2x2RGB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
