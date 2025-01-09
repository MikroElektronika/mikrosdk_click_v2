
---
# Accel 7 Click

> [Accel 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3244) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3244&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows how data from all three axes is collected, processed and later
  displayed in the logger module.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel7

### Example Key Functions

- `accel7_cfg_setup` Config Object Initialization function. 
```c
void accel7_cfg_setup ( accel7_cfg_t *cfg );
``` 
 
- `accel7_init` Initialization function. 
```c
err_t accel7_init ( accel7_t *ctx, accel7_cfg_t *cfg );
```

- `accel7_default_cfg` Click Default Configuration function. 
```c
void accel7_default_cfg ( accel7_t *ctx, uint8_t resolution, uint8_t range );
```

- `accel7_get_axis` This function reads two bytes of data from the desired axis register. 
```c
int16_t accel7_get_axis ( accel7_t *ctx, uint8_t axis );
```
 
- This function calculates the resolution and range values which are used
  in the default_cfg() function.
> void accel7_res_range_cfg ( accel7_t *ctx, uint8_t *resolution, uint8_t *range );

- `accel7_get_interrupt_state` This function reads the state of the interrupt pin. 
```c
uint8_t accel7_get_interrupt_state ( accel7_t *ctx );
```

### Application Init

> Initializes and configures the Click and logger modules.

```c
void application_init (  )
{
    log_cfg_t log_cfg;
    accel7_cfg_t cfg;

    uint8_t resolution = ACCEL7_DATA_RESP_14bit;
    uint8_t range = ACCEL7_RANGE_8g;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    accel7_cfg_setup( &cfg );
    ACCEL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel7_init( &accel7, &cfg );

    accel7_res_range_cfg( &accel7, &resolution, &range );
    accel7_default_cfg( &accel7, resolution, range );

    delay_ms( 100 );
}
```

### Application Task

> Reads and displays data from all three axes every second.

```c
void application_task (  )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_X );
    y_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Y );
    z_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Z );

    log_printf( &logger, "X axis: %d\r\n", x_axis );
    log_printf( &logger, "Y axis: %d\r\n", y_axis );
    log_printf( &logger, "Z axis: %d\r\n", z_axis );   
    
    log_printf( &logger, "------------------\r\n" );

    delay_ms( 1000 );
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
