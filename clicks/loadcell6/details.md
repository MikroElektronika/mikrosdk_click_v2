
---
# Load Cell 6 click

> Load Cell 6 Click is a compact add-on board representing a weigh scale solution. This board features the MAX11270, a high-performance 24-bit delta-sigma ADC that achieves excellent 130dB SNR while dissipating an ultra-low 10mW from Maxim Integrated, now part of Analog Devices. This SPI-configurable ADC sample rates up to 64ksps allow precision DC and AC measurements, with integral non-linearity guaranteed to 4ppm maximum. The MAX11270 offers a 6.5nV/√Hz noise programmable gain amplifier with gain settings between 1x to 128x. Optional buffers are also included to isolate the signal inputs from the switched capacitor sampling network, which allows the MAX11270 to be used with high-impedance sources without compromising the available dynamic range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/load-cell-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the LoadCell6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LoadCell6 Click driver.

#### Standard key functions :

- `loadcell6_cfg_setup` Config Object Initialization function.
```c
void loadcell6_cfg_setup ( loadcell6_cfg_t *cfg );
```

- `loadcell6_init` Initialization function.
```c
err_t loadcell6_init ( loadcell6_t *ctx, loadcell6_cfg_t *cfg );
```

- `loadcell6_default_cfg` Click Default Configuration function.
```c
err_t loadcell6_default_cfg ( loadcell6_t *ctx );
```

#### Example key functions :

- `loadcell6_get_weight` Load Cell 6 get weight function.
```c
err_t loadcell6_get_weight ( loadcell6_t *ctx, loadcell6_data_t *cell_data, float *weight_g );
```

- `loadcell6_calibration` Load Cell 6 calibration function.
```c
err_t loadcell6_calibration ( loadcell6_t *ctx, uint16_t cal_val, loadcell6_data_t *cell_data );
```

- `loadcell6_tare` Load Cell 6 tare the scales function.
```c
err_t loadcell6_tare ( loadcell6_t *ctx, loadcell6_data_t *cell_data );
```

## Example Description

> This library contains API for the Load Cell 6 Click driver.
> The library initializes and defines the SPI bus drivers to read status and ADC data. 
> The library also includes a function for tare, calibration and weight measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, app performs the power on
> sets tare the scale, calibrate scale and start measurements.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell6_cfg_t loadcell6_cfg;  /**< Click config object. */

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
    loadcell6_cfg_setup( &loadcell6_cfg );
    LOADCELL6_MAP_MIKROBUS( loadcell6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == loadcell6_init( &loadcell6, &loadcell6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LOADCELL6_ERROR == loadcell6_default_cfg( &loadcell6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
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
    loadcell6_tare( &loadcell6, &cell_data );
    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 200g weight etalon\r\n");
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

    if ( LOADCELL6_OK == loadcell6_calibration( &loadcell6, LOADCELL6_WEIGHT_200G, &cell_data )  ) 
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 5 sec  \r\n");
        log_printf( &logger, "    remove 200g weight   \r\n");
        log_printf( &logger, "   etalon on the scale.  \r\n");
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else 
    {
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

> This is an example that demonstrates the use of the Load Cell 6 click board™.
> The Load Cell 6 click board™ can be used to measure weight and
> shows the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static float weight_g;
    
    if ( LOADCELL6_OK == loadcell6_get_weight( &loadcell6, &cell_data, &weight_g ) )
    {
        log_printf(&logger, "   Weight : %.2f g\r\n", weight_g ); 
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
