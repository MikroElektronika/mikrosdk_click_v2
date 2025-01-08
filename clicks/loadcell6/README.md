
---
# Load Cell 6 Click

> [Load Cell 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4940) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4940&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Load Cell 6 Click driver.
> The library initializes and defines the SPI bus drivers to read status and ADC data. 
> The library also includes a function for tare, calibration and weight measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell6

### Example Key Functions

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

> This is an example that demonstrates the use of the Load Cell 6 Click board&trade;.
> The Load Cell 6 Click board&trade; can be used to measure weight and
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
