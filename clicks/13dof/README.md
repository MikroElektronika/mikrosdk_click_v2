
---
# 13DOF Click

> [13DOF Click](https://www.mikroe.com/?pid_product=MIKROE-3775) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3775&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example displays values registered by sensors on Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.13DOF

### Example Key Functions

- `c13dof_cfg_setup` Config Object Initialization function. 
```c
void c13dof_cfg_setup ( c13dof_cfg_t *cfg );
``` 
 
- `c13dof_init` Initialization function. 
```c
err_t c13dof_init ( c13dof_t *ctx, c13dof_cfg_t *cfg );
```

- `c13dof_default_cfg` Click Default Configuration function. 
```c
void c13dof_default_cfg ( c13dof_t *ctx );
```

- `c13dof_bmi088_read_accel` Function reads 16-bit X-axis, Y-axis data and Z-axis data. 
```c
void c13dof_bmi088_read_accel ( c13dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
```
 
- `c13dof_bmi088_accel_read_bytes` Function read a sequential data starting from the targeted 8-bit register address. 
```c
err_t c13dof_bmi088_accel_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes );
```

- `c13dof_bmi088_read_gyro` Function reads 16-bit X-axis, Y-axis data and Z-axis data of BMM150 sensor on 13DOF Click board. 
```c
void c13dof_bmi088_read_gyro ( c13dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );
```

### Application Init

> Initialization driver enables -
> BME680 Low power gas, pressure, temperature & humidity sensor, 
> BMI088 6-axis Motion Tracking Sensor and
> BMM150 Geomagnetic Sensor, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c13dof_cfg_t cfg;

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

    c13dof_cfg_setup( &cfg );
    C13DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c13dof_init( &c13dof, &cfg );
    c13dof_default_cfg( &c13dof );
}
```

### Application Task

> This is a example which demonstrates the use of 13DOF Click board.
> Measures and display temperature in degrees Celsius [ C ], humidity data [ % ], 
> pressure [ mbar ] and gas resistance data from the BME680 sensor.
> Measures and display Accel and Gyro data coordinates values 
> for X-axis, Y-axis and Z-axis from the BMI088 sensor.
> Measures and display Geomagnetic data coordinates values for 
> X-axis, Y-axis and Z-axis from the BMM150 sensor.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for each second.

```c
void application_task ( void )
{
    temperature = c13dof_bme680_get_temperature( &c13dof );

    log_printf( &logger, "----------------------------------------------------------\n");
    log_printf( &logger, "Temperature : %.2f C \r\n", temperature );

    humidity = c13dof_bme680_get_humidity( &c13dof );
    log_printf( &logger, "Humidity : %.2f %% \r\n", humidity );

    pressure = c13dof_bme680_get_pressure( &c13dof );
    log_printf( &logger, "Pressure : %.2f mbar \r\n", pressure );

    gas_res = c13dof_bme680_get_gas_resistance( &c13dof );
    log_printf( &logger, "Gas Resistance : %ld \r\n", gas_res );
    
    ready_check = c13dof_bmm150_check_ready( &c13dof );

    while ( ready_check != C13DOF_BMM150_DATA_READY )
    {
        ready_check = c13dof_bmm150_check_ready( &c13dof );
    }
    
    c13dof_bmi088_read_accel( &c13dof, &accel_x, &accel_y, &accel_z );
    c13dof_bmi088_read_gyro( &c13dof, &gyro_x, &gyro_y, &gyro_z );
    c13dof_bmm150_read_geo_mag_data( &c13dof, &mag_x, &mag_y, &mag_z, &r_hall );
    
    log_printf( &logger, "Accel X : %d ", accel_x );
    log_printf( &logger, " Y : %d ", accel_y );
    log_printf( &logger, " Z : %d \r\n", accel_z );
    
    log_printf( &logger, "Gyro X : %d ", gyro_x );
    log_printf( &logger, " Y : %d ", gyro_y );
    log_printf( &logger, " Z : %d \r\n", gyro_z );
        
    log_printf( &logger, "Mag X : %d ", mag_x );
    log_printf( &logger, " Y : %d ", mag_y );
    log_printf( &logger, " Z : %d \r\n", mag_z );

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
