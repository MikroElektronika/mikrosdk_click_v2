
---
# Gyro Click

> [Gyro Click](https://www.mikroe.com/?pid_product=MIKROE-1379) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1379&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example displays values of Gyro sensor (x, y, z axis)

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro

### Example Key Functions

- `gyro_cfg_setup` Config Object Initialization function. 
```c
void gyro_cfg_setup ( gyro_cfg_t *cfg );
``` 
 
- `gyro_init` Initialization function. 
```c
err_t gyro_init ( gyro_t *ctx, gyro_cfg_t *cfg );
```

- `gyro_default_cfg` Click Default Configuration function. 
```c
void gyro_default_cfg ( gyro_t *ctx );
```

- `gyro_get_axis` Function get data from two L3GD20 register. 
```c
int16_t gyro_get_axis ( gyro_t *ctx, uint8_t adr_reg_low  );
```
 
- `gyro_read_gyro` Function read Gyro X-axis, Y-axis and Z-axis axis. 
```c
void gyro_read_gyro ( gyro_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );
```

- `gyro_read_temperature` Function read temperature data. 
```c
uint8_t gyro_read_temperature ( gyro_t *ctx );
```

### Application Init

> Initialization driver, initialize L3GD20 register and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro_cfg_t cfg;

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

    gyro_cfg_setup( &cfg );
    GYRO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro_init( &gyro, &cfg );
    gyro_default_cfg ( &gyro);
}
```

### Application Task

> This is a example which demonstrates the use of Gyro Click board.
> Measured Gyro coordinates ( X-axis, Y-axis, Z-axis ) and temperature in degrees C are being sent
> to the Usart Terminal where you can track their changes.
> All data logs on usb uart for every 2 sec. 

```c
void application_task ( void )
{
    //  Task implementation.

    gyro_read_gyro(  &gyro, &gyrox,  &gyroy, &gyroz );
    temperature = gyro_read_temperature( &gyro );

    log_printf( &logger, " Axis X : %d \r\n", gyrox );
    log_printf( &logger, " Axis Y : %d \r\n", gyroy );
    log_printf( &logger, " Axis Z : %d \r\n", gyroz );
    log_printf( &logger, " Temp.: %.2f C\r\n", temperature );

    Delay_ms ( 1000 );
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
