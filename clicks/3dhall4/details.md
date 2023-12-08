
---
# 3D Hall 4 click

> 3D Hall 4 Click is a compact add-on board that can detect the strength of a magnetic field in all three dimensions. This board features the SENM3Dx, a 3D Hall magnetic sensor from SENIS. It is a CMOS-integrated magnetic field sensor that allows the acquisition of all three magnetic field components at the same time and in the same spot. The sensor is equipped with on-chip EPROM to hold initialization, calibration data, and other settings and definitions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the 3D Hall 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3D Hall 4 Click driver.

#### Standard key functions :

- `c3dhall4_cfg_setup` Config Object Initialization function.
```c
void c3dhall4_cfg_setup ( c3dhall4_cfg_t *cfg );
```

- `c3dhall4_init` Initialization function.
```c
err_t c3dhall4_init ( c3dhall4_t *ctx, c3dhall4_cfg_t *cfg );
```

- `c3dhall4_default_cfg` Click Default Configuration function.
```c
err_t c3dhall4_default_cfg ( c3dhall4_t *ctx );
```

#### Example key functions :

- `c3dhall4_read_data` This function reads the measurement status, 3-axes magnetic field data, and the chip internal temperature.
```c
err_t c3dhall4_read_data ( c3dhall4_t *ctx, c3dhall4_data_t *data_out );
```

- `c3dhall4_reg_write` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t c3dhall4_reg_write ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `c3dhall4_reg_read` This function reads a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t c3dhall4_reg_read ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of 3D Hall 4 click board by reading the magnetic field strength from 3 axes and the sensor internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall4_cfg_t c3dhall4_cfg;  /**< Click config object. */

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
    c3dhall4_cfg_setup( &c3dhall4_cfg );
    C3DHALL4_MAP_MIKROBUS( c3dhall4_cfg, MIKROBUS_1 );
    if ( C3DHALL4_OK != c3dhall4_init( &c3dhall4, &c3dhall4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL4_OK != c3dhall4_default_cfg ( &c3dhall4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data from the sensor and displays them on the USB UART once per second.

```c
void application_task ( void )
{
    c3dhall4_data_t data_res;
    if ( C3DHALL4_OK == c3dhall4_read_data ( &c3dhall4, &data_res ) )
    {
        log_printf( &logger, " Status: 0x%.2X\r\n", data_res.status );
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Chip temperature: %.2f degC\r\n\n", data_res.chip_temp );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
