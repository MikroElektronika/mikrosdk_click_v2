
---
# 9DOF 3 Click

> [9DOF 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4153) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4153&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This Click introduces a small-scale absolute orientation sensor in the class of low-noise 
> 9-axis measurement units. It comprises the full functionality of a triaxial, low-g acceleration 
> sensor, a triaxial angular rate sensor and a triaxial geomagnetic sensor. All three sensor 
> components can be operated and addressed independently from each other. 9DOF 3 Click offers 
> both SPI and I2C digital interfaces

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.9Dof3

### Example Key Functions

- `c9dof3_cfg_setup` Config Object Initialization function. 
```c
void c9dof3_cfg_setup ( c9dof3_cfg_t *cfg );
``` 
 
- `c9dof3_init` Initialization function. 
```c
err_t c9dof3_init ( c9dof3_t *ctx, c9dof3_cfg_t *cfg );
```

- `c9dof3_default_cfg` Click Default Configuration function. 
```c
void c9dof3_default_cfg ( c9dof3_t *ctx );
```

- `c9dof3_check_communication` The function check device ID for accelerometer, gyroscope and magnetometer. 
```c
uint8_t c9dof3_check_communication ( c9dof3_t *ctx );
```
 
- `c9dof3_get_data` Function read Accel, Gyro and Mag X-axis, Y-axis data and Z-axis data. 
```c
void c9dof3_get_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data, c9dof3_gyro_t *gyro_data, c9dof3_mag_t *mag_data );
```

- `c9dof3_generic_read` This function reads data from the desired register. 
```c
void c9dof3_generic_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initialization driver enables - I2C or SPI, check communication, 
> set default configuration for accelerometer, gyroscope and magnetometer, also write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof3_cfg_t cfg;

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

    c9dof3_cfg_setup( &cfg );
    C9DOF3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof3_init( &c9dof3, &cfg );
    Delay_ms ( 100 );

    if ( c9dof3_check_communication( &c9dof3 ) == ( C9DOF3_ACC_COMM_SUCCESS  |
                                                    C9DOF3_GYRO_COMM_SUCCESS |
                                                    C9DOF3_MAG_COMM_SUCCESS ) )
    {
        log_printf( &logger, "    Communication OK     \r\n" );
    }
    else
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    c9dof3_default_cfg( &c9dof3 );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example which demonstrates the use of 9DOF 3 Click board.
> Measures and displays Accel, Gyroscope and Magnetometer values for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( void )
{
    c9dof3_get_data ( &c9dof3, &accel_data, &gyro_data, &mag_data );

    log_printf( &logger, " Accel X: %d | Gyro X: %d |  Mag X: %d\r\n", accel_data.x, gyro_data.x, mag_data.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d |  Mag Y: %d\r\n", accel_data.y, gyro_data.y, mag_data.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d |  Mag Z: %d\r\n", accel_data.z, gyro_data.z, mag_data.z );

    log_printf( &logger, "------------------------------------------\r\n" );

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
