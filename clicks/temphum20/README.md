\mainpage Main Page

---
# TempHum 20 Click

> Temp&Hum 20 Click is a compact add-on board that represents temperature and humidity sensing solution. This board features the CC2D23, a highly accurate, fully-calibrated relative humidity and temperature sensor from Amphenol. This sensor, characterized by its high accuracy (±2% from 20% to 80%RH (±3% over entire humidity range)) and high resolution, provides factory-calibrated 14-bit data to the host controller with a configurable I2C interface. It also comes with alarm features for preset control at a minimum and maximum humidity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum20_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum20 Click driver.

#### Standard key functions :

- `temphum20_cfg_setup` Config Object Initialization function.
```c
void temphum20_cfg_setup ( temphum20_cfg_t *cfg );
```

- `temphum20_init` Initialization function.
```c
err_t temphum20_init ( temphum20_t *ctx, temphum20_cfg_t *cfg );
```

- `temphum20_default_cfg` Click Default Configuration function.
```c
err_t temphum20_default_cfg ( temphum20_t *ctx );
```

#### Example key functions :

- `temphum20_write_command` This function writes a desired command data to the selected command byte.
```c
err_t temphum20_write_command ( temphum20_t *ctx, uint8_t cmd_byte, uint16_t cmd_data );
```

- `temphum20_get_measurement` This function waits for the data to be ready, and then reads the temperature and humidity data and converts them to Celsius and Percents, respectively.
```c
err_t temphum20_get_measurement ( temphum20_t *ctx, float *temp, float *hum );
```

- `temphum20_set_operating_mode` This function sets the device operating mode.
```c
err_t temphum20_set_operating_mode ( temphum20_t *ctx, uint8_t op_mode );
```

## Example Description

> This example demonstrates the use of Temp & Hum 20 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the Click default configuration which resets the device and sets it to normal operating mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum20_cfg_t temphum20_cfg;  /**< Click config object. */

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
    temphum20_cfg_setup( &temphum20_cfg );
    TEMPHUM20_MAP_MIKROBUS( temphum20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum20_init( &temphum20, &temphum20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM20_ERROR == temphum20_default_cfg ( &temphum20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> When the new data is ready, this function reads the temperature and humidity data and displays the results on the USB UART.

```c

void application_task ( void )
{
    float humidity, temperature = 0;
    
    if ( TEMPHUM20_OK == temphum20_get_measurement ( &temphum20, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.3f %%\r\n\n", humidity );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
