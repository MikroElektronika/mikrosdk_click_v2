
---
# Hall Current 3 Click

> [Hall Current 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3118) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3118&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The example starts off with the logger and Click modules and then starts measuring and displaying current values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent3

### Example Key Functions

- `hallcurrent3_cfg_setup` Config Object Initialization function. 
```c
void hallcurrent3_cfg_setup ( hallcurrent3_cfg_t *cfg );
``` 
 
- `hallcurrent3_init` Initialization function. 
```c
err_t hallcurrent3_init ( hallcurrent3_t *ctx, hallcurrent3_cfg_t *cfg );
```

- `hallcurrent3_getCurrent` This function calculates the current value. 
```c
float hallcurrent3_getCurrent ( hallcurrent3_t *ctx );
```
 
- `hallcurrent3_read_data` This function read two bytes of data from the specified register. 
```c
uint16_t hallcurrent3_read_data ( hallcurrent3_t *ctx, uint8_t reg );
```

### Application Init

> Initializes and configures the logger and Click modules.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    hallcurrent3_cfg_t cfg;

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

    hallcurrent3_cfg_setup( &cfg );
    HALLCURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent3_init( &hallcurrent3, &cfg );
}
```

### Application Task

> Reads and displays current values every second.

```c
void application_task ( )
{
    float current_data;

    current_data = hallcurrent3_getCurrent( &hallcurrent3 );
    log_printf( &logger, "Current : %f mA\r\n" );

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
