
---
# Piezo Accel click

Piezo Accel Click is a compact add-on board containing an acceleration sensor based on PE technology. This board features the 820M1-0025, a piezoelectric accelerometer designed for embedded monitoring and preventive maintenance applications from TE Connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/piezo_accel_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/piezo-accel-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the PiezoAccel Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PiezoAccel Click driver.

#### Standard key functions :

- `piezoaccel_cfg_setup` Config Object Initialization function.
```c
void piezoaccel_cfg_setup ( piezoaccel_cfg_t *cfg );
```

- `piezoaccel_init` Initialization function.
```c
PIEZOACCEL_RETVAL piezoaccel_init ( piezoaccel_t *ctx, piezoaccel_cfg_t *cfg );
```

- `piezoaccel_default_cfg` Click Default Configuration function.
```c
void piezoaccel_default_cfg ( piezoaccel_t *ctx );
```

#### Example key functions :

- `piezoaccel_adc_raw_read` Piezo Accel read raw adc function.
```c
uint16_t piezoaccel_adc_raw_read ( piezoaccel_t *ctx );
```

- `piezoaccel_adc_voltage_read` Piezo Accel read adc converted to voltage function.
```c
float piezoaccel_adc_voltage_read ( piezoaccel_t *ctx );
```

- `piezoaccel_g_unit_read` Piezo Accel read force of acceleration function.
```c
float piezoaccel_g_unit_read ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data );
```

## Example Description

> This application demonstrates the performance of Piezo Accel click board.

**The demo application is composed of two sections :**

### Application Init

>  The initialization of UART LOG and SPI click drivers.
Additionally, a default config is performed for
"out of the box" Piezo Accel click settings.
Calibration is optional and is used to correct
the power supply offset of the sensor.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    piezoaccel_cfg_t piezoaccel_cfg;    /**< Click config object. */

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

    piezoaccel_cfg_setup( &piezoaccel_cfg );
    PIEZOACCEL_MAP_MIKROBUS( piezoaccel_cfg, MIKROBUS_1 );
    err_t init_flag = piezoaccel_init( &piezoaccel, &piezoaccel_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    piezoaccel_default_cfg( &piezoaccel, &setup_cfg_data );
    log_info( &logger, " Application Task " );
    Delay_ms ( 200 );
}

```

### Application Task

>  The ADC is constantly read and converted to a
g-force acceleration unit. Data is sent via LOG
every 20 ms and works on MikroPlot for graphical
representation of the sensor results.

```c

void application_task ( void ) {
    float read_val;
    
    read_val = piezoaccel_g_unit_read( &piezoaccel, &setup_cfg_data );
    log_printf( &logger, "%.2f,%.2f\r\n", read_val, time_var );
    time_var += time_incr;
    Delay_ms ( time_incr );
}

```

## Note

>  This demo app is intended to be used with MikroPlot data
visualization tool for clear understanding of the results.
https://www.mikroe.com/mikroplot-data-visualization-tool

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PiezoAccel

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
