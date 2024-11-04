
---
# Magneto 6 Click

> Magneto 6 Click features low power three dimensional Hall effect sensor, TLI493D-A2B6, designed for magnetic sensing applications. It measures the magnetic field in X, Y, and Z direction. Each X, Y and Z Hall probe is connected sequentially to a multiplexer, which is then connected to an Analog to Digital Converter (ADC). Optional, the temperature can be determined as well after the three Hall channels. The data measurement is provided in digital format to the microcontroller over the standard I2C interface. Some of the benefits of this Click board™ are wide application range addressable due to high flexibility and component reduction due to the 3D magnetic measurement principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/magneto-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto 6 Click driver.

#### Standard key functions :

- `magneto6_cfg_setup` Config Object Initialization function.
```c
void magneto6_cfg_setup ( magneto6_cfg_t *cfg );
```

- `magneto6_init` Initialization function.
```c
err_t magneto6_init ( magneto6_t *ctx, magneto6_cfg_t *cfg );
```

- `magneto6_default_cfg` Click Default Configuration function.
```c
err_t magneto6_default_cfg ( magneto6_t *ctx );
```

#### Example key functions :

- `magneto6_read_data` This function reads the measurements of the 3-axes magnetic field sensor in mT and the temperature sensor in degrees Celsius.
```c
err_t magneto6_read_data ( magneto6_t *ctx, magneto6_data_t *data_out );
```

- `magneto6_read_reg` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t magneto6_read_reg ( magneto6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `magneto6_write_reg` This function writes a data byte to the selected register by using I2C serial interface.
```c
err_t magneto6_write_reg ( magneto6_t *ctx, uint8_t reg, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of Magneto 6 Click board by reading the magnetic field strength from 3 axes as well as the ambient temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto6_cfg_t magneto6_cfg;  /**< Click config object. */

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
    magneto6_cfg_setup( &magneto6_cfg );
    MAGNETO6_MAP_MIKROBUS( magneto6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto6_init( &magneto6, &magneto6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO6_ERROR == magneto6_default_cfg ( &magneto6 ) )
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
    magneto6_data_t data_res;
    if ( MAGNETO6_OK == magneto6_read_data ( &magneto6, &data_res ) )
    {
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", data_res.temperature );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
