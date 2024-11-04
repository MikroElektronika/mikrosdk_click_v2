\mainpage Main Page

---
# 3D Hall 9 Click

> 3D Hall 9 Click is a compact add-on board used to detect the strength of a magnetic field in all three dimensions. This board features the ALS31300, a 3D linear Hall-effect sensor with digital output and advanced low power management from Allegro Microsystems. The ALS31300 features an I2C interface, enabling it to be easily configured by MCU with the measurement data provided in digital format of 12-bits corresponding to the magnetic field measured in each X, Y, and Z axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/3d-hall-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the 3D Hall 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3D Hall 9 Click driver.

#### Standard key functions :

- `c3dhall9_cfg_setup` Config Object Initialization function.
```c
void c3dhall9_cfg_setup ( c3dhall9_cfg_t *cfg );
```

- `c3dhall9_init` Initialization function.
```c
err_t c3dhall9_init ( c3dhall9_t *ctx, c3dhall9_cfg_t *cfg );
```

- `c3dhall9_default_cfg` Click Default Configuration function.
```c
err_t c3dhall9_default_cfg ( c3dhall9_t *ctx );
```

#### Example key functions :

- `c3dhall9_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t c3dhall9_write_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t data_in );
```

- `c3dhall9_read_register` This function reads a desired data from the selected register by using I2C serial interface.
```c
err_t c3dhall9_read_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t *data_out );
```

- `c3dhall9_read_data` This function reads new data which consists of X, Y, and Z axis values in Gauss, and temperature in Celsius. It also calculates the angles between all axes in Degrees based on the raw axes data read.
```c
err_t c3dhall9_read_data ( c3dhall9_t *ctx, c3dhall9_data_t *data_out );
```

## Example Description

> This example demonstrates the use of 3D Hall 9 Click board by reading the magnetic
flux density from 3 axes as well as the angles between axes and the sensor temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall9_cfg_t c3dhall9_cfg;  /**< Click config object. */

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
    c3dhall9_cfg_setup( &c3dhall9_cfg );
    C3DHALL9_MAP_MIKROBUS( c3dhall9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall9_init( &c3dhall9, &c3dhall9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL9_ERROR == c3dhall9_default_cfg ( &c3dhall9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the new data from the sensor approximately every 300ms and displays the measurement values on the USB UART.

```c
void application_task ( void )
{
    c3dhall9_data_t sensor_data;
    
    if ( C3DHALL9_OK == c3dhall9_read_data ( &c3dhall9, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f Gauss\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f Gauss\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f Gauss\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle XY: %.1f Degrees\r\n", sensor_data.angle_xy );
        log_printf( &logger, " Angle XZ: %.1f Degrees\r\n", sensor_data.angle_xz );
        log_printf( &logger, " Angle YZ: %.1f Degrees\r\n", sensor_data.angle_yz );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
        Delay_ms ( 300 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
