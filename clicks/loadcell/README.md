
---
# LOAD CELL Click

> [Load cell Click](https://www.mikroe.com/?pid_product=MIKROE-3168) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3168&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> Load cell Click is a weight measurement Click which utilizes a load cell element, 
> in order to precisely measure the weight of an object. 
> The Load Cell Click can be used with the strain gauge type of load cells 
> and can measure up to ±20V or ±40V of differential voltage. 
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell

### Example Key Functions

- `loadcell_cfg_setup` Config Object Initialization function. 
```c
void loadcell_cfg_setup ( loadcell_cfg_t *cfg );
``` 
 
- `loadcell_init` Initialization function. 
```c
err_t loadcell_init ( loadcell_t *ctx, loadcell_cfg_t *cfg );
```

- `loadcell_default_cfg` Click Default Configuration function. 
```c
void loadcell_default_cfg ( loadcell_t *ctx );
```

- `loadcell_read_results` Read results of function. 
```c
uint8_t loadcell_read_results ( loadcell_t *ctx, uint8_t input_sel, uint32_t *data_out );
```
 
- `loadcell_set_rate` Set rate function. 
```c
void loadcell_set_rate ( loadcell_t *ctx, uint8_t rate_sel );
```

- `loadcell_check_out` Check status of pin DO (do_pin). 
```c
uint8_t loadcell_check_out ( loadcell_t *ctx );
```

- `loadcell_reset` Reset clock function. 
```c
void loadcell_reset ( loadcell_t *ctx );
```
 
- `loadcell_set_mode` Set clock mode function. 
```c
void loadcell_set_mode ( loadcell_t *ctx, uint8_t pwr_mode );
```

- `loadcell_tare` Function of messure and read results. 
```c
void loadcell_tare ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );
```

- `loadcell_calibration` Calibration function. 
```c
uint8_t loadcell_calibration ( loadcell_t *ctx, uint8_t input_sel, uint16_t cal_val, loadcell_data_t *cell_data );
```

- `loadcell_get_weight` Get weight function. 
```c
float loadcell_get_weight ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );
```

### Application Init

>
> Initializes GPIO driver and performs the device reset, 
> after which the next conversion cycle will be for channel B with 32 gate value.
> This function also selects the frequency of internal oscillator to 10Hz.
> Sets tare the scale, calibrate scale and start measurements.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    loadcell_cfg_setup( &cfg );
    LOADCELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell_init( &loadcell, &cfg );
    
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "     Load cell Click     \r\n");
    log_printf(&logger, "-------------------------\r\n");
    Delay_ms ( 100 );
    
    loadcell_set_mode( &loadcell, LOADCELL_POWER_UP );
    Delay_ms ( 100 );

    loadcell_reset( &loadcell );
    Delay_ms ( 100 );

    loadcell_set_rate( &loadcell, LOADCELL_10HZ_INTERNAL_OSC );
    Delay_ms ( 100 );

    log_printf(&logger, "    Tare the scale :   Channel B,  Gate 32  \r\n");
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
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

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start tare scales    \r\n");
    loadcell_tare ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );
    Delay_ms ( 500 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Tarring completed \r\n");

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds place 100g weight etalon on the scale for calibration purpose.\r\n");
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

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start calibration    \r\n");

    if ( loadcell_calibration ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, LOADCELL_WEIGHT_100G, &cell_data ) == LOADCELL_GET_RESULT_OK )
    {
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "    Calibration  Done    \r\n");

        log_printf(&logger, "- - - - - - - - - - - - -\r\n");
        log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
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
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "   Start measurements :  \r\n");
    log_printf(&logger, "-------------------------\r\n");
}
```

### Application Task

>
> This is an example which demonstrates the use of Load Cell Click board.
> Display the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.
> 

```c
void application_task ( void )
{
    weight_val = loadcell_get_weight( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );

    log_printf(&logger, "     Weight : %.2f\r\n", weight_val );

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
