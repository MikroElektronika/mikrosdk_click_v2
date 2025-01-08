
---
# Accel 8 Click

> [Accel 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3341) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3341&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures accelermeter and gyroscopic data and temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel8

### Example Key Functions

- `accel8_cfg_setup` Config Object Initialization function. 
```c
void accel8_cfg_setup ( accel8_cfg_t *cfg );
``` 
 
- `accel8_init` Initialization function. 
```c
err_t accel8_init ( accel8_t *ctx, accel8_cfg_t *cfg );
```

- `accel8_default_cfg` Click Default Configuration function. 
```c
void accel8_default_cfg ( accel8_t *ctx );
```

- `accel8_get_accel_axis` This function reads Accel axis data. 
```c
void accel8_get_accel_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
```
 
- `accel8_get_gyro_axis` This function reads Gyro axis data. 
```c
void accel8_get_gyro_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
```

- `accel8_get_interrupt` This function returns Interupt state. 
```c
uint8_t accel8_get_interrupt ( accel8_t *ctx );
```

### Application Init

> Initialization driver init, reset chip and start configuration chip for measurement.
 
```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel8_cfg_t cfg;

    uint8_t temp_write;

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

    accel8_cfg_setup( &cfg );
    ACCEL8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel8_init( &accel8, &cfg );

    log_printf( &logger, " *-* Device Reset *-* \r\n");
    temp_write = ACCEL8_PM1_DEVICE_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_PWR_MGMT_1, &temp_write, 1 );
    temp_write = ACCEL8_GYRO_RESET | ACCEL8_ACCEL_RESET | ACCEL8_TEMP_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_SIGNAL_PATH_RESET, &temp_write, 1 );

    log_printf( &logger, " *-* Device Configuration *-* \r\n" );
    accel8_default_cfg ( &accel8, ACCEL8_INTE_DATA_RDY_ENABLE, ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_250dbs, &range);

    Delay_ms ( 1000 );
    log_printf( &logger, " --- Start Measurement --- \r\n" );
}
```

### Application Task

> Reads Accel X/Y/Z axis, Gyro X/Y/Z axis and device Temperature. 
> All data logs on the USBUART every 2 sec.

```c
void application_task ( void )
{   
    float temperature;
    int16_t x_gyro_axis;
    int16_t y_gyro_axis;
    int16_t z_gyro_axis;
    int16_t x_accel_axis;
    int16_t y_accel_axis;
    int16_t z_accel_axis;

    //  Task implementation.

    accel8_get_accel_axis( &accel8,&x_accel_axis, &y_accel_axis, &z_accel_axis );
    accel8_get_gyro_axis( &accel8, &x_gyro_axis, &y_gyro_axis, &z_gyro_axis );
    temperature = accel8_get_temperature( &accel8 );
    
    // LOGS DATA

    log_printf( &logger, "________________ Accel 8 Click _________________\r\n" );
    log_printf( &logger, "|  Data   | X axis | Y axis | Z axis |  Range  |\r\n" );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Accel  | %d  | %d  | %d  | %dg |\r\n", x_accel_axis, y_accel_axis, z_accel_axis, accel_range );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Gyro   | %d  | %d  | %d  | %ddps|\r\n", x_gyro_axis, y_gyro_axis, z_gyro_axis, gyro_range );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Temp   | %.2f  C         |\r\n" , temperature);
    log_printf( &logger, "|_________|_________________|\r\n" );

    log_printf( &logger, " \r\n" );
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
