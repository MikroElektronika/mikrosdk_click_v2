
---
# Temp&Hum 17 Click

Temp&Hum 17 Click is a compact add-on board that represents temperature and humidity sensing solutions. This board features the HS3001, a highly accurate, fully calibrated relative humidity and temperature sensor from Renesas. It features proprietary sensor-level protection, ensuring high reliability and long-term stability. Integrated calibration and temperature-compensation logic provides fully corrected RH and temperature values via standard I2C output. No user calibration of the output data is required.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-17-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum17 Click driver.

#### Standard key functions :

- `temphum17_cfg_setup` Config Object Initialization function.
```c
void temphum17_cfg_setup ( temphum17_cfg_t *cfg );
```

- `temphum17_init` Initialization function.
```c
TEMPHUM17_RETVAL temphum17_init ( temphum17_t *ctx, temphum17_cfg_t *cfg );
```

- `temphum17_default_cfg` Click Default Configuration function.
```c
void temphum17_default_cfg ( temphum17_t *ctx );
```

#### Example key functions :

- `temphum17_wake_up` Temp&Hum 17 wake up function.
```c
TEMPHUM17_RETVAL temphum17_wake_up ( temphum17_t *ctx );
```

- `temphum17_get_raw_data` Temp&Hum 17 get raw data function.
```c
TEMPHUM17_RETVAL temphum17_get_raw_data ( temphum17_t *ctx, uint8_t resolution, int16_t *temp, uint16_t *hum, uint8_t *status );
```

- `temphum17_get_temp_hum` Temp&Hum 17 get temperature and humidity function.
```c
TEMPHUM17_RETVAL temphum17_get_temp_hum ( temphum17_t *ctx, uint8_t resolution, float *temperature, float *humidity );
```

## Example Description

> This library contains API for the Temp&Hum 17 Click driver.
> This demo application shows an example of 
> relative humidity and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as temperature and relative humidity.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;             /**< Logger config object. */
    temphum17_cfg_t temphum17_cfg;  /**< Click config object. */

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

    temphum17_cfg_setup( &temphum17_cfg );
    TEMPHUM17_MAP_MIKROBUS( temphum17_cfg, MIKROBUS_1 );
    err_t init_flag = temphum17_init( &temphum17, &temphum17_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum17_default_cfg ( &temphum17 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Temp&Hum 17 Click board™.
> Logs the temperature [ degree Celsius ] and relative humidity [ % ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    if ( temphum17_get_temp_hum( &temphum17, TEMPHUM17_RESOLUTION_14_BITS, &temperature, &humidity ) == TEMPHUM17_STATUS_VALID_DATA ) {
        log_printf( &logger, "  Temperature : %.02f C\r\n  Humidity    : %.02f %%\r\n", temperature, humidity );
    } else {
        log_printf( &logger, "     Measurement Error\r\n\tStale Data\r\n" );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );  
}

```

## Note

> Sequence of commands needed to enter the programming mode, 
which must be sent within 10ms after applying power to the sensor.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
