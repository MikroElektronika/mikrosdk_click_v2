\mainpage Main Page

---
# 6DOF IMU 18 click

> 6DOF IMU 18 Click is a compact add-on board with a 6-axis inertial measurement unit. This board features the ICM-42605, a high-performance 6-axis MotionTracking™ IMU from TDK InvenSense.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-18-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOF IMU 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOF IMU 18 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This library contains API for 6DOF IMU 18 Click driver. 
> The library initializes and defines the I2C and SPI bus drivers to 
  write and read data from registers, as well as the default 
  configuration for reading gyroscope and accelerator data, and temperature.

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );
    
    uint8_t id = 0;
    c6dofimu18_reg_read( &c6dofimu18, C6DOFIMU18_BANK0_SEL, C6DOFIMU18_REG_WHO_AM_I, &id, 1);
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) id );
    if ( C6DOFIMU18_WHO_AM_I_VALUE != id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
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
        Delay_ms( 1000 );
    }    
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
