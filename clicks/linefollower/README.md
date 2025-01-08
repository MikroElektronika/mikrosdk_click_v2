
---
# Line Follower Click

> [Line Follower Click](https://www.mikroe.com/?pid_product=MIKROE-1999) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1999&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Line Follower Click carries an array of five QRE1113 
> miniature reflective object sensors,
> reading staus of AN, RST, PWM, TX and RX pins and reading tracking data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LineFollower

### Example Key Functions

- `linefollower_cfg_setup` Config Object Initialization function. 
```c
void linefollower_cfg_setup ( linefollower_cfg_t *cfg );
``` 
 
- `linefollower_init` Initialization function. 
```c
err_t linefollower_init ( linefollower_t *ctx, linefollower_cfg_t *cfg );
```

- `linefollower_default_cfg` Click Default Configuration function. 
```c
void linefollower_default_cfg ( linefollower_t *ctx );
```

- `linefollower_data_track` Get status of all pin function. 
```c
void linefollower_data_track ( linefollower_t *ctx, linefollower_direction_t *data_track );
```

### Application Init

> Application Init performs logger and Click Initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    linefollower_cfg_t cfg;

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
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " - Application Init -\r\n" );

    //  Click initialization.
    linefollower_cfg_setup( &cfg );
    LINEFOLLOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linefollower_init( &linefollower, &cfg );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Line Follower  Click \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}
```

### Application Task

> Application Task shows the functionality of the Line Follower Click.
> Each one of the QRE1113 sensors consist of an
> infrared transmitter and infrared receiver. 
> By default the sensor output a Logic Level 1, until they encounter a 
> white surface which changes the output signal to 0.

```c
void application_task ( void )
{
    linefollower_direction_t data_track;
    
    linefollower_data_track ( &linefollower, &data_track );
    
    log_printf( &logger, " %u\t%u\t%u\t%u\t%u\r\n", 
                (uint16_t) data_track.u1, 
                (uint16_t) data_track.u2, 
                (uint16_t) data_track.u3, 
                (uint16_t) data_track.u4, 
                (uint16_t) data_track.u5);
    
    Delay_ms ( 100 );
}
```

### Note

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
