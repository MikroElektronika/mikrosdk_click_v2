
---
# Load Cell 8 Click

> [Load Cell 8 Click](https://www.mikroe.com/?pid_product=MIKROE-6060) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6060&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Load Cell 8 Click by measuring the weight
 in grams of the goods from the load cell sensor connected to the Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell8

### Example Key Functions

- `loadcell8_cfg_setup` Config Object Initialization function.
```c
void loadcell8_cfg_setup ( loadcell8_cfg_t *cfg );
```

- `loadcell8_init` Initialization function.
```c
err_t loadcell8_init ( loadcell8_t *ctx, loadcell8_cfg_t *cfg );
```

- `loadcell8_default_cfg` Click Default Configuration function.
```c
err_t loadcell8_default_cfg ( loadcell8_t *ctx );
```

- `loadcell8_read_raw_adc` This function reads raw ADC value by using I2C serial interface.
```c
err_t loadcell8_read_raw_adc ( loadcell8_t *ctx, uint32_t *raw_adc );
```

- `loadcell8_tare_scale` This function calculates the cell_data which is the raw ADC readings of the empty container by using I2C serial interface.
```c
err_t loadcell8_tare_scale ( loadcell8_t *ctx, loadcell8_data_t *cell_data );
```

- `loadcell8_calibration_weight` This function calibrates the weight by calculating the cell_data for the input calibration weight by using I2C serial interface.
```c
err_t loadcell8_calibration_weight ( loadcell8_t *ctx, uint16_t cal_val, loadcell8_data_t *cell_data );
```

### Application Init

> Initializes the driver and reads the tare scale of the empty container, and after
 that, it calibrates the weight scale with a known calibration weight.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell8_cfg_t loadcell8_cfg;  /**< Click config object. */

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
    loadcell8_cfg_setup( &loadcell8_cfg );
    LOADCELL8_MAP_MIKROBUS( loadcell8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == loadcell8_init( &loadcell8, &loadcell8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LOADCELL8_ERROR == loadcell8_default_cfg ( &loadcell8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove all goods from the scale in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Calculating tare scale...\r\n" );
    if ( LOADCELL8_OK == loadcell8_tare_scale( &loadcell8, &cell_data ) )
    {
        log_printf( &logger, " Tarring complete!\r\n\n" );
    }
    else 
    {
        log_error( &logger, " Calculating tare scale." );
        for ( ; ; );
    }

    log_printf( &logger, " Place a %ug calibration weight on the scale in the following 5 sec.\r\n", 
                ( uint16_t ) LOADCELL8_WEIGHT_100G );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Calibrating weight...\r\n" );
    if ( LOADCELL8_OK == loadcell8_calibration_weight( &loadcell8, LOADCELL8_WEIGHT_100G, &cell_data ) ) 
    {
        log_printf( &logger, " Calibration complete!\r\n\n" );
    } 
    else 
    {
        log_error( &logger, " Calibrating weight." );
        for ( ; ; );
    }

    log_printf( &logger, " ___________________\r\n" );
    log_printf( &logger, " Start measurements:\r\n" );
    log_printf( &logger, " ___________________\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> The demo application measures weight and shows the measurement of scales in grams [ g ].
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float weight_g = 0;
    if ( LOADCELL8_OK == loadcell8_get_weight( &loadcell8, &cell_data, &weight_g ) )
    {
        log_printf( &logger, " Weight : %.2f g \r\n", weight_g );
    }
    Delay_ms ( 100 );
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
