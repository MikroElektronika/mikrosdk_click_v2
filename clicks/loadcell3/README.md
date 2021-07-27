\mainpage Main Page

---
# Load Cell 3 click

Load Cell 3 Click is a compact add-on board that represents a weigh scale solution. This board features the PGA302, a low-drift, low-noise, programmable signal-conditioner device designed for various resistive bridge-sensing applications from Texas Instruments. It creates 2.5V of bridge excitation and a current output source with programmable current output up to 1mA. Two identical analog front-end (AFE) channels followed by a 16-bit Sigma-Delta ADC are available at the input, where each AFE channel has a dedicated programmable gain amplifier with gain up to 200V/V. It also comes with an on-chip temperature sensor and integrated EEPROM memory for device configuration, calibration, and user data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/load_cell_3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/load-cell-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LoadCell3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LoadCell3 Click driver.

#### Standard key functions :

- `loadcell3_cfg_setup` Config Object Initialization function.
```c
void loadcell3_cfg_setup ( loadcell3_cfg_t *cfg );
```

- `loadcell3_init` Initialization function.
```c
LOADCELL3_RETVAL loadcell3_init ( loadcell3_t *ctx, loadcell3_cfg_t *cfg );
```

- `loadcell3_default_cfg` Click Default Configuration function.
```c
void loadcell3_default_cfg ( loadcell3_t *ctx );
```

#### Example key functions :

- `loadcell3_tare` Load Cell 3 tare the scales function.
```c
void loadcell3_tare ( loadcell3_t *ctx, loadcell3_data_t *cell_data );
```

- `loadcell3_calibration` Load Cell 3 calibration function.
```c
err_t loadcell3_calibration ( loadcell3_t *ctx, uint16_t cal_val, loadcell3_data_t *cell_data );
```

- `loadcell3_get_weight` Load Cell 3 get weight function.
```c
float loadcell3_get_weight ( loadcell3_t *ctx, loadcell3_data_t *cell_data );
```

## Example Description

> This library contains API for the Load Cell 3 click driver.
> The library also includes a function for tare and calibration and weight measurement.
> This demo application shows an example of weight measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, the app sets tare the scale, 
> calibrate scale and start measurements. 

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    loadcell3_cfg_t loadcell3_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    loadcell3_cfg_setup( &loadcell3_cfg );
    LOADCELL3_MAP_MIKROBUS( loadcell3_cfg, MIKROBUS_1 );
    err_t init_flag = loadcell3_init( &loadcell3, &loadcell3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    loadcell3_default_cfg ( &loadcell3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     Tare the scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " >> Remove all object << \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, " please remove all object\r\n" );
    log_printf( &logger, "     from the scale.     \r\n" );
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start tare scales    \r\n" );
    loadcell3_tare ( &loadcell3, &cell_data );
    Delay_ms( 500 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Tarring is complete   \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Calibrate Scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "   >>> Load etalon <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, "place 100g weight etalon \r\n" );
    log_printf( &logger, "    on the scale for     \r\n" );
    log_printf( &logger, "   calibration purpose.  \r\n" );
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );

    if ( loadcell3_calibration ( &loadcell3, LOADCELL3_WEIGHT_100G, &cell_data ) == LOADCELL3_OK ) {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );

        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, " In the following 10 sec \r\n" );
        log_printf( &logger, "   remove 100g weight    \r\n" );
        log_printf( &logger, "   etalon on the scale.  \r\n" );
        Delay_ms( 10000 );
    }
    else {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Calibration  Error    \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Start measurements :  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
}

```

### Application Task

> This is an example that shows the use of a Load Cell 3 click board™.
> The Load Cell 3 click board can be used to measure weight,
> shows the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    weight_val = loadcell3_get_weight( &loadcell3, &cell_data );
    log_printf( &logger, "   Weight : %.2f g\r\n", weight_val );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
