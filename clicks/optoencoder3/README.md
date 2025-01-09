
---
# Opto Encoder 3 Click

> [Opto Encoder 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3710) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3710&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The demo application displays the counter value or displays the status of each O pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder3

### Example Key Functions

- `optoencoder3_cfg_setup` Config Object Initialization function. 
```c
void optoencoder3_cfg_setup ( optoencoder3_cfg_t *cfg );
``` 
 
- `optoencoder3_init` Initialization function. 
```c
err_t optoencoder3_init ( optoencoder3_t *ctx, optoencoder3_cfg_t *cfg );
```

- `optoencoder3_cnt` Functions for reading number of swipes. 
```c
uint8_t optoencoder3_cnt ( optoencoder3_t *ctx );
```
 
- `optoencoder3_enable` Sets state of Click. 
```c
void optoencoder3_enable ( optoencoder3_t *ctx, uint8_t active );
```

- `optoencoder3_read_all_pins` Sets state of all pins. 
```c
void optoencoder3_read_all_pins ( optoencoder3_t *ctx, optoencoder3_pins_t *pins );
```

### Application Init

> Configures the driver and logger, and selects the demo application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder3_cfg_t cfg;

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

    optoencoder3_cfg_setup( &cfg );
    OPTOENCODER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder3_init( &optoencoder3, &cfg );

    optoencoder3_enable ( &optoencoder3, OPTOENCODER3_ENABLE );
    
    example_setter = DEMO_CNT;
}
```

### Application Task

> Depending on the demo application mode set in the application init it:
>    - Measures and displays the value of the counter - DEMO_CNT mode; or
>    - Draws the status of each O pin - DEMO_GRAPH mode.

```c
void application_task ( void )
{
    if ( example_setter == DEMO_GRAPH )
    {
        draw_pins_status(  );
    }
    else if ( example_setter == DEMO_CNT )
    {
        view_counters(  );
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
