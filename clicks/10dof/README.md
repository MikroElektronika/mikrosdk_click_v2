
---
# 10DOF Click

> [10DOF Click](https://www.mikroe.com/?pid_product=MIKROE-2073) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2073&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This is a example which demonstrates the use of 10DOF Click board.
> It measures temperature, and pressure data from the BME180 chip sensor
> and accel, gyro and magnetometar coordinates values for X-axis, Y-axis and Z-axis.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.10Dof

### Example Key Functions

- `c10dof_cfg_setup` Config Object Initialization function. 
```c
void c10dof_cfg_setup ( c10dof_cfg_t *cfg );
``` 
 
- `c10dof_init` Initialization function. 
```c
err_t c10dof_init ( c10dof_t *ctx, c10dof_cfg_t *cfg );
```

- `c10dof_default_cfg` Click Default Configuration function. 
```c
void c10dof_default_cfg ( c10dof_t *ctx );
```

- `c10dof_write_byte` This function writes data to the desired register. 
```c
void c10dof_write_byte ( c10dof_t *ctx, uint8_t reg, uint8_t data_in, uint8_t slave_addr );
```
 
- `c10dof_bmp180_chip_ID` This function reads the ID value od the BMP180 chip. 
```c
uint8_t c10dof_bmp180_chip_ID ( c10dof_t *ctx );
```

- `c10dof_default_configuration_BMP180` This function sets default configuration for the BMP180 sensor function. 
```c
void c10dof_default_configuration_BMP180 ( c10dof_t *ctx );
```

### Application Init

> Initialize the driver and sets the default configuration of BMP180 and BNO055 chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c10dof_cfg_t cfg;

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

    c10dof_cfg_setup( &cfg );
    C10DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10dof_init( &c10dof, &cfg );
    c10dof_default_cfg( &c10dof );
}
```

### Application Task

> Displays temperature and pressure data from the BMP180 and BNO055 sensors.

```c
void application_task ( void )
{
    c10dof_read_accel( &c10dof, &accelX, &accelY, &accelZ );
    Delay_ms ( 10 );
    c10dof_read_gyro( &c10dof, &gyroX,  &gyroY, &gyroZ );
    Delay_ms ( 10 );
    c10dof_read_mag( &c10dof, &magX,  &magY, &magZ );
    Delay_ms ( 10 );
    
    temperature = c10dof_get_temperature( &c10dof );
    Delay_ms ( 10 );
    c10dof_get_measurements( &c10dof, &temperature, &pressure );
    Delay_ms ( 10 );

    log_printf( &logger, "Accel X : %d  |  ", accelX );
    log_printf( &logger, "Gyro X  : %d  |  ", gyroX );
    log_printf( &logger, "Mag X   : %d  |  ", magX );
    log_printf( &logger, "Temp.   : %.2f C  \r\n", temperature, deg_cel);

    log_printf( &logger, "Accel Y : %d  |  ", accelY);
    log_printf( &logger, "Gyro Y  : %d  |  ", gyroY);
    log_printf( &logger, "Mag Y   : %d  |  \r\n", magY);

    log_printf( &logger, "Accel Z : %d  |  ", accelZ);
    log_printf( &logger, "Gyro Z  : %d  |  ", gyroZ);
    log_printf( &logger, "Mag Z   : %d  |  ", magZ);
    log_printf( &logger, "Press.  : %.2f mbar \r\n", pressure);

    log_printf( &logger, "--------------------------------------------------------------------\r\n", pressure);
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
