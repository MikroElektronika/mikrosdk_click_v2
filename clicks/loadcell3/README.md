
---
# Load Cell 3 Click

> [Load Cell 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4658) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4658&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Load Cell 3 Click driver.
> The library also includes a function for tare and calibration and weight measurement.
> This demo application shows an example of weight measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell3

### Example Key Functions

- `loadcell3_cfg_setup` Config Object Initialization function.
```c
void loadcell3_cfg_setup ( loadcell3_cfg_t *cfg );
```

- `loadcell3_init` Initialization function.
```c
err_t loadcell3_init ( loadcell3_t *ctx, loadcell3_cfg_t *cfg );
```

- `loadcell3_default_cfg` Click Default Configuration function.
```c
void loadcell3_default_cfg ( loadcell3_t *ctx );
```

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

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, the app sets tare the scale, 
> calibrate scale and start measurements. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    loadcell3_cfg_t loadcell3_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     Tare the scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " >> Remove all object << \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, " please remove all object\r\n" );
    log_printf( &logger, "     from the scale.     \r\n" );
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

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start tare scales    \r\n" );
    loadcell3_tare ( &loadcell3, &cell_data );
    Delay_ms ( 500 );
    
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

> This is an example that shows the use of a Load Cell 3 Click board&trade;.
> The Load Cell 3 Click board can be used to measure weight,
> shows the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    weight_val = loadcell3_get_weight( &loadcell3, &cell_data );
    log_printf( &logger, "   Weight : %.2f g\r\n", weight_val );
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
