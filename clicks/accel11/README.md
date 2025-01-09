
---
# Accel 11 Click

> [Accel 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3440) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3440&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This demo application reads X / Y / Z axis acceleration data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel11

### Example Key Functions

- `accel11_cfg_setup` Config Object Initialization function. 
```c
void accel11_cfg_setup ( accel11_cfg_t *cfg );
``` 
 
- `accel11_init` Initialization function. 
```c
err_t accel11_init ( accel11_t *ctx, accel11_cfg_t *cfg );
```

- `accel11_default_cfg` Click Default Configuration function. 
```c
void accel11_default_cfg ( accel11_t *ctx );
```

- `accel11_get_axis_data` This function reads accel axis. 
```c
int16_t accel11_get_axis_data ( accel11_t *ctx, uint8_t axis );
```
 
- `accel11_test_comunication` This function test comunication. 
```c
uint8_t accel11_test_comunication ( accel11_t *ctx );
```

- `accel11_power_on_procedure` This function for power on chip. 
```c
void accel11_power_on_procedure ( accel11_t *ctx );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    uint8_t tmp;
    log_cfg_t log_cfg;
    accel11_cfg_t cfg;

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

    accel11_cfg_setup( &cfg );
    ACCEL11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel11_init( &accel11, &cfg );

    tmp = accel11_test_comunication( &accel11 );
    if ( tmp == ACCEL11_TEST_COMUNICATION_OK )
    {
        log_printf( &logger, " Comunication OK !!!\r\n" );
    }
    else
    {
        log_printf( &logger, " Comunication ERROR !!!\r\n" );
        for ( ; ; );
    }
    accel11_default_cfg( &accel11 );
}
```

### Application Task

> Reads X / Y / Z axis acceleration data and it logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_X_AXIS );
    log_printf( &logger, " X axis : %d\r\n", x_axis );

    y_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Y_AXIS );
    log_printf( &logger, " Y axis : %d\r\n", y_axis );

    z_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Z_AXIS );
    log_printf( &logger, " Z axis : %d\r\n", z_axis );

    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
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
