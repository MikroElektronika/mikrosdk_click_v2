
---
# TMR Angle Click

> [TMR Angle Click](https://www.mikroe.com/?pid_product=MIKROE-3769) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3769&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example reads and value in deegres, and then logs the result. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TMRAngle

### Example Key Functions

- `tmrangle_cfg_setup` Config Object Initialization function. 
```c
void tmrangle_cfg_setup ( tmrangle_cfg_t *cfg );
``` 
 
- `tmrangle_init` Initialization function. 
```c
err_t tmrangle_init ( tmrangle_t *ctx, tmrangle_cfg_t *cfg );
```

- `tmrangle_default_cfg` Click Default Configuration function. 
```c
void tmrangle_default_cfg ( tmrangle_t *ctx );
```

- `tmrangle_init_sensor_data` Function read and stores negative and positive, sine and cosine parameters data. 
```c
void tmrangle_init_sensor_data ( tmrangle_t* ctx );
```
 
- `tmrangle_calibration_find_param ` This function will extract the maximum, minimum voltage levels, amplitude, offset, and orthogonality. 
```c
void tmrangle_calibration_find_param  ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param  );
```

- `tmrangle_get_calib_angle` Function calculates the calibrated angle in degrees and this structure holds the current sensor calibration parameters. 
```c
float tmrangle_get_calib_angle ( tmrangle_calib_data_t* calib_param );
```

### Application Init

> Initializes driver, and also write log.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrangle_cfg_t cfg;

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

    tmrangle_cfg_setup( &cfg );
    TMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrangle_init( &tmrangle, &cfg );

}
```

### Application Task

> Reads angle value in degrees and logs the results.

```c
void application_task ( void )
{
    float angle;
    trigonometry_t trig_set;
    tmrangle_calib_data_t calibration_store_params;
    tmrangle_init_sensor_data( &tmrangle );

    trig_set.max_diff_sin = TMRANGLE_MAX_DIFF_SIN;
    trig_set.max_diff_cos = TMRANGLE_MAX_DIFF_COS;
    trig_set.min_diff_sin = TMRANGLE_MIN_DIFF_SIN;
    trig_set.min_diff_cos = TMRANGLE_MIN_DIFF_COS;
    trig_set.sin_45 = TMRANGLE_SIN_45;
    trig_set.cos_45 = TMRANGLE_COS_45;
    trig_set.sin_135 = TMRANGLE_SIN_135;
    trig_set.cos_135 = TMRANGLE_COS_135;

    tmrangle_init_calib_data( &tmrangle, &calibration_store_params, &trig_set );
    tmrangle_calibration_find_param( &tmrangle, &calibration_store_params );

    angle = tmrangle_get_calib_angle( &tmrangle, &calibration_store_params );

    log_printf( &logger, "Angle is %f deg\r\n", angle );

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
