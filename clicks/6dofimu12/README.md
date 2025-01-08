
---
# 6DOF IMU 12 Click

> [6DOF IMU 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4073) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4073&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu12

### Example Key Functions

- `c6dofimu12_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu12_cfg_setup ( c6dofimu12_cfg_t *cfg );
``` 
 
- `c6dofimu12_init` Initialization function. 
```c
err_t c6dofimu12_init ( c6dofimu12_t *ctx, c6dofimu12_cfg_t *cfg );
```

- `c6dofimu12_default_cfg` Click Default Configuration function. 
```c
void c6dofimu12_default_cfg ( c6dofimu12_t *ctx );
```

- Function check status initialization of the device
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
err_t c6dofimu12_check_id ( c6dofimu12_t *ctx );
 
- Function check status initialization of the device
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
err_t c6dofimu12_check_init_status ( c6dofimu12_t *ctx );

- Function reads Accel and Gyro 16-bit ( signed )
  X-axis, Y-axis data and Z-axis data from the 12
  targeted starts from C6DOFIMU12_REG_ACC_X_LSB_ADDR register address
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
> void c6dofimu12_get_data ( c6dofimu12_t *ctx, c6dofimu12_accel_t *accel_data, c6dofimu12_gyro_t *gyro_data );

### Application Init

> Initializes the driver and checks the communication then initializes the device and sets the device default configuration.

```c
void application_init ( void )
{
    uint8_t tx_buf;

    log_cfg_t log_cfg;
    c6dofimu12_cfg_t cfg;

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

    c6dofimu12_cfg_setup( &cfg );
    C6DOFIMU12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu12_init( &c6dofimu12, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, " Driver init done \r\n" );
    log_printf( &logger, "----------------------------------\r\n");
    
    if ( c6dofimu12_check_id( &c6dofimu12 ) == C6DOFIMU12_SUCCESS )
    {
        log_printf( &logger, "  Communication OK\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
    }
    else
    {
        log_printf( &logger, " Communication ERROR\r\n" );
        log_printf( &logger, " Reset the device\r\n" );
        log_printf( &logger, "----------------------------------\r\n");

        for ( ; ; );
    }
    
    tx_buf = C6DOFIMU12_PWR_CONF_ADV_PWR_SAVE_DISABLED | 
             C6DOFIMU12_FIFO_READ_DISABLED | 
             C6DOFIMU12_FAST_PWR_UP_DISABLED;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_PWR_CONF_ADDR, &tx_buf, 1 );
    Delay_ms ( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_START;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms ( 100 );
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_DATA_ADDR, bmi270_config_file, 8192 );
    Delay_ms ( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_STOP;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms ( 100 );

    if ( c6dofimu12_check_init_status( &c6dofimu12 ) == C6DOFIMU12_SUCCESS )
    {
        log_printf( &logger, " Initialization completed\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
    }
    else
    {
        log_printf( &logger, " Initialization ERROR\r\n" );
        log_printf( &logger, " Reset the device\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
        
        for( ; ; );
    }
    c6dofimu12_default_cfg( &c6dofimu12 );
    Delay_ms ( 100 );
}
```

### Application Task

> Measures acceleration and gyroscope data and displays the results on USB UART each second.

```c
void application_task ( void )
{
    c6dofimu12_get_data( &c6dofimu12, &c6dofimu12_accel, &c6dofimu12_gyro );

    log_printf( &logger, " Accel X: %d | Gyro X: %d\r\n", c6dofimu12_accel.x, c6dofimu12_gyro.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d\r\n", c6dofimu12_accel.y, c6dofimu12_gyro.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d\r\n", c6dofimu12_accel.z, c6dofimu12_gyro.z );
    log_printf( &logger, "----------------------------------\r\n");
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
