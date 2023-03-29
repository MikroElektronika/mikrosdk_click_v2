
---
# Magnetic Rotary 6 click

> Magnetic Rotary 6 Click is a compact add-on board for accurate magnet-position sensing. This board features the AS5247U, an SPI-configurable high-resolution dual rotary position sensor for fast absolute angle measurement over a full 360-degree range from ams AG. The AS5047D is equipped with revolutionary integrated dynamic angle error compensation (DAEC™) with almost 0 latency and offers a robust design that suppresses the influence of any homogenous external stray magnetic field. It also comes with onboard headers reserved for incremental and commutation signals of their respective A/B/I and U/V/W signals, with a maximum resolution of 16384 steps / 4096 pulses per revolution, alongside embedded self-diagnostics features.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magnetic-rotary-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Magnetic Rotary 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magnetic Rotary 6 Click driver.

#### Standard key functions :

- `magneticrotary6_cfg_setup` Config Object Initialization function.
```c
void magneticrotary6_cfg_setup ( magneticrotary6_cfg_t *cfg );
```

- `magneticrotary6_init` Initialization function.
```c
err_t magneticrotary6_init ( magneticrotary6_t *ctx, magneticrotary6_cfg_t *cfg );
```

- `magneticrotary6_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary6_default_cfg ( magneticrotary6_t *ctx );
```

#### Example key functions :

- `magneticrotary6_write_register` This function writes a desired data to the selected register of a desired sensor die by using SPI serial interface.
```c
err_t magneticrotary6_write_register ( magneticrotary6_t *ctx, uint8_t die_sel, uint16_t reg, uint16_t data_in );
```

- `magneticrotary6_get_angle` This function reads the absolute position raw data of a desired sensor die and converts it to degrees (Angle).
```c
err_t magneticrotary6_get_angle ( magneticrotary6_t *ctx, uint8_t die_sel, float *angle );
```

- `magneticrotary6_set_direction` This function sets the rotation direction of a desired sensor die.
```c
err_t magneticrotary6_set_direction ( magneticrotary6_t *ctx, uint8_t die_sel, uint8_t dir );
```

## Example Description

> This example demonstrates the use of Magnetic Rotary 6 click board by reading and displaying the magnet's angular position in degrees measured by the bottom and top sensor dies.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the magnet rotation direction for the bottom die to clockwise and for the top die to counter-clockwise.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary6_cfg_t magneticrotary6_cfg;  /**< Click config object. */

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
    magneticrotary6_cfg_setup( &magneticrotary6_cfg );
    MAGNETICROTARY6_MAP_MIKROBUS( magneticrotary6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary6_init( &magneticrotary6, &magneticrotary6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY6_ERROR == magneticrotary6_default_cfg ( &magneticrotary6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position from both sensor dies in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_BOTTOM, &angle ) )
    {
        log_printf( &logger, " Angle (bottom die): %.1f degrees\r\n", angle );
    }
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_TOP, &angle ) )
    {
        log_printf( &logger, " Angle (top die): %.1f degrees\r\n\n", angle );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
