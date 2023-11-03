\mainpage Main Page

---
# PRESS click

> PRESS Click is a compact add-on board that contains a board-mount pressure sensor. This board features the ILPS28QSW, an absolute digital output barometer from STMicroelectronics. It is a dual full-scale sensor with a measuring range of 260 up to 4060hPa. In addition, it comes with a Qvar detection ability, which is an electric charge variation detection and is available on two pins.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/press_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/press-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the PRESS Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PRESS Click driver.

#### Standard key functions :

- `press_cfg_setup` Config Object Initialization function.
```c
void press_cfg_setup ( press_cfg_t *cfg );
```

- `press_init` Initialization function.
```c
err_t press_init ( press_t *ctx, press_cfg_t *cfg );
```

- `press_default_cfg` Click Default Configuration function.
```c
err_t press_default_cfg ( press_t *ctx );
```

#### Example key functions :

- `press_get_measurement_data` PRESS gets the measurement data function.
```c
err_t press_get_measurement_data ( press_t *ctx, float *pressure, float *temperature );
```

- `press_get_ah_qvar_data` PRESS gets the AH/Qvar data function.
```c
err_t press_get_ah_qvar_data ( press_t *ctx, float *ah_qvar );
```

- `press_sw_reset` PRESS software reset function.
```c
err_t press_sw_reset ( press_t *ctx );

```

## Example Description

> This example demonstrates the use of PRESS Click board™ by reading and displaying
> the pressure, temperature and Qvar measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    press_cfg_t press_cfg;  /**< Click config object. */

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
    press_cfg_setup( &press_cfg );
    PRESS_MAP_MIKROBUS( press_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == press_init( &press, &press_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESS_ERROR == press_default_cfg ( &press ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    log_printf( &logger, " Pressure and Temperature\r\n" );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    if ( PRESS_OK == press_config_ah_qvar( &press, PRESS_AH_QVAR_ENABLE ) )
    {
        log_printf( &logger, " Swipe sensing\r\n" );
    }
    else
    {
        log_error( &logger, " Qvar configuration.\r\n" );
        for ( ; ; );
    }
#endif
    log_printf( &logger, " ______________________ \r\n" );
    Delay_ms( 1000 );
}
```

### Application Task

> The demo application shows the module working depending on the example mode:
> - EXAMPLE_MODE_PRESS_TEMP: Reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
> - EXAMPLE_MODE_SWIPE_SENSING: Detect a touch or a swipe.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    example_pressure_temperature( );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    example_swipe_sensing( );
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PRESS

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
