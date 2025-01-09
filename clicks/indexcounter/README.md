
---
# Index Counter Click

> [Index Counter Click](https://www.mikroe.com/?pid_product=MIKROE-4005) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4005&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application enables usage of Index counter Click board which can be used to measure rotational speed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IndexCounter

### Example Key Functions

- `indexcounter_cfg_setup` Config Object Initialization function. 
```c
void indexcounter_cfg_setup ( indexcounter_cfg_t *cfg );
``` 
 
- `indexcounter_init` Initialization function. 
```c
err_t indexcounter_init ( indexcounter_t *ctx, indexcounter_cfg_t *cfg );
```

- `indexcounter_default_cfg` Click Default Configuration function. 
```c
void indexcounter_default_cfg ( indexcounter_t *ctx );
```

- `indexcounter_get_dir` This function returns a state of the direction DIR ( AN ) pin. 
```c
uint8_t indexcounter_get_dir ( indexcounter_t *ctx );
```
 
- `indexcounter_get_speed` This function returns a state of the speed SPD ( RST ) pin. 
```c
uint8_t indexcounter_get_speed ( indexcounter_t *ctx );
```

### Application Init

> Initilaziation of GPIO and write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    indexcounter_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    indexcounter_cfg_setup( &cfg );
    INDEXCOUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    indexcounter_init( &indexcounter, &cfg );
}
```

### Application Task

> This is an example which demonstrates the use of the Index Counter Click board.
> This example shows the direction of movement, Rotations Per Minute ( RPM or speed )
> of the three pairs of rotating poles positioned in the sensor operating range.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    //  Task implementation.

    speed_state = indexcounter_get_speed( &indexcounter );
    dir_state = indexcounter_get_dir( &indexcounter );

    if ( enable_speed && speed_state )
    {
        pulse_ms = time_cnt - start_timer;
        start_timer = time_cnt;
        speed_rpm = INDEXCOUNTER_ONE_MIN_CONV_MS / ( pulse_ms * n_pole_pairs );
        enable_speed = INDEXCOUNTER_SPEED_DISABLE;

        log_display ( speed_rpm );
    }

    if ( ( !enable_speed ) && ( !speed_state ) )
    {
        enable_speed = INDEXCOUNTER_SPEED_ENABLE;
    }

    Delay_1ms();
    time_cnt++;
}


```

### Note

> Additional Functions :
>       - void log_display ( float rpm_val ) - The function displays all results
>         and a float value with a comma with two decimal places.

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
