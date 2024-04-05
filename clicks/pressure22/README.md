\mainpage Main Page

---
# Pressure 22 click

> Pressure 22 Click is a compact add-on board that contains a board-mount pressure sensor. 
> This board features the MS5839-02BA, an ultra-compact chlorine-resistant digital pressure and 
> temperature sensor from TE Connectivity. The sensor is a small digital altimeter operating from 300 up to 1200mbar, 
> optimized for applications where chlorine and saline are present. The sensor is filled with gel, 
> which makes it robust, and enables it to work in harsh environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-22-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 22 Click driver.

#### Standard key functions :

- `pressure22_cfg_setup` Config Object Initialization function.
```c
void pressure22_cfg_setup ( pressure22_cfg_t *cfg );
```

- `pressure22_init` Initialization function.
```c
err_t pressure22_init ( pressure22_t *ctx, pressure22_cfg_t *cfg );
```

- `pressure22_default_cfg` Click Default Configuration function.
```c
err_t pressure22_default_cfg ( pressure22_t *ctx );
```

#### Example key functions :

- `pressure22_get_measurement_data` Pressure 22 get the measurement data function.
```c
err_t pressure22_get_measurement_data ( pressure22_t *ctx, float *temperature, float *pressure );
```

- `pressure22_get_calibration_data` Pressure 22 gets the calibration data function.
```c
err_t pressure22_get_calibration_data ( pressure22_t *ctx );
```

- `pressure22_get_adc_data` Pressure 22 gets the ADC data function.
```c
err_t pressure22_get_adc_data ( pressure22_t *ctx, uint32_t *adc );
```

## Example Description

> This library contains API for Pressure 22 Click driver.
> The demo application reads and calculate pressure and temperature data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure22_cfg_t pressure22_cfg;  /**< Click config object. */

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
    pressure22_cfg_setup( &pressure22_cfg );
    PRESSURE22_MAP_MIKROBUS( pressure22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure22_init( &pressure22, &pressure22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE22_ERROR == pressure22_default_cfg ( &pressure22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ____________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Pressure 22 Click board™.
> The demo application reads and displays the Pressure [mBar] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{   
    static float temperature, pressure;
    if ( PRESSURE22_OK == pressure22_get_measurement_data( &pressure22, &temperature, &pressure ) )
    {
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " _______________________ \r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
