
---
# Load Cell 2 Click

> [Load Cell 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4047) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4047&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> Load Cell 2 Click is a weight measurement Click 
> which utilizes a load cell element, 
> in order to precisely measure the weight of an object.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell2

### Example Key Functions

- `loadcell2_cfg_setup` Config Object Initialization function. 
```c
void loadcell2_cfg_setup ( loadcell2_cfg_t *cfg );
``` 
 
- `loadcell2_init` Initialization function. 
```c
err_t loadcell2_init ( loadcell2_t *ctx, loadcell2_cfg_t *cfg );
```

- `loadcell2_default_cfg` Click Default Configuration function. 
```c
void loadcell2_default_cfg ( loadcell2_t *ctx );
```

- `loadcell2_get_weight` Get weight function. 
```c
float loadcell2_get_weight ( loadcell2_t *ctx, loadcell2_data_t *cell_data );
```
 
- `loadcell2_get_result` Get results function. 
```c
uint32_t loadcell2_get_result ( loadcell2_t *ctx );
```

- `loadcell2_calibration` Calibration function. 
```c
uint8_t loadcell2_calibration ( loadcell2_t *ctx, uint16_t cal_val, loadcell2_data_t *cell_data );
```

### Application Init

>
> Initializes I2C driver and performs the device reset, 
> and performs the device reset, set power on and default configuration.
> Sets tare the scale, calibrate scale and start measurements.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell2_cfg_t cfg;

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
    log_printf( &logger, "  - Application Init -   \r\n" );

    //  Click initialization.

    loadcell2_cfg_setup( &cfg );
    LOADCELL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell2_init( &loadcell2, &cfg );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Load cell Click     \r\n");
    log_printf( &logger, "-------------------------\r\n");
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Reset all registers   \r\n");
    loadcell2_reset( &loadcell2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "        Power On         \r\n");
    loadcell2_power_on( &loadcell2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Set default config.   \r\n");
    loadcell2_default_cfg( &loadcell2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "      Calibrate AFE      \r\n");
    loadcell2_calibrate_afe( &loadcell2 );
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
    loadcell2_tare ( &loadcell2, &cell_data );
    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 1000g weight etalon\r\n");
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

    if ( loadcell2_calibration ( &loadcell2, LOADCELL2_WEIGHT_1000G, &cell_data ) == LOADCELL2_GET_RESULT_OK )
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");

        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 10 sec \r\n");
        log_printf( &logger, "   remove 1000g weight   \r\n");
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

>
> This is an example which demonstrates the 
> use of Load Cell 2 Click board. 
> Display the measurement of scales in grams [g].
> Results are being sent to the Usart Terminal 
> where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.
> 

```c
void application_task ( void )
{
    weight_val = loadcell2_get_weight( &loadcell2, &cell_data );

    log_printf(&logger, "   Weight : %5.2f g\r\n", weight_val );

    Delay_ms ( 1000 );
}
```

### Note


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
