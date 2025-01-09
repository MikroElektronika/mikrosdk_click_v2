
---
# Light Ranger 4 Click

> [LightRanger 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3176) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3176&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>  Demo application is used to shows basic controls LightRanger 4 Click

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger4

### Example Key Functions

- `lightranger4_cfg_setup` Config Object Initialization function. 
```c
void lightranger4_cfg_setup ( lightranger4_cfg_t *cfg );
``` 
 
- `lightranger4_init` Initialization function. 
```c
err_t lightranger4_init ( lightranger4_t *ctx, lightranger4_cfg_t *cfg );
```

- `lightranger4_default_cfg` Click Default Configuration function. 
```c
void lightranger4_default_cfg ( lightranger4_t *ctx );
```

- `lightranger4_new_data_ready` Function that checks whether the new data is ready for reading. 
```c
uint8_t lightranger4_new_data_ready ( lightranger4_t *ctx );
```
 
- `lightranger4_get_distance` Function reads distance of the object in front of the sensor. 
```c
uint16_t lightranger4_get_distance ( lightranger4_t *ctx );
```

- `lightranger4_power_on` Function for starts power ON procedure. 
```c
void lightranger4_power_on ( lightranger4_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration,
> adjusts the LONG mode (distance measurement up to 4 meters),
> sets the time budget and start measurement with the adjustment of inter measurements period.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger4_cfg_t cfg;

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

    lightranger4_cfg_setup( &cfg );
    LIGHTRANGER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger4_init( &lightranger4, &cfg );

    lightranger4_power_on( &lightranger4 );
    log_info( &logger, "--- Wait until the configuration of the chip is completed ---" );

    lightranger4_default_cfg( &lightranger4 );
    lightranger4_set_distance_mode( &lightranger4, LR4_DISTANCE_MODE_LONG );
    lightranger4_set_measurement_timing_budget( &lightranger4, 1000 );
    lightranger4_start_measurement( &lightranger4, 20 );

    log_info( &logger, "--- Sensor start measurement ---" );
    Delay_100ms( );
}
```

### Application Task

> Reads the distance of the object in front of the sensor and logs 
> distance to USBUART every 500 ms.

```c
void application_task ( void )
{
    uint16_t distance;
    uint8_t m_status;

    //  Task implementation.

    while ( lightranger4_new_data_ready( &lightranger4 ) != 0 )
    {
        Delay_1ms();
    }

    distance = lightranger4_get_distance( &lightranger4 );
    log_printf( &logger, "** Distance: %d mm \r\n", distance );

    m_status = lightranger4_get_range_status( &lightranger4 );
    switch ( m_status )
    {
        case LR4_MRESP_SIGNAL_FAIL:
        {
            log_info( &logger, "Signal fail." );
            break;
        }
        case LR4_MRESP_PHASE_OUT_OF_VALID_LIMITS:
        {
            log_info( &logger, "Phase out of valid limits" );
            break;
        }
        case LR4_MRESP_SIGMA_FAIL:
        {
            log_info( &logger, "Sigma Fail. " );
            break;
        }
        case LR4_MRESP_WRAP_TARGET_FAIL:
        {
            log_info( &logger, "Wrap target fail." );
            break;
        }
        case LR4_MRESP_MINIMUM_DETECTION_THRESHOLD:
        {
            log_info( &logger, "Target is below minimum detection threshold. " );
            break;
        }
    }
    Delay_ms ( 500 );
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
