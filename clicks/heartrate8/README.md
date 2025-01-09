
---
# Heart Rate 8 Click

> [Heart Rate 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3218) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3218&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Hearth rate 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate8

### Example Key Functions

- `heartrate8_cfg_setup` Config Object Initialization function. 
```c
void heartrate8_cfg_setup ( heartrate8_cfg_t *cfg );
``` 
 
- `heartrate8_init` Initialization function. 
```c
err_t heartrate8_init ( heartrate8_t *ctx, heartrate8_cfg_t *cfg );
```

- `heartrate8_default_cfg` Click Default Configuration function. 
```c
void heartrate8_default_cfg ( heartrate8_t *ctx );
```

- `heartrate8_get_data ` Function gets the selected data from the determined LED Data registers.. 
```c
uint8_t heartrate8_get_data  ( heartrate8_t *ctx, uint8_t data_select, uint16_t *led_out_on, uint16_t *led_out_off );
```

- `heartrate8_check_int` Function checks INT pin, is interrupt occured or not. 
```c
uint8_t heartrate8_check_int ( heartrate8_t *ctx );
```

- `heartrate8_meas_sync` Function performs the measurement synchronization. 
```c
void heartrate8_meas_sync ( heartrate8_t *ctx );
```

### Application Init

> Performs the device reset.  The device is configured to work in Single Measurement Mode with LED pulsing.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate8_cfg_t cfg;

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
    log_info( &logger, "---- Application Initializing ----" );

    //  Click initialization.

    heartrate8_cfg_setup( &cfg );
    HEARTRATE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate8_init( &heartrate8, &cfg );
    Delay_ms ( 500 );
    heartrate8_default_cfg( &heartrate8 );
    i = 0;

    log_printf( &logger, "HeartRate 8 is initialized\n");
}
```

### Application Task

> Sends command to start measurement cycle, then waits until measurement cycle is finished. When measurement cycle is done, gets LED ON and LED OFF Data for the selected LED driver (GREEN or IR LED) and performs data plotting on serial plotter every 35ms.
 

```c
void application_task ( void )
{
    heartrate8_start_measure( &heartrate8 );
    
    int_check = heartrate8_check_int( &heartrate8 );
    while (int_check != HEARTRATE8_INT_ACTIVE)
    {
        int_check = heartrate8_check_int( &heartrate8 );
    }
    
    heartrate8_get_data( &heartrate8, HEARTRATE8_GREEN_DATA_GET, &led_data_on, &led_data_off );
    plot_res( led_data_on );
    int_check = heartrate8_int_clear( &heartrate8 );
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
