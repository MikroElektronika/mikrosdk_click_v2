\mainpage Main Page

---
# Magneto 10 Click

> Magneto 10 Click is a compact add-on board that contains a 3D magnetometer. This board features the MLX90392, a +/-5mT range magnetometer for low-noise applications from Melexis Technologies. The MLX90392, specially designed for micropower applications, measures magnetic fields along the three axes (X, Y being in a plane parallel to the surface of the die, and Z being perpendicular to the surface).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto10_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/magneto-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto10 Click driver.

#### Standard key functions :

- `magneto10_cfg_setup` Config Object Initialization function.
```c
void magneto10_cfg_setup ( magneto10_cfg_t *cfg );
```

- `magneto10_init` Initialization function.
```c
err_t magneto10_init ( magneto10_t *ctx, magneto10_cfg_t *cfg );
```

- `magneto10_default_cfg` Click Default Configuration function.
```c
err_t magneto10_default_cfg ( magneto10_t *ctx );
```

#### Example key functions :

- `magneto10_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in microTesla.
```c
err_t magneto10_get_magnetic_flux ( magneto10_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `magneto10_get_temperature` This function reads the raw temperature value and converts it to Celsius.
```c
err_t magneto10_get_temperature ( magneto10_t *ctx, float *temperature );
```

- `magneto10_set_operating_mode` This function sets the device operating mode.
```c
err_t magneto10_set_operating_mode ( magneto10_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of Magneto 10 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    magneto10_cfg_t magneto10_cfg;  /**< Click config object. */

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
    magneto10_cfg_setup( &magneto10_cfg );
    MAGNETO10_MAP_MIKROBUS( magneto10_cfg, MIKROBUS_1 );
    
    if ( I2C_MASTER_ERROR == magneto10_init( &magneto10, &magneto10_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( MAGNETO10_ERROR == magneto10_default_cfg( &magneto10 ) ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnetic flux as well as the internal temperature data every 100ms and displays the results on the USB UART.

```c

void application_task ( void )
{
    float x_axis, y_axis, z_axis, temperature;
    if ( MAGNETO10_OK == magneto10_get_magnetic_flux ( &magneto10, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n Y-axis: %.2f uT\r\n Z-axis: %.2f uT\r\n", 
                    x_axis, y_axis, z_axis );
    }
    if ( MAGNETO10_OK == magneto10_get_temperature ( &magneto10, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
