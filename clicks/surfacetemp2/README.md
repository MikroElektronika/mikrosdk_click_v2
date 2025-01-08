
---
# Surface Temp 2 Click

> [Surface Temp 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4266) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4266&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Surface Temp 2 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SurfaceTemp2

### Example Key Functions

- `surfacetemp2_cfg_setup` Config Object Initialization function. 
```c
void surfacetemp2_cfg_setup ( surfacetemp2_cfg_t *cfg );
``` 
 
- `surfacetemp2_init` Initialization function. 
```c
err_t surfacetemp2_init ( surfacetemp2_t *ctx, surfacetemp2_cfg_t *cfg );
```

- `surfacetemp2_get_temperature` Get Temperature function. 
```c
float surfacetemp2_get_temperature ( surfacetemp2_t *ctx );
```
 
- `surfacetemp2_set_crit_trsh` Set Critical Temperature Threshold function. 
```c
void surfacetemp2_set_crit_trsh ( surfacetemp2_t *ctx, float trsh );
```

- `surfacetemp2_get_ct_pin` Get CT pin state function. 
```c
uint8_t surfacetemp2_get_ct_pin ( surfacetemp2_t *ctx );
```

### Application Init

> Initalizes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp2_cfg_t cfg;

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

    surfacetemp2_cfg_setup( &cfg );
    SURFACETEMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp2_init( &surfacetemp2, &cfg );

    setup_val = SURFACETEMP2_CFG_FLT_Q_4 | SURFACETEMP2_CFG_CT_MODE | SURFACETEMP2_CFG_RES_16;
    surfacetemp2_setup ( &surfacetemp2, setup_val );
    surfacetemp2_set_high_trsh( &surfacetemp2, 40.00 );
    surfacetemp2_set_low_trsh( &surfacetemp2, 10.00 );
    surfacetemp2_set_crit_trsh( &surfacetemp2, 70.00 );
    surfacetemp2_set_hys_val( &surfacetemp2, 5 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the temperature in Celsius and displays the value on the USB UART each second.

```c
void application_task ( void )
{
    temperature = surfacetemp2_get_temperature( &surfacetemp2 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
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
