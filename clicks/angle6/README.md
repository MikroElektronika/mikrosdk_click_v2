\mainpage Main Page

---
# Angle 6 Click

> Angle 6 Click is a compact add-on board that detects the absolute angular position of a permanent magnet, typically a diametrically magnetized cylinder on a rotating shaft. This board features the MAQ470GQE, a 12-bit contactless angle sensor with PWM output from Monolithic Power Systems. It supports a wide range of magnetic field strengths and spatial configurations, with both end-of-shaft and off-axis (side-shaft mounting), supported configurations. Fast data acquisition and processing provides accurate angle measurement at speeds from 0 to 60,000 rpm, alongside magnetic field strength detection with programmable thresholds.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/angle-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Angle 6 Click driver.

#### Standard key functions :

- `angle6_cfg_setup` Config Object Initialization function.
```c
void angle6_cfg_setup ( angle6_cfg_t *cfg );
```

- `angle6_init` Initialization function.
```c
err_t angle6_init ( angle6_t *ctx, angle6_cfg_t *cfg );
```

- `angle6_default_cfg` Click Default Configuration function.
```c
err_t angle6_default_cfg ( angle6_t *ctx );
```

#### Example key functions :

- `angle6_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t angle6_write_register ( angle6_t *ctx, uint8_t reg, uint8_t data_in );
```

- `angle6_read_register` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t angle6_read_register ( angle6_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `angle6_read_angle` This function reads raw angle data and converts it to degrees.
```c
err_t angle6_read_angle ( angle6_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Angle 6 Click board by reading and displaying the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the rotation direction to clockwise.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle6_cfg_t angle6_cfg;  /**< Click config object. */

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
    angle6_cfg_setup( &angle6_cfg );
    ANGLE6_MAP_MIKROBUS( angle6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle6_init( &angle6, &angle6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE6_ERROR == angle6_default_cfg ( &angle6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle = 0;
    if ( ANGLE6_OK == angle6_read_angle ( &angle6, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
