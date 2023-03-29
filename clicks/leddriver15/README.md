\mainpage Main Page

---
# LED Driver 15 click

> LED Driver 15 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the MP3309C, a fully integrated synchronous boost white LED driver with an I2C interface from Monolithic Power Systems. The MP3309C offers high efficiency, delivers up to 40mA of LED current, and operates from a voltage of mikroBUS™ power rails, supporting up to 8 white LEDs in series. It also features a programmable switching frequency to optimize efficiency, supports analog and PWM dimming, and has multiple built-in protection functions that protect the circuit during abnormalities.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Driver 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 15 Click driver.

#### Standard key functions :

- `leddriver15_cfg_setup` Config Object Initialization function.
```c
void leddriver15_cfg_setup ( leddriver15_cfg_t *cfg );
```

- `leddriver15_init` Initialization function.
```c
err_t leddriver15_init ( leddriver15_t *ctx, leddriver15_cfg_t *cfg );
```

- `leddriver15_default_cfg` Click Default Configuration function.
```c
err_t leddriver15_default_cfg ( leddriver15_t *ctx );
```

#### Example key functions :

- `leddriver15_set_i2c_dimming` This function sets the LEDs dimming level in I2C mode.
```c
err_t leddriver15_set_i2c_dimming ( leddriver15_t *ctx, uint8_t dimming );
```

- `leddriver15_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void leddriver15_enable_device ( leddriver15_t *ctx );
```

- `leddriver15_disable_device` This function disables the device by setting the EN pin to low logic state.
```c
void leddriver15_disable_device ( leddriver15_t *ctx );
```

## Example Description

> This example demonstrates the use of LED Driver 15 click board by changing the LEDs dimming level.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver15_cfg_t leddriver15_cfg;  /**< Click config object. */

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
    leddriver15_cfg_setup( &leddriver15_cfg );
    LEDDRIVER15_MAP_MIKROBUS( leddriver15_cfg, MIKROBUS_1 );
    if ( LEDDRIVER15_OK != leddriver15_init( &leddriver15, &leddriver15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER15_OK != leddriver15_default_cfg ( &leddriver15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the LEDs dimming level in I2C mode every 500ms. The dimming level will be displayed on the USB UART.

```c
void application_task ( void )
{
    static uint8_t dimming = LEDDRIVER15_I2C_DIMMING_MIN;
    if ( LEDDRIVER15_OK == leddriver15_set_i2c_dimming ( &leddriver15, dimming ) )
    {
        log_printf( &logger, " Dimming level: %u\r\n\n", ( uint16_t ) dimming );
    }
    if ( ++dimming > LEDDRIVER15_I2C_DIMMING_MAX )
    {
        dimming = LEDDRIVER15_I2C_DIMMING_MIN;
    }
    Delay_ms( 500 );
}
```

## Note

> It is recommended to connect 8 LEDs in series (40mA) to the output connector.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
