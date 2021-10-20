
---
# Environment 2 click

Environment 2 Click is a compact add-on board containing best-in-class SHT humidity and SGP air-quality sensing solutions from Sensirion. This board features SHT40 and SGP40, a high-accuracy ultra-low-power relative humidity, and a temperature sensor combined with MOx based gas sensor. The SHT40 sensor offers linearized digital output, provides constant temperature accuracy, up to 0.1°C, and shows the best performance when operated within the temperature and humidity range of 5-60°C and 20-80%RH, while the SGP40, a digital gas sensor, features a temperature-controlled micro hot-plate providing a humidity-compensated VOC-based indoor air quality signal. This Click board™ is suitable for indoor air quality and various temperature and humidity-related applications

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/environment2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/environment-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Environment2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Environment2 Click driver.

#### Standard key functions :

- `environment2_cfg_setup` Config Object Initialization function.
```c
void environment2_cfg_setup ( environment2_cfg_t *cfg );
```

- `environment2_init` Initialization function.
```c
ENVIRONMENT2_RETVAL environment2_init ( environment2_t *ctx, environment2_cfg_t *cfg );
```

- `environment2_default_cfg` Click Default Configuration function.
```c
void environment2_default_cfg ( environment2_t *ctx );
```

#### Example key functions :

- `environment2_get_temp_hum` Environment 2 get temperature and relative humidity function.
```c
err_t environment2_get_temp_hum ( environment2_t *ctx, float *humidity, float *temperature );
```

- `environment2_get_air_quality` Environment 2 get air quality data function.
```c
err_t environment2_get_air_quality ( environment2_t *ctx, uint16_t *air_quality );
```

- `environment2_sgp40_measure_test` Environment 2 SGP40 measurement test function.
```c
uint16_t environment2_sgp40_measure_test ( environment2_t *ctx );
```

## Example Description

> This library contains API for Environment 2 Click driver.
> The library contains drivers for measuring air quality,
> temperature and relative humidity.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and triggers the built-in self-test checking,
> set heater off, performs sensors configuration and initialize VOC algorithm.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    environment2_cfg_t environment2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n    Application Init\r\n" );

    // Click initialization.

    environment2_cfg_setup( &environment2_cfg );
    ENVIRONMENT2_MAP_MIKROBUS( environment2_cfg, MIKROBUS_1 );
    err_t init_flag = environment2_init( &environment2, &environment2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_printf( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "    Application Task   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Environment 2 Click  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    if ( environment2_sgp40_measure_test( &environment2 ) == ENVIRONMENT2_SGP40_TEST_PASSED ) {
        log_printf( &logger, "    All tests passed\r\n" );
        log_printf( &logger, "      Successfully\r\n" );
    } else {
        log_printf( &logger, "    One or more tests have\r\n" );
        log_printf( &logger, "     Failed\r\n" );
    }
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 100 );
    
    environment2_sgp40_heater_off( &environment2 );
    Delay_ms( 100 );
    
    environment2_config_sensors( );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Environment 2 Click board.
> Measured and display air quality ( raw data ), 
> temperature ( degrees Celsius ), relative humidity ( % ) and VOC Index.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB UART changes every 2 sec.

```c

void application_task ( void ) {
    environment2_get_temp_hum(  &environment2, &humidity, &temperature );
    Delay_ms( 100 );
    
    log_printf( &logger, " Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    environment2_get_air_quality( &environment2, &air_quality );
    Delay_ms( 100 );
    
    log_printf( &logger, " Air Quality : %d \r\n", air_quality );
    log_printf( &logger, "- - - - - - - - - -  - \r\n" );
    
    environment2_get_voc_index( &environment2, &voc_index );
    Delay_ms( 100 );
    
    log_printf( &logger, " VOC Index   : %d  \r\n", ( uint16_t ) voc_index );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
