
---
# PHT click

PHT Click is a compact add-on board that contains a PHT combo sensor. This board features the MS8607, a digital combination sensor providing 3 environmental measurements all-in-one: pressure, humidity, and temperature from TE Connectivity. This sensor is based on leading MEMS technologies, provides factory-calibrated PHT data available over an I2C serial interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pht_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pht-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the PHT Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PHT Click driver.

#### Standard key functions :

- `pht_cfg_setup` Config Object Initialization function.
```c
void pht_cfg_setup ( pht_cfg_t *cfg );
```

- `pht_init` Initialization function.
```c
err_t pht_init ( pht_t *ctx, pht_cfg_t *cfg );
```

#### Example key functions :

- `pht_set_ratio` Set Ratio function.
```c
uint8_t pht_set_ratio ( pht_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );
```

- `pht_get_temperature_pressure` Get temperature and pressure function.
```c
void pht_get_temperature_pressure ( pht_t *ctx, float *temperature, float *pressure );
```

- `pht_get_relative_humidity` Get humidity function.
```c
void pht_get_relative_humidity ( pht_t *ctx, float *humidity );
```

## Example Description

> This is an example that demonstrates the use of the PHT Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C,  performs the device reset and determines the oversampling ratio,  also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
      /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    pht_cfg_setup( &pht_cfg );
    PHT_MAP_MIKROBUS( pht_cfg, MIKROBUS_1 );
    err_t init_flag = pht_init( &pht, &pht_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "--------------------------- \r\n " );
    log_printf( &logger, " Device reset \r\n" );
    pht_reset( &pht );
    Delay_ms( 100 );
    log_printf( &logger, "--------------------------- \r\n " );
    log_printf( &logger, " Set Oversampling Ratio \r\n" );
    pht_set_ratio( &pht, PHT_PT_CMD_RATIO_2048, PHT_PT_CMD_RATIO_2048);
    Delay_ms( 100 );
    log_printf( &logger, "--------------------------- \r\n " );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------- \r\n " );
}

```

### Application Task

> PHT Click board can be used to measure Pressure, Temperature  and Relative Humidity. All data logs write on USB uart changes every 3 sec.

```c

void application_task ( void ) {
    pht_get_temperature_pressure( &pht, &temperature, &pressure );
    Delay_ms( 10 );
    pht_get_relative_humidity( &pht, &humidity );
    Delay_ms( 10 );
    
    log_printf( &logger, " Preassure   : %.2f mbar \r\n ", pressure );
    log_printf( &logger, " Humidity    : %.2f %% \r\n ", humidity );
    log_printf( &logger, " Temperature : %.2f C \r\n ", temperature );
    log_printf( &logger, "--------------------------- \r\n " );
    Delay_ms( 3000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PHT

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
