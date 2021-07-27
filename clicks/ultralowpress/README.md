\mainpage Main Page

---
# Ultra-Low Press click

> Ultra-Low Press Click is a compact add-on board containing a mountable gage pressure sensor for pneumatic pressure measurements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ultra_low_press_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ultra-low-press-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the UltraLowPress Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UltraLowPress Click driver.

#### Standard key functions :

- `ultralowpress_cfg_setup` Config Object Initialization function.
```c
void ultralowpress_cfg_setup ( ultralowpress_cfg_t *cfg );
```

- `ultralowpress_init` Initialization function.
```c
err_t ultralowpress_init ( ultralowpress_t *ctx, ultralowpress_cfg_t *cfg );
```

#### Example key functions :

- `ultralowpress_ready_to_read` Ready to read.
```c
uint8_t ultralowpress_ready_to_read ( ultralowpress_t *ctx )
```

- `ultralowpress_get_press` Read pressure.
```c
float ultralowpress_get_press ( ultralowpress_t *ctx )
```

- `ultralowpress_get_temp` Read temperature.
```c
float ultralowpress_get_temp ( ultralowpress_t *ctx )
```

## Example Description

> This application reads the serial number of the sensor. If there were 
no errors it continues reading temperature and pressure data from the sensor.

**The demo application is composed of two sections :**

### Application Init

> Initializes host communication(UART and I2C). Reads devices serial number and logs it.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultralowpress_cfg_t ultralowpress_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ultralowpress_cfg_setup( &ultralowpress_cfg );
    ULTRALOWPRESS_MAP_MIKROBUS( ultralowpress_cfg, MIKROBUS_1 );
    err_t init_flag = ultralowpress_init( &ultralowpress, &ultralowpress_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Serial number of sensor read
    uint16_t temp_read = 0;
    uint32_t serial_read = 0;
    init_flag = ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_H, &temp_read );
    serial_read = temp_read;
    serial_read <<= 16;
    init_flag |= ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_L, &temp_read );
    serial_read |= temp_read;
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Read" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " > Serial number: 0x%.8LX\r\n", serial_read );
    }
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks if data is available. When it's available it reads the temperature 
and pressure data from the sensor and logs it.

```c

void application_task ( void ) 
{
    if ( ultralowpress_ready_to_read( &ultralowpress ) )
    {
        ultralowpress_clear_status( &ultralowpress );
        float temp = ultralowpress_get_temp( &ultralowpress );
        float press = ultralowpress_get_press( &ultralowpress );
        log_printf( &logger, " > Temperature[ C ]: %.2f\r\n > Pressure[ Pa ]: %.2f\r\n", temp, press );
    }
    Delay_ms( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UltraLowPress

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
