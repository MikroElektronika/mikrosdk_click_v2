
---
# EMG Click

> [EMG Click](https://www.mikroe.com/?pid_product=MIKROE-2621) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2621&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This is an example which demonstrates the use of EMG Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EMG

### Example Key Functions

- `emg_cfg_setup` Config Object Initialization function.
```c
void emg_cfg_setup ( emg_cfg_t *cfg );
```

- `emg_init` Initialization function.
```c
err_t emg_init ( emg_t *ctx, emg_cfg_t *cfg );
```

- `emg_read_an_pin_value` EMG read AN pin value function.
```c
err_t emg_read_an_pin_value ( emg_t *ctx, uint16_t *data_out );
```

- `emg_read_an_pin_voltage` EMG read AN pin voltage level function.
```c
err_t emg_read_an_pin_voltage ( emg_t *ctx, float *data_out );
```

### Application Init

> Initializes ADC and timer counter.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    emg_cfg_t emg_cfg;  /**< Click config object. */

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
    emg_cfg_setup( &emg_cfg );
    EMG_MAP_MIKROBUS( emg_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == emg_init( &emg, &emg_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    time = 0;
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads ADC value and sends results on serial plotter every 5 ms.

```c
void application_task ( void )  
{
    uint16_t emg_an = 0;
    if ( emg_read_an_pin_value( &emg, &emg_an ) == ADC_SUCCESS ){
        log_printf( &logger, " %u,%lu\r\n ", emg_an, time );
    }
    time += 5;
    Delay_ms ( 5 );
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
