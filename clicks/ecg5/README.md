
---
# ECG 5 Click

> [ECG 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3446) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3446&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This is an example which demonstrates the use of ECG 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG5

### Example Key Functions

- `ecg5_cfg_setup` Config Object Initialization function.
```c
void ecg5_cfg_setup ( ecg5_cfg_t *cfg );
```

- `ecg5_init` Initialization function.
```c
err_t ecg5_init ( ecg5_t *ctx, ecg5_cfg_t *cfg );
```

- `ecg5_set_mode` Mode Setting function.
```c
void ecg5_setMode( ecg5_t *ctx, uint8_t state );
```

- `ecg5_check_lod_negative` LOD- Checking function.
```c
err_t ecg5_check_LOD_negative( ecg5_t *ctx );
```

- `ecg5_check_lod_positive` LOD+ Checking function.
```c
err_t ecg5_check_lod_positive( ecg5_t *ctx );
```

### Application Init

> Initializes ADC and GPIO.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg5_cfg_t ecg5_cfg;  /**< Click config object. */

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
    ecg5_cfg_setup( &ecg5_cfg );
    ECG5_MAP_MIKROBUS( ecg5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ecg5_init( &ecg5, &ecg5_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads ADC value and sends results on serial plotter every 5 ms.

```c
void application_task ( void ) 
{
    uint16_t ecg5_an = 0;
    if ( ecg5_read_an_pin_value( &ecg5, &ecg5_an ) == ADC_SUCCESS ) {
        log_printf( &logger, " %u,%lu\r\n ", ecg5_an, time );
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
