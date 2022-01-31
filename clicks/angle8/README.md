\mainpage Main Page

---
# Angle 8 click

> Angle 8 Click is a compact add-on board that detects the absolute angular position of a permanent magnet. This board features the MA782GGU, a low-power angle sensor with integrated wake-up angle detection from Monolithic Power Systems. With its power cycling ability, the MA782GGU can be optimized for applications that require low average power. It supports a wide range of magnetic field strengths and spatial configurations, with both end-of-shaft and off-axis (side-shaft mounting), supported configurations. Fast data acquisition and processing provides accurate angle measurement at an applied magnetic field of 60mT, alongside magnetic field strength detection with programmable thresholds. This Click board™ is suitable for general-purpose angle measurements, in embedded motion control applications, as a power/speed control trigger solution, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/angle-8-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Angle 8 Click driver.

#### Standard key functions :

- `angle8_cfg_setup` Config Object Initialization function.
```c
void angle8_cfg_setup ( angle8_cfg_t *cfg );
```

- `angle8_init` Initialization function.
```c
err_t angle8_init ( angle8_t *ctx, angle8_cfg_t *cfg );
```

- `angle8_default_cfg` Click Default Configuration function.
```c
err_t angle8_default_cfg ( angle8_t *ctx );
```

#### Example key functions :

- `angle8_get_nd_pin` This function returns the new data ready (ND) pin logic state.
```c
uint8_t angle8_get_nd_pin ( angle8_t *ctx );
```

- `angle8_set_cycle_time` This function sets the sensor cycle time (measurement rate) in milliseconds.
```c
err_t angle8_set_cycle_time ( angle8_t *ctx, float time_ms );
```

- `angle8_read_angle` This function reads raw angle data and converts it to degrees.
```c
err_t angle8_read_angle ( angle8_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Angle 8 click board by reading and displaying the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the clockwise rotation direction and cycle time to 100ms.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle8_cfg_t angle8_cfg;  /**< Click config object. */

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
    angle8_cfg_setup( &angle8_cfg );
    ANGLE8_MAP_MIKROBUS( angle8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle8_init( &angle8, &angle8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE8_ERROR == angle8_default_cfg ( &angle8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the new data ready flag and then reads the magnet's angular position in degrees and displays the results on the USB UART.

```c
void application_task ( void )
{
    if ( angle8_get_nd_pin ( &angle8 ) )
    {
        float angle = 0;
        if ( ANGLE8_OK == angle8_read_angle ( &angle8, &angle ) )
        {
            log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
