
---
# Barometer 6 click

> Barometer 6 Click is a compact add-on board used to measure air pressure in a specific environment. This board features the 2SMPB-02E, a high-accuracy digital barometric air pressure sensor with low current consumption from Omron Electronics. The 2SMPB-02E has a calibration parameter for broader pressure and temperature range, features a MEMS chip for sensing air pressure and an IC chip for signal processing. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-6-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 6 Click driver.

#### Standard key functions :

- `barometer6_cfg_setup` Config Object Initialization function.
```c
void barometer6_cfg_setup ( barometer6_cfg_t *cfg );
```

- `barometer6_init` Initialization function.
```c
err_t barometer6_init ( barometer6_t *ctx, barometer6_cfg_t *cfg );
```

- `barometer6_default_cfg` Click Default Configuration function.
```c
err_t barometer6_default_cfg ( barometer6_t *ctx );
```

#### Example key functions :

- `barometer6_hardware_reset` Barometer 6 hardware reset function.
```c
void barometer6_hardware_reset ( barometer6_t *ctx );
```

- `barometer6_set_mode` Barometer 6 set operation mode function.
```c
void barometer6_set_mode ( barometer6_t *ctx, uint8_t mode );
```

- `barometer6_read_temperature_value` Barometer 6 get temperature value function.
```c
void barometer6_read_temperature_value ( barometer6_t *ctx, float *temp_out );
```

## Example Description

> This is an example that demonstrates the use of the Barometer 6 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes SPI or I2C driver, applies default settings and reads Chip ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer6_cfg_t barometer6_cfg;  /**< Click config object. */

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
    barometer6_cfg_setup( &barometer6_cfg );
    BAROMETER6_MAP_MIKROBUS( barometer6_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer6_init( &barometer6, &barometer6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    barometer6_default_cfg ( &barometer6 );
    
    barometer6_read_id( &barometer6, &dev_id );
    if ( BAROMETER6_ID_VALUE != dev_id )
    {
        log_printf( &logger, " Device communication Error " );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) dev_id );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Demonstrates use of Barometer 6 click board by reading pressure and temperature data seconds 
> and logging it on the UART terminal.

```c
void application_task ( void )
{
    float pressure;
    float temperature;
    
    barometer6_read_temperature_value( &barometer6, &temperature );
    barometer6_read_preassure_value( &barometer6, &pressure );
        
    log_printf( &logger, " Temperature : %.2f C    \r\n", temperature );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
