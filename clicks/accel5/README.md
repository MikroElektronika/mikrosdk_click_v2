
---
# Accel 5 Click

> [Accel 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3149) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3149&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application allows linear motion and gravitational force measurements. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel5

### Example Key Functions

- `accel5_cfg_setup` Config Object Initialization function. 
```c
void accel5_cfg_setup ( accel5_cfg_t *cfg );
``` 
 
- `accel5_init` Initialization function. 
```c
err_t accel5_init ( accel5_t *ctx, accel5_cfg_t *cfg );
```

- `accel5_default_cfg` Click Default Configuration function. 
```c
void accel5_default_cfg ( accel5_t *ctx );
```

- `accel5_write_byte` Functions for write one byte in register. 
```c
void accel5_write_byte( accel5_t *ctx, uint8_t reg, uint8_t reg_data );
```
 
- `accel5_read_byte` Functions for read byte from register. 
```c
uint8_t accel5_read_byte ( accel5_t *ctx, uint8_t reg );
```

- `accel5_read_data` Functions for read data from register. 
```c
uint16_t accel5_read_data ( accel5_t *ctx, uint8_t reg );
```

### Application Init

> Initializes Driver init and settings accelerometer data range and mode.

```c
void application_init ( void )
{
log_cfg_t log_cfg;
    accel5_cfg_t cfg;

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

    accel5_cfg_setup( &cfg );
    ACCEL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel5_init( &accel5, &cfg );
}
```

### Application Task

> Reads the accel X / Y / Z axis data, every 500 ms.

```c
void application_task ( void )
{
    x_axis_data = accel5_get_axis( &accel5, ACCEL5_X_AXIS );
    log_printf ( &logger, " X axis : %d \r\n  ", x_axis_data );
    
    y_axis_data = accel5_get_axis( &accel5, ACCEL5_Y_AXIS );
    log_printf ( &logger, " Y axis : %d \r\n  ", y_axis_data );

    z_axis_data = accel5_get_axis( &accel5, ACCEL5_Z_AXIS );
    log_printf ( &logger, " Z axis : %d \r\n  ", z_axis_data );
    
    Delay_ms ( 500 );
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
