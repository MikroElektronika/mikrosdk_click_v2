\mainpage Main Page

---
# Load Cell 7 Click

> Load Cell 7 Click is a compact add-on board representing a weigh scale solution. This board features the ADS1230, a high-precision 20-bit delta-sigma analog-to-digital converter (ADC) with an outstanding noise performance from Texas Instruments. This SPI-configurable ADC (read-only) offers selectable gain and data rate values, supporting a full-scale differential input of ±39mV/±19.5mV and 10SPS/80SPS, respectively. It comes with an onboard low-noise programmable gain amplifier (PGA) and onboard oscillator providing a complete front-end solution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/load-cell-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Load Cell 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Load Cell 7 Click driver.

#### Standard key functions :

- `loadcell7_cfg_setup` Config Object Initialization function.
```c
void loadcell7_cfg_setup ( loadcell7_cfg_t *cfg );
```

- `loadcell7_init` Initialization function.
```c
err_t loadcell7_init ( loadcell7_t *ctx, loadcell7_cfg_t *cfg );
```

#### Example key functions :

- `loadcell7_tare_scale` This function calculates the @b ctx->tare_scale which is the raw ADC readings of the empty container.
```c
err_t loadcell7_tare_scale ( loadcell7_t *ctx );
```

- `loadcell7_calibrate_weight` This function calibrates the weight by calculating the @b ctx->weight_scale for the input calibration weight.
```c
err_t loadcell7_calibrate_weight ( loadcell7_t *ctx, float cal_weight );
```

- `loadcell7_get_weight` This function calculates the weight of the goods in grams.
```c
err_t loadcell7_get_weight ( loadcell7_t *ctx, float *weight );
```

## Example Description

> This example demonstrates the use of Load Cell 7 Click by measuring the weight in grams of the goods from the load cell sensor connected to the Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and reads the tare scale of the empty container, and after that, it calibrates the weight scale with a known calibration weight.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell7_cfg_t loadcell7_cfg;  /**< Click config object. */

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
    loadcell7_cfg_setup( &loadcell7_cfg );
    LOADCELL7_MAP_MIKROBUS( loadcell7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == loadcell7_init( &loadcell7, &loadcell7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove all goods from the scale in the following 5 sec.\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Calculating tare scale...\r\n");
    if ( LOADCELL7_OK == loadcell7_tare_scale ( &loadcell7 ) ) 
    {
        log_printf( &logger, " Tarring complete!\r\n\n");
    }
    else 
    {
        log_error( &logger, " Calculating tare scale.");
        for ( ; ; );
    }
    
    log_printf( &logger, " Place a %ug calibration weight on the scale in the following 5 sec.\r\n", 
                ( uint16_t ) LOADCELL7_CALIBRATION_WEIGHT_G );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Calibrating weight...\r\n");
    if ( LOADCELL7_OK == loadcell7_calibrate_weight ( &loadcell7, LOADCELL7_CALIBRATION_WEIGHT_G ) ) 
    {
        log_printf( &logger, " Calibration complete!\r\n\n");
    }
    else 
    {
        log_error( &logger, " Calibrating weight.");
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the net weight of the goods in grams approximately once per second and logs the results on the USB UART. 

```c
void application_task ( void )
{
    float weight;
    if ( LOADCELL7_OK == loadcell7_get_weight ( &loadcell7, &weight ) ) 
    {
        log_printf(&logger, " Weight : %.2f g\r\n", weight );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
