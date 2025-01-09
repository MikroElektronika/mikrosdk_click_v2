
---
# Ambient 8 Click

> [Ambient 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3452) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3452&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example collects data from the sensor, calculates the light intensity and then logs it. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient8

### Example Key Functions

- `ambient8_cfg_setup` Config Object Initialization function. 
```c
void ambient8_cfg_setup ( ambient8_cfg_t *cfg );
``` 
 
- `ambient8_init` Initialization function. 
```c
err_t ambient8_init ( ambient8_t *ctx, ambient8_cfg_t *cfg );
```

- `ambient8_default_cfg` Click Default Configuration function. 
```c
void ambient8_default_cfg ( ambient8_t *ctx );
```

- `ambient8_set_constants` This function sets constants ( gain and integration time ) for lux level calculation. 
```c
void ambient8_set_constants ( ambient8_t* ctx );
```
 
- `ambient8_get_als_data` This function checks for new data by polling ALS status register. 
```c
err_t ambient8_get_als_data ( ambient8_t* ctx, uint16_t* als_data_ch1,uint16_t* als_data_ch0 );
```

- This function reads and data and performs lux level calculation
err_t ambient8_get_lux_level ( ambient8_t* ctx, float* lux_level, float window_factor, float IR_factor );

### Application Init

> Initializes device and I2C driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient8_cfg_t cfg;

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

    ambient8_cfg_setup( &cfg );
    AMBIENT8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient8_init( &ambient8, &cfg );

    window_factor = 1.0;
    IR_factor = 0.0;
}
```

### Application Task

> Performs Lux calculation based on window and IR factor and log results.

```c
void application_task ( void )
{
    status_flag = ambient8_get_lux_level( &ambient8, &lux_level, window_factor, IR_factor );

    if ( status_flag == 0 )
    {
        log_printf( &logger, "Lux level : %.2f lx\r\n", lux_level );
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
