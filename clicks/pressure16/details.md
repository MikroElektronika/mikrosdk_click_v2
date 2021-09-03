
---
# Pressure 16 click

Pressure 16 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the WSEN-PADS (2511020213301), a high-precision MEMS-based digital absolute pressure sensor from Würth Elektronik. It has a fully-calibrated 24-bit pressure output to provide accurate atmospheric pressure data with a configurable host interface that supports both I2C and SPI serial communication and with an intelligent on-chip motion-triggered interrupt feature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure_16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-16-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure16 Click driver.

#### Standard key functions :

- `pressure16_cfg_setup` Config Object Initialization function.
```c
void pressure16_cfg_setup ( pressure16_cfg_t *cfg );
```

- `pressure16_init` Initialization function.
```c
PRESSURE16_RETVAL pressure16_init ( pressure16_t *ctx, pressure16_cfg_t *cfg );
```

- `pressure16_default_cfg` Click Default Configuration function.
```c
void pressure16_default_cfg ( pressure16_t *ctx );
```

#### Example key functions :

- `pressure16_get_press_temp` Pressure 16 get pressure and temperature function.
```c
PRESSURE16_RETVAL pressure16_get_press_temp ( pressure16_t *ctx, float *pressure, float *temperature );
```

- `pressure16_set_ctrl_config` Pressure 16 set control configuration function.
```c
PRESSURE16_RETVAL pressure16_set_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t ctrl_cfg_data );
```

- `pressure16_get_device_id` Pressure 16 get device ID function.
```c
PRESSURE16_RETVAL pressure16_get_device_id ( pressure16_t *ctx, uint8_t *dev_id );
```

## Example Description

> This library contains API for the Pressure 16 Click driver.
> This demo application shows an example of pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C and SPI module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as pressure and temperature.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    pressure16_cfg_t pressure16_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    pressure16_cfg_setup( &pressure16_cfg );
    PRESSURE16_MAP_MIKROBUS( pressure16_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure16_init( &pressure16, &pressure16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pressure16_default_cfg ( &pressure16 );
    log_info( &logger, " Application Task " );
    
    pressure16_get_device_id( &pressure16, &device_id );
    if ( device_id == PRESSURE16_DEVICE_ID ) {
        log_info( &logger, " Communication OK" );    
    } else {
        log_info( &logger, " Communication ERROR" ); 
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Start measuring\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of a Pressure 16 Click board™.
> Logs the pressure [ mbar ] and temperature [ degree Celsius ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float pressure, temperature;
    
    pressure16_get_press_temp( &pressure16, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
    log_printf( &logger, " Temperature :  %.2f C \r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" ); 
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
