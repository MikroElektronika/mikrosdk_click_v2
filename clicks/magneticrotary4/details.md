
---
# Magnetic Rotary 4 Click

> Magnetic Rotary 4 Click is a compact add-on board for accurate magnet-position sensing. This board features the AS5047D, an SPI-configurable high-resolution rotary position sensor for fast absolute angle measurement over a full 360-degree range from ams AG. The AS5047D is equipped with revolutionary integrated dynamic angle error compensation (DAEC™) with almost 0 latency and offers a robust design that suppresses the influence of any homogenous external stray magnetic field. It also comes with an onboard header reserved for incremental and commutation signals of their respective A/B/I and U/V/W signals alongside embedded self-diagnostics, including magnetic field strength, lost magnet, and other related diagnostic features.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/magnetic-rotary-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Magnetic Rotary 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magnetic Rotary 4 Click driver.

#### Standard key functions :

- `magneticrotary4_cfg_setup` Config Object Initialization function.
```c
void magneticrotary4_cfg_setup ( magneticrotary4_cfg_t *cfg );
```

- `magneticrotary4_init` Initialization function.
```c
err_t magneticrotary4_init ( magneticrotary4_t *ctx, magneticrotary4_cfg_t *cfg );
```

#### Example key functions :

- `magneticrotary4_set_rotation_direction` This function sets the magnet rotation direction to clockwise or counter-clockwise.
```c
err_t magneticrotary4_set_rotation_direction ( magneticrotary4_t *ctx, uint8_t direction );
```

- `magneticrotary4_calibrate_zero_position` This function calibrates the sensor to zero Angle position.
```c
err_t magneticrotary4_calibrate_zero_position ( magneticrotary4_t *ctx );
```

- `magneticrotary4_get_angle` This function reads the absolute position raw data and converts it to degrees (Angle).
```c
err_t magneticrotary4_get_angle ( magneticrotary4_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Magnetic Rotary 4 Click board by reading and displaying the magnet (potentiometer) angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, sets the rotation direction, and calibrates the sensor for potentiometer zero position.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary4_cfg_t magneticrotary4_cfg;  /**< Click config object. */

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
    magneticrotary4_cfg_setup( &magneticrotary4_cfg );
    MAGNETICROTARY4_MAP_MIKROBUS( magneticrotary4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary4_init( &magneticrotary4, &magneticrotary4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_set_rotation_direction ( &magneticrotary4, MAGNETICROTARY4_DIRECTION_CW ) )
    {
        log_error( &logger, " Set rotation direction." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_calibrate_zero_position ( &magneticrotary4 ) )
    {
        log_error( &logger, " Calibrate zero position." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet (potentiometer) angular position in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY4_OK == magneticrotary4_get_angle ( &magneticrotary4, &angle ) )
    {
        log_printf( &logger, " Angle: %.1f degrees\r\n\n", angle );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
