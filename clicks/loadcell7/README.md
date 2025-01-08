
---
# Load Cell 7 Click

> [Load Cell 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5276) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5276&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Load Cell 7 Click by measuring the weight in grams of the goods from the load cell sensor connected to the Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell7

### Example Key Functions

- `loadcell7_cfg_setup` Config Object Initialization function.
```c
void loadcell7_cfg_setup ( loadcell7_cfg_t *cfg );
```

- `loadcell7_init` Initialization function.
```c
err_t loadcell7_init ( loadcell7_t *ctx, loadcell7_cfg_t *cfg );
```

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
