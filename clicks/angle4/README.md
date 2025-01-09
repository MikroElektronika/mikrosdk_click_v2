
---
# Angle 4 Click

> [Angle 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3130) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3130&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enables use of angular magnetic rotary sensor, which can be used as a rotary 
> encoder.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle4

### Example Key Functions

- `angle4_cfg_setup` Config Object Initialization function. 
```c
void angle4_cfg_setup ( angle4_cfg_t *cfg );
``` 
 
- `angle4_init` Initialization function. 
```c
err_t angle4_init ( angle4_t *ctx, angle4_cfg_t *cfg );
```

- `angle4_default_cfg` Click Default Configuration function. 
```c
void angle4_default_cfg ( angle4_t *ctx );
```

- `angle4_start_mesuremenet` function used to start measurement mode. 
```c
void angle4_start_mesuremenet ( angle4_t *ctx );
```
 
- `angle4_get_new_angle` This function is used to retrieve Angle value depending on the given resolution. 
```c
uint8_t angle4_get_new_angle ( angle4_t *ctx, uint16_t *data_out );
```

- `angle4_read_byte` This function is used to read single byte of Data on the desired address. 
```c
uint8_t angle4_read_byte ( angle4_t *ctx, uint8_t addr );
```

### Application Init

> Driver intialization, standard configurations and start measurement

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    angle4_cfg_t cfg;

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

    angle4_cfg_setup( &cfg );
    ANGLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle4_init( &angle4, &cfg );

    angle4_default_cfg( &angle4, ANGLE4_CCFG2_DIR_COUNTER_CLOCKWISE_ROTATION,\
                                 ANGLE4_CCFG2_ABS_RESOLUTION_14bit );
    log_printf( &logger, " --- Start measurement \r\n");

    angle4_start_mesuremenet( &angle4 );
}
```

### Application Task

> Reads Angle in degreeses and logs data to USBUART every 200 ms.

```c
void application_task ( void )
{
    //  Task implementation.

    uint16_t angle_value;

    angle4_get_new_angle( &angle4, &angle_value );
    log_printf( &logger, " Angle : %d deg\r\n", angle_value );
    Delay_ms ( 200 );
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
