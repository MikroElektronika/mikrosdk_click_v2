\mainpage Main Page

---
# Altitude 6 Click

> Altitude 6 Click is a compact add-on board that allows height measurement of an object or point related to sea level or ground level. This board features the MS5611-01BA03, a high-resolution barometric pressure sensor optimized for altimeter applications with an altitude resolution of 10 cm from TE Connectivity. It consists of a high linearity pressure sensor and an ultra-low power 24 bit ΔΣ ADC with internal factory calibrated coefficients. Also, it provides a precise digital 24-bit pressure and temperature value, different operation modes, and a configurable host interface that supports both SPI and I2C serial communication allowing the user to optimize for conversion speed and current consumption. The high accuracy and stability of both pressure and temperature signal of the MS5611-01BA03 make this Click board™ suitable for height sensing in medical and consumer applications, indoor navigation, mobile altimeter or barometer systems, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/altitude6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/altitude-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Altitude6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Altitude6 Click driver.

#### Standard key functions :

- `altitude6_cfg_setup` Config Object Initialization function.
```c
void altitude6_cfg_setup ( altitude6_cfg_t *cfg );
```

- `altitude6_init` Initialization function.
```c
err_t altitude6_init ( altitude6_t *ctx, altitude6_cfg_t *cfg );
```

- `altitude6_default_cfg` Click Default Configuration function.
```c
err_t altitude6_default_cfg ( altitude6_t *ctx );
```

#### Example key functions :

- `altitude6_get_data` Altitude 6 get data function.
```c
err_t altitude6_get_data ( altitude6_t *ctx, float *temperature, float *pressure, float *altitude );
```

- `altitude6_get_raw_data` Altitude 6 get raw data function.
```c
err_t altitude6_get_raw_data ( altitude6_t *ctx, uint32_t *temp_data, uint32_t *press_data );
```

- `altitude6_get_calibration_data` Altitude 6 get calibration data function.
```c
err_t altitude6_get_calibration_data ( altitude6_t *ctx );
```

## Example Description

> This library contains API for Altitude 6 Click driver.
> The demo application reads and calculate 
> temperature, pressure and altitude data.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C or SPI driver and log UART.
> After driver initialization the app set 
> driver interface setup and  default settings.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    altitude6_cfg_t altitude6_cfg;  /**< Click config object. */

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
    altitude6_cfg_setup( &altitude6_cfg );
    altitude6_drv_interface_selection( &altitude6_cfg, ALTITUDE6_DRV_SEL_I2C );
    ALTITUDE6_MAP_MIKROBUS( altitude6_cfg, MIKROBUS_1 );
    err_t init_flag  = altitude6_init( &altitude6, &altitude6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ALTITUDE6_ERROR == altitude6_default_cfg ( &altitude6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Altitude 6 Click board™.
> In this example, display the Altitude ( m ), 
> Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static float temperature;
    static float pressure;
    static float altitude;
    
    if ( altitude6_get_data( &altitude6, &temperature, &pressure, &altitude ) == ALTITUDE6_OK )
    {
        log_printf( &logger, " Altitude    : %.2f m       \r\n", altitude );
        log_printf( &logger, " Pressure    : %.2f mbar    \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C       \r\n", temperature );
        log_printf( &logger, "----------------------------\r\n" );   
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
