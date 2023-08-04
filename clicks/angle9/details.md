
---
# Angle 9 click

> Angle 9 Click is a compact add-on board that detects the absolute position of a permanent magnet. This board features the AAS33001, a precision angle sensor with incremental and motor commutation outputs and on-chip linearization from Allegro Microsystems. It is a contactless angle sensor for 0° to 360° angular position, rotation speed, and directional measurement. Support for incremental output interface (ABI) and motor commutation (UVW) is also available. The same goes for the on-chip EEPROM for storing factory and customer calibration parameters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/angle-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Angle 9 Click driver.

#### Standard key functions :

- `angle9_cfg_setup` Config Object Initialization function.
```c
void angle9_cfg_setup ( angle9_cfg_t *cfg );
```

- `angle9_init` Initialization function.
```c
err_t angle9_init ( angle9_t *ctx, angle9_cfg_t *cfg );
```

#### Example key functions :

- `angle9_read_angle` This function reads the magnetic angular position in degrees.
```c
err_t angle9_read_angle ( angle9_t *ctx, float *angle );
```

- `angle9_read_field_strength` This function reads the magnetic field strength in gauss.
```c
err_t angle9_read_field_strength ( angle9_t *ctx, uint16_t *field_str );
```

- `angle9_read_temperature` This function reads the sensor internal temperature in degrees celsius.
```c
err_t angle9_read_temperature ( angle9_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Angle 9 click board by reading and displaying
the magnet's angular position in degrees, field strength in gauss, and the internal
sensor temperature in degrees celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle9_cfg_t angle9_cfg;  /**< Click config object. */

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
    angle9_cfg_setup( &angle9_cfg );
    ANGLE9_MAP_MIKROBUS( angle9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle9_init( &angle9, &angle9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees, magnetic field strength in gauss,
and the internal sensor temperature in degrees celsius and displays the results
on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle = 0;
    float int_temp = 0;
    uint16_t field_str = 0;
    if ( ANGLE9_OK == angle9_read_angle ( &angle9, &angle ) )
    {
        log_printf ( &logger, " Angle: %.1f deg\r\n", angle );
        if ( ANGLE9_OK == angle9_read_field_strength ( &angle9, &field_str ) )
        {
            log_printf ( &logger, " Field strength: %u Gauss\r\n", field_str );
        }
        if ( ANGLE9_OK == angle9_read_temperature ( &angle9, &int_temp ) )
        {
            log_printf ( &logger, " Internal temperature: %.2f degC\r\n\n", int_temp );
        }
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
