\mainpage Main Page

---
# Pressure 15 Click

> Pressure 15 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the LPS27HHW, an ultra-compact piezoresistive absolute pressure sensor that functions as a digital output barometer from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure_15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-15-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure15 Click driver.

#### Standard key functions :

- `pressure15_cfg_setup` Config Object Initialization function.
```c
void pressure15_cfg_setup ( pressure15_cfg_t *cfg );
```

- `pressure15_init` Initialization function.
```c
err_t pressure15_init ( pressure15_t *ctx, pressure15_cfg_t *cfg );
```

- `pressure15_default_cfg` Click Default Configuration function.
```c
err_t pressure15_default_cfg ( pressure15_t *ctx );
```

#### Example key functions :

- `pressure15_get_int` Get interrupt pin state.
```c
uint8_t pressure15_get_int ( pressure15_t *ctx );
```

- `pressure15_get_pressure` Get pressure data.
```c
err_t pressure15_get_pressure ( pressure15_t *ctx, float *pressure );
```

- `pressure15_get_temperature` Get temperature data.
```c
err_t pressure15_get_temperature ( pressure15_t *ctx, float *temperature );
```

## Example Description

> This application example showcases the ability of the device to
read temperature and pressure data.

**The demo application is composed of two sections :**

### Application Init

> Initialization of hosts communication modules (UART, SPI/I2C) 
and interrupt pin. Checks device ID and sets the default configuration
that enables interrupt on new data.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure15_cfg_t pressure15_cfg;  /**< Click config object. */

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
    pressure15_cfg_setup( &pressure15_cfg );
    PRESSURE15_MAP_MIKROBUS( pressure15_cfg, MIKROBUS_1 );
    err_t init_flag = pressure15_init( &pressure15, &pressure15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t whoami = 0;
    init_flag = pressure15_generic_read( &pressure15, PRESSURE15_REG_WHO_AM_I, &whoami, 1 );
    if ( !init_flag && ( PRESSURE15_ID == whoami ) )
    {
        log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )whoami );
    }
    else
    {
        log_error( &logger, " ID\r\n");
    }
    
    pressure15_default_cfg ( &pressure15 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks if an interrupt occurred. If occurred reads new pressure and temperature
data in hPa and degC respectively.

```c

void application_task ( void ) 
{
    if ( pressure15_get_int( &pressure15 ) )
    {
        float temperature, pressure;
        
        pressure15_get_pressure( &pressure15, &pressure );
        log_printf( &logger, " > Pressure[hPa]: %.2f\r\n", pressure );
        
        pressure15_get_temperature( &pressure15, &temperature );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "***************************************\r\n" );
        Delay_ms ( 200 );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
