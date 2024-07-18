\mainpage Main Page

---
# 3D Hall 14 click

> 3D Hall 14 Click is a compact add-on board designed for high-precision position sensing in various applications. This board features the MLX90394, a 3-axis magnetometer from Melexis based on the Triaxis® Hall technology. The MLX90394 offers low power consumption, excellent noise performance, and flexible measurement modes, including intelligent wake-up functions for efficient power management. It communicates via a standard 2-Wire I2C interface and supports fast-mode frequencies up to 1MHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the 3D Hall 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3D Hall 14 Click driver.

#### Standard key functions :

- `c3dhall14_cfg_setup` Config Object Initialization function.
```c
void c3dhall14_cfg_setup ( c3dhall14_cfg_t *cfg );
```

- `c3dhall14_init` Initialization function.
```c
err_t c3dhall14_init ( c3dhall14_t *ctx, c3dhall14_cfg_t *cfg );
```

- `c3dhall14_default_cfg` Click Default Configuration function.
```c
err_t c3dhall14_default_cfg ( c3dhall14_t *ctx );
```

#### Example key functions :

- `c3dhall14_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in microTesla.
```c
err_t c3dhall14_get_magnetic_flux ( c3dhall14_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `c3dhall14_get_temperature` This function reads the raw temperature value and converts it to Celsius.
```c
err_t c3dhall14_get_temperature ( c3dhall14_t *ctx, float *temperature );
```

- `c3dhall14_set_range` This function sets the magnetic flux measurement range.
```c
err_t c3dhall14_set_range ( c3dhall14_t *ctx, uint8_t range );
```

## Example Description

> This example demonstrates the use of 3D Hall 14 click board by reading the magnetic field strength from 3 axes and the sensor internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall14_cfg_t c3dhall14_cfg;  /**< Click config object. */

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
    c3dhall14_cfg_setup( &c3dhall14_cfg );
    C3DHALL14_MAP_MIKROBUS( c3dhall14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall14_init( &c3dhall14, &c3dhall14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL14_ERROR == c3dhall14_default_cfg ( &c3dhall14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data from the sensor and displays them on the USB UART every 200ms.

```c
void application_task ( void )
{
    float x_axis = 0;
    float y_axis = 0;
    float z_axis = 0;
    float temperature = 0;
    if ( C3DHALL14_OK == c3dhall14_get_magnetic_flux ( &c3dhall14, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.1f uT\r\n", x_axis );
        log_printf( &logger, " Y-axis: %.1f uT\r\n", y_axis );
        log_printf( &logger, " Z-axis: %.1f uT\r\n", z_axis );
    }
    if ( C3DHALL14_OK == c3dhall14_get_temperature ( &c3dhall14, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
