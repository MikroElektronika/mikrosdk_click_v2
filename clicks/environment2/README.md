
---
# Environment 2 Click

> [Environment 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4558) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4558&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Environment 2 Click driver.
> The library contains drivers for measuring air quality,
> temperature and relative humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment2

### Example Key Functions

- `environment2_cfg_setup` Config Object Initialization function.
```c
void environment2_cfg_setup ( environment2_cfg_t *cfg );
```

- `environment2_init` Initialization function.
```c
err_t environment2_init ( environment2_t *ctx, environment2_cfg_t *cfg );
```

- `environment2_default_cfg` Click Default Configuration function.
```c
void environment2_default_cfg ( environment2_t *ctx );
```

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

### Application Init

> Initializes I2C driver and triggers the built-in self-test checking,
> set heater off, performs sensors configuration and initialize VOC algorithm.

```c
void application_init ( void ) 
{
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
    Delay_ms ( 100 );
    
    environment2_sgp40_heater_off( &environment2 );
    Delay_ms ( 100 );
    
    environment2_config_sensors( );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Environment 2 Click board.
> Measured and display air quality ( raw data ), 
> temperature ( degrees Celsius ), relative humidity ( % ) and VOC Index.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB UART changes every 2 sec.

```c
void application_task ( void ) 
{
    environment2_get_temp_hum(  &environment2, &humidity, &temperature );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    environment2_get_air_quality( &environment2, &air_quality );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Air Quality : %d \r\n", air_quality );
    log_printf( &logger, "- - - - - - - - - -  - \r\n" );
    
    environment2_get_voc_index( &environment2, &voc_index );
    Delay_ms ( 100 );
    
    log_printf( &logger, " VOC Index   : %d  \r\n", ( uint16_t ) voc_index );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
