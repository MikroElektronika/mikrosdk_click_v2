
---
# Load Cell 5 Click

Load Cell 5 Click is a compact add-on board that represents a weigh scale solution. This board features the AD7780, a pin-programmable, low power, 24-bit sigma-delta ΣΔ ADC from Analog Devices. It interfaces directly to the load cell, where the low-level signal from the load cell is amplified by the AD7780’s internal low noise programmable gain amplifier programmed to operate with a gain of 128 or 1. It also has a power-down mode allowing the user to switch off the power to the bridge sensor and power-down the AD7780 when not converting, increasing the product battery life. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/load-cell-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the LoadCell5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LoadCell5 Click driver.

#### Standard key functions :

- `loadcell5_cfg_setup` Config Object Initialization function.
```c
void loadcell5_cfg_setup ( loadcell5_cfg_t *cfg );
```

- `loadcell5_init` Initialization function.
```c
LOADCELL5_RETVAL loadcell5_init ( loadcell5_t *ctx, loadcell5_cfg_t *cfg );
```

- `loadcell5_default_cfg` Click Default Configuration function.
```c
void loadcell5_default_cfg ( loadcell5_t *ctx );
```

#### Example key functions :

- `loadcell5_set_power_mode` Load Cell 5 set power mode function.
```c
err_t loadcell5_set_power_mode ( loadcell5_t *ctx, uint8_t pwr_mode );
```

- `loadcell5_read_adc` Load Cell 5 reading ADC data function.
```c
uint32_t loadcell5_read_adc ( loadcell5_t *ctx );
```

- `loadcell5_get_weight` Load Cell 5 get weight function.
```c
float loadcell5_get_weight ( loadcell5_t *ctx, loadcell5_data_t *cell_data );
```

## Example Description

> This library contains API for Load Cell 5 Click driver.
> The library initializes and defines the SPI bus drivers to read status and ADC data. 
> The library also includes a function for tare, calibration and weight measurement.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module, log UART, and additional pins
> and performs the power on. Sets tare the scale, calibrate scale 
> and start measurements. 

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell5_cfg_t loadcell5_cfg;  /**< Click config object. */

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

    loadcell5_cfg_setup( &loadcell5_cfg );
    LOADCELL5_MAP_MIKROBUS( loadcell5_cfg, MIKROBUS_1 );
    err_t init_flag  = loadcell5_init( &loadcell5, &loadcell5_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    loadcell5_default_cfg ( &loadcell5 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 500 ); 
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Tare the scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " >> Remove all object << \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, " please remove all object\r\n");
    log_printf( &logger, "     from the scale.     \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start tare scales    \r\n");
    loadcell5_tare ( &loadcell5, &cell_data );
    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 100g weight etalon\r\n");
    log_printf( &logger, "    on the scale for     \r\n");
    log_printf( &logger, "   calibration purpose.  \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");

    if ( loadcell5_calibration ( &loadcell5, LOADCELL5_WEIGHT_100G, &cell_data ) == LOADCELL5_OK ) {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");

        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 10 sec \r\n");
        log_printf( &logger, "   remove 100g weight   \r\n");
        log_printf( &logger, "   etalon on the scale.  \r\n");
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Start measurements :  \r\n");
    log_printf( &logger, "-------------------------\r\n");
}

```

### Application Task

> This is an example that demonstrates the use of the Load Cell 5 Click board.
> The Load Cell 5 Click board can be used to measure weight,
> shows the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {   
    weight_val = loadcell5_get_weight( &loadcell5, &cell_data );

    log_printf(&logger, "   Weight : %.2f g\r\n", weight_val );

    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
 