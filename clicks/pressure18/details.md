
---
# Pressure 18 click

> Pressure 18 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the BMP384, a robust barometric pressure sensor delivering market-leading accuracy in a compact package from Bosch Sensortec. The BMP384 provides a relative accuracy of ±9Pa and typical absolute accuracy of ±50Pa with ultra-low noise, low power consumption, and a temperature coefficient offset of ±1Pa/K. It converts output data into a 24-bit digital value and sends the information via a configurable host interface that supports SPI and I2C serial communications. It measures pressure from 300hPa to 1250hPa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 18 Click driver.

#### Standard key functions :

- `pressure18_cfg_setup` Config Object Initialization function.
```c
void pressure18_cfg_setup ( pressure18_cfg_t *cfg );
```

- `pressure18_init` Initialization function.
```c
err_t pressure18_init ( pressure18_t *ctx, pressure18_cfg_t *cfg );
```

- `pressure18_default_cfg` Click Default Configuration function.
```c
err_t pressure18_default_cfg ( pressure18_t *ctx );
```

#### Example key functions :

- `pressure18_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure18_get_int_pin ( pressure18_t *ctx );
```

- `pressure18_read_data` This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
```c
err_t pressure18_read_data ( pressure18_t *ctx, float *pressure, float *temperature );
```

- `pressure18_soft_reset` This function performs the software reset feature.
```c
err_t pressure18_soft_reset ( pressure18_t *ctx );
```

## Example Description

> This example demonstrates the use of Pressure 18 click board by reading and displaying the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure18_cfg_t pressure18_cfg;  /**< Click config object. */

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
    pressure18_cfg_setup( &pressure18_cfg );
    PRESSURE18_MAP_MIKROBUS( pressure18_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure18_init( &pressure18, &pressure18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE18_ERROR == pressure18_default_cfg ( &pressure18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt and then reads the pressure and temperature data and displays them on the USB UART every 320ms approximately.

```c
void application_task ( void )
{
    if ( pressure18_get_int_pin ( &pressure18 ) )
    {
        float pressure, temperature;
        if ( PRESSURE18_OK == pressure18_read_data ( &pressure18, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure * PRESSURE18_PA_TO_MBAR );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
