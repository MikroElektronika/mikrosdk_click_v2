\mainpage Main Page

---
# Barometer 8 click

> Barometer 8 Click is a compact add-on board used to measure air pressure in a specific environment. This board features the ILPS22QS, an ultra-compact piezoresistive absolute pressure sensor that functions as a digital output barometer from STMicroelectronics. The ILPS22QS comprises a sensing element and an IC chip for signal processing in one package, converts pressure into a 24-bit digital value, and sends the information via a configurable host interface that supports SPI and I2C serial communications. It has a selectable dual full-scale absolute pressure range, up to 1260hPa and 4060hPa, with an accuracy of 0.5hPa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-8-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 8 Click driver.

#### Standard key functions :

- `barometer8_cfg_setup` Config Object Initialization function.
```c
void barometer8_cfg_setup ( barometer8_cfg_t *cfg );
```

- `barometer8_init` Initialization function.
```c
err_t barometer8_init ( barometer8_t *ctx, barometer8_cfg_t *cfg );
```

- `barometer8_default_cfg` Click Default Configuration function.
```c
err_t barometer8_default_cfg ( barometer8_t *ctx );
```

#### Example key functions :

- `barometer8_write_register` This function writes a desired data byte to the selected register.
```c
err_t barometer8_write_register ( barometer8_t *ctx, uint8_t reg, uint8_t data_in );
```

- `barometer8_read_register` This function reads a data byte from the selected register.
```c
err_t barometer8_read_register ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `barometer8_read_data` This function reads the pressure and temperature raw data and converts them to mBar and Celsius.
```c
err_t barometer8_read_data ( barometer8_t *ctx, float *pressure, float *temperature );
```

## Example Description

> This example demonstrates the use of Barometer 8 click board by reading and displaying the pressure and temperature values.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer8_cfg_t barometer8_cfg;  /**< Click config object. */

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
    barometer8_cfg_setup( &barometer8_cfg );
    BAROMETER8_MAP_MIKROBUS( barometer8_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer8_init( &barometer8, &barometer8_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER8_ERROR == barometer8_default_cfg ( &barometer8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the pressure and temperature data on the USB UART every 250ms approximately, as per output data rate (ODR) bits configuration.

```c
void application_task ( void )
{
    float pressure, temperature;
    if ( BAROMETER8_OK == barometer8_read_data ( &barometer8, &pressure, &temperature ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms( 5 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
