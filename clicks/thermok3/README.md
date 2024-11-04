\mainpage Main Page

---
# Thermo K 3 Click

> Thermo K 3 Click is a compact add-on board that provides accurate temperature measurements with a thermocouple probe. This board features the MAX6675, a cold-junction-compensated K-thermocouple-to-digital converter from Analog Devices. With the versatile type-K probe, this board enables precise temperature measurements of up to +700°C in 12-bit (0.25°C) resolution. This board can measure temperatures as high as +1024°C but with less precision. It features cold-junction compensation sensing and correction and open thermocouple detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermok3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-k-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermo K 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo K 3 Click driver.

#### Standard key functions :

- `thermok3_cfg_setup` Config Object Initialization function.
```c
void thermok3_cfg_setup ( thermok3_cfg_t *cfg );
```

- `thermok3_init` Initialization function.
```c
err_t thermok3_init ( thermok3_t *ctx, thermok3_cfg_t *cfg );
```

#### Example key functions :

- `thermok3_read_data` This function reads a raw data output by using the SPI serial interface.
```c
err_t thermok3_read_data ( thermok3_t *ctx, uint16_t *data_out );
```

- `thermok3_read_temperature` This function reads a raw data output and converts it to temperature in Celsius.
```c
err_t thermok3_read_temperature ( thermok3_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo K 3 Click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermok3_cfg_t thermok3_cfg;  /**< Click config object. */

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
    thermok3_cfg_setup( &thermok3_cfg );
    THERMOK3_MAP_MIKROBUS( thermok3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermok3_init( &thermok3, &thermok3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.
If there's no thermocouple type-K probe inserted an appropriate message will be displayed instead.

```c
void application_task ( void )
{
    float temperature = 0;
    err_t error_flag = thermok3_read_temperature ( &thermok3, &temperature );
    if ( THERMOK3_OK == error_flag )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    else if ( THERMOK3_OPEN_THERMOCOUPLE == error_flag )
    {
        log_printf( &logger, " NO thermocouple input\r\n\n" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoK3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
