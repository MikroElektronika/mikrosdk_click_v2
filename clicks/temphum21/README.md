\mainpage Main Page

---
# TempHum 21 Click

> Temp&Hum 21 Click is a compact add-on board representing temperature and humidity sensing solution. This board features the HIH8130-021-001, a highly accurate, fully-calibrated digital humidity and temperature sensor from Honeywell Sensing and Productivity Solutions. This sensor, characterized by its high accuracy (±2% RH and ±0.5°C over a wide operating temperature range) and high resolution, provides factory-calibrated 14-bit data to the host controller with a configurable I2C interface. It also comes with alarm features with selectable alarm thresholds by an MCU or externally.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 21 Click driver.

#### Standard key functions :

- `temphum21_cfg_setup` Config Object Initialization function.
```c
void temphum21_cfg_setup ( temphum21_cfg_t *cfg );
```

- `temphum21_init` Initialization function.
```c
err_t temphum21_init ( temphum21_t *ctx, temphum21_cfg_t *cfg );
```

#### Example key functions :

- `temphum21_read_measurement` This function requests measurement and waits for a measurement to complete and after that reads temperature in Celsius and relative humidity in percents.
```c
err_t temphum21_read_measurement ( temphum21_t *ctx, float *temperature, float *humidity );
```

- `temphum21_get_all_pin` This function returns the alarm low (ALL) pin logic state.
```c
uint8_t temphum21_get_all_pin ( temphum21_t *ctx );
```

- `temphum21_get_alh_pin` This function returns the alarm high (ALH) pin logic state.
```c
uint8_t temphum21_get_alh_pin ( temphum21_t *ctx );
```

## Example Description

> This example demonstrates the use of Temp & Hum 21 Click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum21_cfg_t temphum21_cfg;  /**< Click config object. */

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
    temphum21_cfg_setup( &temphum21_cfg );
    TEMPHUM21_MAP_MIKROBUS( temphum21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum21_init( &temphum21, &temphum21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM21_ERROR == temphum21_default_cfg ( &temphum21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (Celsius) and humidity (Percents) data and displays the results on the USB UART approximately once per second.
It also checks if any alarm is detected on the humidity measurement.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM21_STATUS_NORMAL_OP == temphum21_read_measurement ( &temphum21, &temperature, &humidity ) )
    {
        if ( temphum21_get_all_pin ( &temphum21 ) )
        {
            log_info ( &logger, " Alarm LOW detected " );
        }
        else if ( temphum21_get_alh_pin ( &temphum21 ) )
        {
            log_info ( &logger, " Alarm HIGH detected " );
        }
        
        log_printf ( &logger, " Temperature: %.2f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%\r\n\n", humidity );
        
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
