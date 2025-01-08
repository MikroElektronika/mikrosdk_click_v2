
---
# Heart Rate 9 Click

> [Heart Rate 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3822) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3822&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Heart Rate 9 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate9

### Example Key Functions

- `heartrate9_cfg_setup` Config Object Initialization function.
```c
void heartrate9_cfg_setup ( heartrate9_cfg_t *cfg );
```

- `heartrate9_init` Initialization function.
```c
err_t heartrate9_init ( heartrate9_t *ctx, heartrate9_cfg_t *cfg );
```

- `heartrate9_default_cfg` Click Default Configuration function.
```c
void heartrate9_default_cfg ( heartrate9_t *ctx );
```

- `heartrate9_generic_write` Heart Rate 9 data writing function.
```c
err_t heartrate9_generic_write ( heartrate9_t *ctx, char *data_buf, uint16_t len );
```

- `heartrate9_generic_read` Heart Rate 9 data reading function.
```c
err_t heartrate9_generic_read ( heartrate9_t *ctx, char *data_buf, uint16_t max_len );
```

- `heartrate9_set_rst` Sets state of the rst pin setting.
```c
void heartrate9_set_rst ( heartrate9_t *ctx, uint8_t state );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate9_cfg_t heartrate9_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate9_cfg_setup( &heartrate9_cfg );
    HEARTRATE9_MAP_MIKROBUS( heartrate9_cfg, MIKROBUS_1 );
    err_t init_flag  = heartrate9_init( &heartrate9, &heartrate9_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
}
```

### Application Task

> Reads the received data and logs it.

```c
void application_task ( void )
{
   heartrate9_process();

    if ( app_buf_len > 0 )
    {
        log_printf( &logger, "%s", app_buf );
        heartrate9_clear_app_buf(  );
    }
}
```

### Note

> Data structure is:
>>AA;BB;CC;DD;EE;
>>>AA -> Data header.\
BB -> Red diode.\
CC -> IR diode.\
DD -> Green diode.\
EE -> BPM.

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
