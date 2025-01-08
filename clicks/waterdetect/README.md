
---
# Water Detect Click

> [Water Detect Click](https://www.mikroe.com/?pid_product=MIKROE-2786) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2786&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Water Detect Click is used for detecting water and other electroconductive liquids. If the detection area is wet the output of Microchip's MCP606 CMOS op-amp will go positive, signaling the presence of liquid.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect

### Example Key Functions

- `waterdetect_cfg_setup` Config Object Initialization function. 
```c
void waterdetect_cfg_setup ( waterdetect_cfg_t *cfg );
``` 
 
- `waterdetect_init` Initialization function. 
```c
err_t waterdetect_init ( waterdetect_t *ctx, waterdetect_cfg_t *cfg );
```

- `waterdetect_default_cfg` Click Default Configuration function. 
```c
void waterdetect_default_cfg ( waterdetect_t *ctx );
```

#### Example key function :

- `waterdetect_get_status` Get the status of the water detection function. 
```c
uint8_t waterdetect_get_status ( waterdetect_t *ctx );
```

### Application Init

> Initializes GPIO and LOG structures, set INT pins as input and starts to write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    waterdetect_cfg_t cfg;

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

    waterdetect_cfg_setup( &cfg );
    WATERDETECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    waterdetect_init( &waterdetect, &cfg );
    Delay_100ms();
    
    log_printf( &logger, "  Initialization Driver   \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, "  Wait to detect water...  \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
}
```

### Application Task

> Reads device status and determines if there are water presence or not.

```c
void application_task ( void )
{
    wd_state = waterdetect_get_status( &waterdetect );

    if ( wd_state > wd_state_old )
    {
        log_printf( &logger, " >  Water is detected  < \r\n" );
        log_printf( &logger, "------------------------- \r\n" );
        wd_state_old = 1;
    }

    if ( wd_state < wd_state_old )
    {
        log_printf( &logger, " There is no water \r\n" );
        log_printf( &logger, "------------------- \r\n" );
        wd_state_old = 0;
    }
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
