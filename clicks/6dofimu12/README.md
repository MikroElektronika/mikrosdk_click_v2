\mainpage Main Page
 
---
# 6DOF IMU 12 click

6DOF IMU 12 Click carries the ultra-low-power BMI270 from Bosch Sensortec, inertial measurement unit optimized for wearables providing precise acceleration, angular rate measurement and intelligent on-chip motion-triggered interrupt features.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-12-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the C6DofImu12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for C6DofImu12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu12_cfg_setup ( c6dofimu12_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU12_RETVAL c6dofimu12_init ( c6dofimu12_t *ctx, c6dofimu12_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu12_default_cfg ( c6dofimu12_t *ctx );


#### Example key functions :

- Function check status initialization of the device
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
> C6DOFIMU12_RETVAL c6dofimu12_check_id ( c6dofimu12_t *ctx );
 
- Function check status initialization of the device
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
> C6DOFIMU12_RETVAL c6dofimu12_check_init_status ( c6dofimu12_t *ctx );

- Function reads Accel and Gyro 16-bit ( signed )
  X-axis, Y-axis data and Z-axis data from the 12
  targeted starts from C6DOFIMU12_REG_ACC_X_LSB_ADDR register address
  of BMI270 6-axis, smart, low-power Inertial Measurement
  on 6DOF IMU 12 Click board.
> void c6dofimu12_get_data ( c6dofimu12_t *ctx, c6dofimu12_accel_t *accel_data, c6dofimu12_gyro_t *gyro_data );

## Examples Description

> This example demonstrates the use of 6DOF IMU 12 click board.

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );

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
    Delay_ms( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_START;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms( 100 );
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_DATA_ADDR, bmi270_config_file, 8192 );
    Delay_ms( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_STOP;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms( 100 );

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
    Delay_ms( 100 );
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
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.C6DofImu12

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
