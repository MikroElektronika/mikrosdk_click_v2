
---
# 3D Hall 10 click

> 3D Hall 10 Click is a compact add-on board used to detect the strength of a magnetic field in all three dimensions. This board features the TMAG5170, a high-precision linear 3D Hall effect sensor from Texas Instruments. The TMAG5170 features an SPI interface for configuration by MCU. The measurement data is provided in digital format of 12-bits corresponding to the magnetic field measured in each X, Y, and Z axes. It can achieve ultra-high precision at speeds up to 20kSPS for faster and more accurate real-time control and offers multiple diagnostics features to detect and report both system and device-level failures.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the 3D Hall 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3D Hall 10 Click driver.

#### Standard key functions :

- `c3dhall10_cfg_setup` Config Object Initialization function.
```c
void c3dhall10_cfg_setup ( c3dhall10_cfg_t *cfg );
```

- `c3dhall10_init` Initialization function.
```c
err_t c3dhall10_init ( c3dhall10_t *ctx, c3dhall10_cfg_t *cfg );
```

- `c3dhall10_default_cfg` Click Default Configuration function.
```c
err_t c3dhall10_default_cfg ( c3dhall10_t *ctx );
```

#### Example key functions :

- `c3dhall10_get_alert_pin` This function returns the alert (ALR) pin logic state. The alert pin is configured as a conversion complete interrupt by default.
```c
uint8_t c3dhall10_get_alert_pin ( c3dhall10_t *ctx );
```

- `c3dhall10_read_data` This function reads new data which consists of X, Y, and Z axis values in mT, and temperature in Celsius. It also reads the angle in Degrees between X and Y by default, and magnitude data as well.
```c
err_t c3dhall10_read_data ( c3dhall10_t *ctx, c3dhall10_data_t *data_out );
```

- `c3dhall10_write_frame` This function writes a desired data to the selected register by using SPI serial interface.
```c
err_t c3dhall10_write_frame ( c3dhall10_t *ctx, uint8_t reg_addr, uint16_t data_in );
```

## Example Description

> This example demonstrates the use of 3D Hall 10 click board by reading the magnetic
flux density from 3 axes, and the angle and magnitude between X and Y axes as well as the sensor internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall10_cfg_t c3dhall10_cfg;  /**< Click config object. */

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
    c3dhall10_cfg_setup( &c3dhall10_cfg );
    C3DHALL10_MAP_MIKROBUS( c3dhall10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c3dhall10_init( &c3dhall10, &c3dhall10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL10_ERROR == c3dhall10_default_cfg ( &c3dhall10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the conversion complete interrupt and then reads the new data from the sensor approximately every 100ms and displays the measurement values on the USB UART.

```c
void application_task ( void )
{
    while ( c3dhall10_get_alert_pin ( &c3dhall10 ) );
    
    c3dhall10_data_t sensor_data;
    if ( C3DHALL10_OK == c3dhall10_read_data ( &c3dhall10, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f mT\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f mT\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f mT\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle: %.1f Degrees\r\n", sensor_data.angle );
        log_printf( &logger, " Magnitude: %u\r\n", sensor_data.magnitude );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
