\mainpage Main Page

---
# Accel 15 click

Accel 15 Click is a compact add-on board that contains a longevity acceleration sensor. This board features the BMA490L, a high-performance 16-bit digital triaxial acceleration sensor with extended availability of up to ten years from Bosch Sensortech. It allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, ±8g, and ±16g in three axes with a configurable host interface that supports both I2C and SPI serial communication and with intelligent on-chip motion-triggered interrupt features. Intelligent signal processing and evaluation in the accelerometer ASIC enables advanced gesture recognition for numerous industrial IoT applications where low power consumption is vital. This Click board™ is suitable for home appliances, power tools, and other industrial products whose lifetime is essential.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-15-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel15 Click driver.

#### Standard key functions :

- `accel15_cfg_setup` Config Object Initialization function.
```c
void accel15_cfg_setup ( accel15_cfg_t *cfg );
```

- `accel15_init` Initialization function.
```c
ACCEL15_RETVAL accel15_init ( accel15_t *ctx, accel15_cfg_t *cfg );
```

- `accel15_default_cfg` Click Default Configuration function.
```c
void accel15_default_cfg ( accel15_t *ctx );
```

#### Example key functions :

- `accel15_get_axis_data` Accel 15 get accelerometer axis function.
```c
void accel15_get_axis_data ( accel15_t *ctx, accel15_axis_t *axis );
```

- `accel15_generic_write` Accel 15 data writing function.
```c
err_t accel15_generic_write ( accel15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `accel15_generic_read` Accel 15 data reading function.
```c
err_t accel15_generic_read ( accel15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

## Example Description

> This library contains API for Accel 15 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data. 

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app checks communication, 
> sensor ID, and then executes a default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel15_cfg_t accel15_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_printf( &logger, "     Application Init    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    // Click initialization.

    accel15_cfg_setup( &accel15_cfg );
    ACCEL15_MAP_MIKROBUS( accel15_cfg, MIKROBUS_1 );
    err_t init_flag  = accel15_init( &accel15, &accel15_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( accel15_check_id( &accel15 ) == 0 ) {
        log_printf( &logger, "     Communication OK    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    accel15_default_cfg ( &accel15 );
    log_printf( &logger, "     Application Task    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 1 sec.

```c

void application_task ( void ) {
    if ( accel15_get_int_1( &accel15 ) == ACCEL15_DRDY ) {
        accel15_get_axis_data( &accel15, &axis );

        log_printf( &logger, "\tX : %5d \r\n", axis.x );
        log_printf( &logger, "\tY : %5d \r\n", axis.y );
        log_printf( &logger, "\tZ : %5d \r\n", axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        
        Delay_ms( 1000 );    
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
