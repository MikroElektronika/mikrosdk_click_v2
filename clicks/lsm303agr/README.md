
---
# LSM303AGR Click

> [LSM303AGR Click](https://www.mikroe.com/?pid_product=MIKROE-2684) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2684&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo example returns magnetic and acceleration values from the LSM303AGR sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LSM303AGR

### Example Key Functions

- `lsm303agr_cfg_setup` Config Object Initialization function. 
```c
void lsm303agr_cfg_setup ( lsm303agr_cfg_t *cfg );
``` 
 
- `lsm303agr_init` Initialization function. 
```c
err_t lsm303agr_init ( lsm303agr_t *ctx, lsm303agr_cfg_t *cfg );
```

- `lsm303agr_default_cfg` Click Default Configuration function. 
```c
void lsm303agr_default_cfg ( lsm303agr_t *ctx );
```

- `lsm303agr_get_acc_axis_x` Reading the raw X axis data and calculating the value. 
```c
float lsm303agr_get_acc_axis_x ( lsm303agr_t *ctx );
```
 
- `lsm303agr_get_mag_axis_x` Reading the raw X axis data and calculating the value. 
```c
float lsm303agr_get_mag_axis_x ( lsm303agr_t *ctx );
```

- `lsm303agr_get_mag_axis_y` Reading the raw Y axis data and calculating the value. 
```c
float lsm303agr_get_mag_axis_y ( lsm303agr_t *ctx );
```

### Application Init

> Driver initialization and setting operating modes of accelerometer and magnetometer.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm303agr_cfg_t cfg;

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

    lsm303agr_cfg_setup( &cfg );
    LSM303AGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm303agr_init( &lsm303agr, &cfg );
    lsm303agr_default_cfg ( &lsm303agr );
   
}
```

### Application Task

> Reading accelerometer and magnetometer axis X,Y,Z and displaying it on terminal.

```c
void application_task ( void )
{
    //  Task implementation.

    log_printf(&logger, "======== Accelerometer data ========\r\n");
    
    read_data = lsm303agr_get_acc_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %f\r\n", read_data);
    
    log_printf(&logger, "======== Mangetometer data ========\r\n");
    
    read_data = lsm303agr_get_mag_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %f\r\n", read_data);

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
