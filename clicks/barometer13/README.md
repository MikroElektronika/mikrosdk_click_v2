\mainpage Main Page

---
# Barometer 13 click

> Barometer 13 Click is a compact add-on board that measures air pressure in a specific environment. This board features the BMP585, a barometric pressure sensor from Bosch Sensortec. It has a nominal operating pressure range of 30 up to 125kPa and a temperature operating range from -40 to +85°C. The sensor provides true absolute pressure and temperature readings due to on-chip linearization and temperature compensation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 13 Click driver.

#### Standard key functions :

- `barometer13_cfg_setup` Config Object Initialization function.
```c
void barometer13_cfg_setup ( barometer13_cfg_t *cfg );
```

- `barometer13_init` Initialization function.
```c
err_t barometer13_init ( barometer13_t *ctx, barometer13_cfg_t *cfg );
```

- `barometer13_default_cfg` Click Default Configuration function.
```c
err_t barometer13_default_cfg ( barometer13_t *ctx );
```

#### Example key functions :

- `barometer13_get_measurement` Barometer 13 get the measurement data function.
```c
err_t barometer13_get_measurement ( barometer13_t *ctx, float *pressure, float *temperature );
```

- `barometer13_set_odr` Barometer 13 set the output data rate function.
```c
err_t barometer13_set_odr ( barometer13_t *ctx, uint8_t odr );
```

- `barometer13_set_int_cfg` Barometer 13 set the interrupt config function.
```c
err_t barometer13_set_int_cfg ( barometer13_t *ctx, uint8_t int_en, uint8_t int_od, 
                                                    uint8_t int_pol, uint8_t int_mode );
```

## Example Description

> This example demonstrates the use of  Barometer 13  Click board™ 
> by reading and displaying the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer13_cfg_t barometer13_cfg;  /**< Click config object. */

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
    barometer13_cfg_setup( &barometer13_cfg );
    BAROMETER13_MAP_MIKROBUS( barometer13_cfg, MIKROBUS_1 );
    err_t init_flag = barometer13_init( &barometer13, &barometer13_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER13_ERROR == barometer13_default_cfg ( &barometer13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________ \r\n" );
}
```

### Application Task

> The demo application reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    float pressure = 0, temperature = 0;
    if ( ( BAROMETER13_OK == barometer13_get_measurement( &barometer13, &pressure, &temperature ) ) &&
         barometer13_get_interrupt( &barometer13 ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " ______________________ \r\n" );
        Delay_ms( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
