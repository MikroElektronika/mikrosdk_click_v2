
---
# Heart rate 6 Click

> [Heart rate 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3215) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3215&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The example demonstrates the use of Heart rate 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate6

### Example Key Functions

- `heartrate6_cfg_setup` Config Object Initialization function. 
```c
void heartrate6_cfg_setup ( heartrate6_cfg_t *cfg );
``` 
 
- `heartrate6_init` Initialization function. 
```c
err_t heartrate6_init ( heartrate6_t *ctx, heartrate6_cfg_t *cfg );
```

- `heartrate6_default_cfg` Click Default Configuration function. 
```c
void heartrate6_default_cfg ( heartrate6_t *ctx );
```

- `heartrate6_get_data` Function reads the LED Data as 16bit unsigned value. 
```c
void heartrate6_get_data ( heartrate6_t *ctx, uint16_t *led_off_data, uint16_t *led_on_data );
```
 
- `heartrate6_set_freq` Function sets the data reading frequency and the LED pulse frequency. 
```c
void heartrate6_set_freq ( heartrate6_t *ctx, uint8_t freq_data );
```

- `heartrate6_start_measure` Function starts measurement cycle. 
```c
void heartrate6_start_measure ( heartrate6_t *ctx );
```

### Application Init

> Initializes interface and performs the device configuration and reset.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate6_cfg_t cfg;

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

    heartrate6_cfg_setup( &cfg );
    HEARTRATE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate6_init( &heartrate6, &cfg );
    Delay_ms ( 500 );

    heartrate6_default_cfg( &heartrate6 );
    log_printf( &logger, " Heart rate 6 is initialized. \r\n");
    Delay_ms ( 500 );
}
```

### Application Task

> Waits until measurement cycle is finished and data is ready for reading. 
> Then reads the LED data and performs the data plotting on USB UART.

```c
void application_task ( void )
{
    heartrate6_wait_measure( &heartrate6 );
    
    heartrate6_get_data( &heartrate6,  &led_data_off, &led_data_on );
    
    counter++;
    if ( led_data_off < 200 )
    {
        log_printf( &logger, "%u;\r\n", led_data_on );
        counter = 200;
    }
    else if ( counter > 200 )
    {
        log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
        counter = 0;
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
