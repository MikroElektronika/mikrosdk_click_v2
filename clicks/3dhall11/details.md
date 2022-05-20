
---
# 3D Hall 11 click

> 3D Hall 11 Click is a compact add-on board used to detect the strength of a magnetic field in all three dimensions. This board features the TMAG5273, a low-power linear 3D Hall-effect sensor from Texas Instruments. A precision analog signal chain alongside an integrated 12-bit ADC digitizes the measured analog magnetic field values and passes them via the I2C interface to the microcontroller for further processing. It can achieve ultra-high precision at speeds up to 20kSPS for faster and more accurate real-time control and has an integrated temperature sensor available for multiple system functions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the 3D Hall 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3D Hall 11 Click driver.

#### Standard key functions :

- `c3dhall11_cfg_setup` Config Object Initialization function.
```c
void c3dhall11_cfg_setup ( c3dhall11_cfg_t *cfg );
```

- `c3dhall11_init` Initialization function.
```c
err_t c3dhall11_init ( c3dhall11_t *ctx, c3dhall11_cfg_t *cfg );
```

- `c3dhall11_default_cfg` Click Default Configuration function.
```c
err_t c3dhall11_default_cfg ( c3dhall11_t *ctx );
```

#### Example key functions :

- `c3dhall11_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t c3dhall11_write_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t data_in );
```

- `c3dhall11_read_register` This function reads data from the selected register.
```c
err_t c3dhall11_read_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `c3dhall11_read_data` This function reads new data which consists of X, Y, and Z axis values in mT, and temperature in Celsius. It also reads the angle in Degrees between X and Y by default, and magnitude data as well.
```c
err_t c3dhall11_read_data ( c3dhall11_t *ctx, c3dhall11_data_t *data_out );
```

## Example Description

> This example demonstrates the use of 3D Hall 11 click board by reading the magnetic
flux density from 3 axes, and the angle and magnitude between X and Y axes
as well as the sensor internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall11_cfg_t c3dhall11_cfg;  /**< Click config object. */

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
    c3dhall11_cfg_setup( &c3dhall11_cfg );
    C3DHALL11_MAP_MIKROBUS( c3dhall11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall11_init( &c3dhall11, &c3dhall11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL11_ERROR == c3dhall11_default_cfg ( &c3dhall11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data from the sensor approximately every 100ms and displays the measurement values on the USB UART.

```c
void application_task ( void )
{
    c3dhall11_data_t sensor_data;
    if ( C3DHALL11_OK == c3dhall11_read_data ( &c3dhall11, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f mT\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f mT\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f mT\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle: %.1f Degrees\r\n", sensor_data.angle );
        log_printf( &logger, " Magnitude: %u\r\n", ( uint16_t ) sensor_data.magnitude );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
