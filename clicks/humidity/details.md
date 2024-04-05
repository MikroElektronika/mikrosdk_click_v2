
---
# Humidity click

> Humidity Click is a compact add-on board used to sense the amount of water vapor in the air. This board features the HIH-5030, an analog output relative humidity sensor from Honeywell Sensing and Productivity Solutions. The HIH-5031 is a covered, condensation-resistant, integrated circuit humidity sensor that is factory-fitted with a hydrophobic filter allowing usage in many condensing environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/humidity_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/humidity-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Humidity Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Humidity Click driver.

#### Standard key functions :

- `humidity_cfg_setup` Config Object Initialization function.
```c
void humidity_cfg_setup ( humidity_cfg_t *cfg );
```

- `humidity_init` Initialization function.
```c
err_t humidity_init ( humidity_t *ctx, humidity_cfg_t *cfg );
```

#### Example key functions :

- `humidity_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t humidity_read_voltage ( humidity_t *ctx, float *voltage );
```

- `humidity_voltage_to_rh` This function calculates relative humidity percents based on the voltage input.
```c
float humidity_voltage_to_rh ( humidity_t *ctx, float voltage );
```

- `humidity_drv_interface_selection` This function sets a serial driver interface which will be used further in the click driver.
```c
void humidity_drv_interface_selection ( humidity_cfg_t *cfg, humidity_drv_t drv_sel );
```

## Example Description

> This example demonstrates the use of Humidity click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger. The I2C communication interface is selected by default.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    humidity_cfg_t humidity_cfg;  /**< Click config object. */

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
    humidity_cfg_setup( &humidity_cfg );
    HUMIDITY_MAP_MIKROBUS( humidity_cfg, MIKROBUS_1 );
    if ( HUMIDITY_OK != humidity_init( &humidity, &humidity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC voltage and then calculates the relative humidity from it.
> The calculated value of relative humidity in percents is being displayed on the USB UART approximately once per second. 

```c

void application_task ( void )
{
    float voltage = 0;
    if ( HUMIDITY_OK == humidity_read_voltage ( &humidity, &voltage ) )
    {
        log_printf( &logger, " Relative Humidity [%%RH]: %.2f\r\n\n", humidity_voltage_to_rh( &humidity, voltage ) );
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Humidity

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
