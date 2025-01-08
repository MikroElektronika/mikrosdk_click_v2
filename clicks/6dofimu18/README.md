
---
# 6DOF IMU 18 Click

> [6DOF IMU 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5591) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5591&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for 6DOF IMU 18 Click driver. 
> The library initializes and defines the I2C and SPI bus drivers to 
  write and read data from registers, as well as the default 
  configuration for reading gyroscope and accelerator data, and temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU18

### Example Key Functions

- `c6dofimu18_cfg_setup` Config Object Initialization function.
```c
void c6dofimu18_cfg_setup ( c6dofimu18_cfg_t *cfg );
```

- `c6dofimu18_init` Initialization function.
```c
err_t c6dofimu18_init ( c6dofimu18_t *ctx, c6dofimu18_cfg_t *cfg );
```

- `c6dofimu18_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu18_default_cfg ( c6dofimu18_t *ctx );
```

- `c6dofimu18_set_reg_bank` 6DOF IMU 18 set register bank function.
```c
err_t c6dofimu18_set_reg_bank( c6dofimu18_t *ctx, uint8_t bank );
```

- `c6dofimu18_get_int1_state` 6DOF IMU 18 read INT1 pin state function.
```c
uint8_t c6dofimu18_get_int1_state ( c6dofimu18_t *ctx );
```

- `c6dofimu18_get_data_from_register` 6DOF IMU 18 read data function.
```c
err_t c6dofimu18_get_data_from_register ( c6dofimu18_t *ctx, float *temperature_data, c6dofimu18_data_t *accel_data, c6dofimu18_data_t *gyro_data, uint32_t *tmst_data );
```

### Application Init

> Initializes the driver after that resets the device and performs default configuration and reads the device id.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu18_cfg_t c6dofimu18_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    c6dofimu18_cfg_setup( &c6dofimu18_cfg );
    C6DOFIMU18_MAP_MIKROBUS( c6dofimu18_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu18_init( &c6dofimu18, &c6dofimu18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    uint8_t id = 0;
    c6dofimu18_reg_read( &c6dofimu18, C6DOFIMU18_BANK0_SEL, C6DOFIMU18_REG_WHO_AM_I, &id, 1);
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) id );
    if ( C6DOFIMU18_WHO_AM_I_VALUE != id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( C6DOFIMU18_OK != c6dofimu18_default_cfg ( &c6dofimu18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the 6DOF IMU 18 Click board by 
  measuring and displaying acceleration and gyroscope data for X-axis, 
  Y-axis, and Z-axis as well as temperature in degrees Celsius.

```c
void application_task ( void )
{
    if ( c6dofimu18_get_int1_state( &c6dofimu18) )
    {       
        c6dofimu18_data_t accel_data;
        c6dofimu18_data_t gyro_data;
        float temp_data;
        uint32_t tmst_data;
        
        c6dofimu18_get_data_from_register( &c6dofimu18, &temp_data, &accel_data, &gyro_data, &tmst_data );
        log_printf( &logger, " TEMP: %.2f \r\n", temp_data );
        log_printf( &logger, " GYRO: x:%d y:%d z:%d \r\n", gyro_data.data_x,gyro_data.data_y,gyro_data.data_z );
        log_printf( &logger, " ACCEL: x:%d y:%d z:%d \r\n", accel_data.data_x,accel_data.data_y,accel_data.data_z );
        log_printf( &logger, "========================== \r\n" );
        Delay_ms ( 1000 );
    }
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
