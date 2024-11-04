
---
# Pressure 21 Click

> Pressure 21 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the BMP581, an absolute barometric pressure sensor from Bosch Sensortec. The BMP581 provides a relative accuracy of ±6Pa and typical absolute accuracy of ±30Pa with ultra-low noise, low power consumption, and temperature stability alongside programmable output: temperature-only or both pressure and temperature (pressure-only is not supported). It converts output data into a 24-bit digital value and sends the information via a configurable host interface that supports SPI and I2C serial communications. It measures pressure from 30kPa up to 125kPa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 21 Click driver.

#### Standard key functions :

- `pressure21_cfg_setup` Config Object Initialization function.
```c
void pressure21_cfg_setup ( pressure21_cfg_t *cfg );
```

- `pressure21_init` Initialization function.
```c
err_t pressure21_init ( pressure21_t *ctx, pressure21_cfg_t *cfg );
```

- `pressure21_default_cfg` Click Default Configuration function.
```c
err_t pressure21_default_cfg ( pressure21_t *ctx );
```

#### Example key functions :

- `pressure21_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure21_get_int_pin ( pressure21_t *ctx );
```

- `pressure21_get_sensor_data` This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
```c
err_t pressure21_get_sensor_data ( pressure21_t *ctx, float *pressure, float *temperature );
```

- `pressure21_write_register` This function writes a desired data to the selected register.
```c
err_t pressure21_write_register ( pressure21_t *ctx, uint8_t reg, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of Pressure 21 Click board by reading and displaying the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure21_cfg_t pressure21_cfg;  /**< Click config object. */

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
    pressure21_cfg_setup( &pressure21_cfg );
    PRESSURE21_MAP_MIKROBUS( pressure21_cfg, MIKROBUS_1 );
    err_t init_flag = pressure21_init( &pressure21, &pressure21_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE21_ERROR == pressure21_default_cfg ( &pressure21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt and then reads the pressure and temperature data and displays them on the USB UART approximately once per second.

```c
void application_task ( void )
{
    if ( pressure21_get_int_pin ( &pressure21 ) )
    {
        float pressure, temperature;
        if ( PRESSURE21_OK == pressure21_get_sensor_data ( &pressure21, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mBar\r\n", pressure * PRESSURE21_PA_TO_MBAR );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
