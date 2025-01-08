
---
# Color 9 Click

> [Color 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3690) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3690&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This example reads data from the sensor, and then logs IR, green, blue and red 
> measurements.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color9

### Example Key Functions

- `color9_cfg_setup` Config Object Initialization function. 
```c
void color9_cfg_setup ( color9_cfg_t *cfg );
``` 
 
- `color9_init` Initialization function. 
```c
err_t color9_init ( color9_t *ctx, color9_cfg_t *cfg );
```

- `color9_get_green` This function gets Green measurement reading. 
```c
uint32_t color9_get_green ( color9_t* ctx );
```
 
- `color9_get_blue` This function gets Blue measurement reading. 
```c
uint32_t color9_get_blue ( color9_t* ctx );
```

- `color9_get_red` This function gets Red measurement reading. 
```c
uint32_t color9_get_red ( color9_t* ctx );
```

### Application Init

> Initialize the driver and test if the sensor is
> present. If the ID read from the sensor is correct
> execute the initialization procedure.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color9_cfg_t cfg;

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

    color9_cfg_setup( &cfg );
    COLOR9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color9_init( &color9, &cfg );

    ID = color9_read( &color9, COLOR9_PART_ID );

    if ( ID == 0xB2 )
    {
        log_printf( &logger, "Register ID 0x%x\r\n", ID );
        color9_meas_rate( &color9, COLOR9_LS_MEAS_BITWIDTH_13, COLOR9_LS_MEAS_RATE_1000ms );
        color9_reg_ctrl( &color9, COLOR9_MAIN_CTRL_CS_MODE | COLOR9_MAIN_CTRL_LS_EN );
    }
    else
    {
        log_printf( &logger, "Error\r\n" );
        while ( 1 );
    }
}
```

### Application Task

> Wait for the color data to be available then read the data
> and send it to the serial port.


```c
void application_task ( void )
{
    conv_complete = color9_get_status_reg( &color9 );

    if ( conv_complete & 0x08 )
    {
        conv_complete = 0;
        measurement_data = color9_get_Ir( &color9 );
        log_printf( &logger, "Ir: %d\r\n", measurement_data );

        
        measurement_data = color9_get_green( &color9 );
        log_printf(&logger, "Green: %d\r\n", measurement_data);

        measurement_data = color9_get_blue( &color9 );
        log_printf(&logger, "Blue: %d\r\n", measurement_data);

        measurement_data = color9_get_red( &color9 );
        log_printf(&logger, "Red: %d\r\n", measurement_data);

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
