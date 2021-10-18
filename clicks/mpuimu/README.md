\mainpage Main Page
 
 

---
# MPU IMU click

MPU IMU Click carries the integrated 6-axis motion tracking device that combines 3-axis gyroscope and accelerometer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mpuimu_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mpu-imu-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the MpuImu Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MpuImu Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mpuimu_cfg_setup ( mpuimu_cfg_t *cfg ); 
 
- Initialization function.
> MPUIMU_RETVAL mpuimu_init ( mpuimu_t *ctx, mpuimu_cfg_t *cfg );

- Click Default Configuration function.
> void mpuimu_default_cfg ( mpuimu_t *ctx );

#### Example key functions :

- This function read Accel X-axis, Y-axis and Z-axis.
> void mpuimu_read_accel ( mpuimu_t *ctx, mpuimu_accel_data_t *accel_data );
 
- This function read Gyro X-axis, Y-axis and Z-axis.
> void mpuimu_read_gyro ( mpuimu_t *ctx, mpuimu_gyro_data_t *gyro_data );

- This function reads temperature data.
> float mpuimu_read_temperature ( mpuimu_t *ctx );

## Examples Description

> 
> Example code performs acceleration, angular rate (gyroscopic), and temperature measurement.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mpuimu_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    mpuimu_cfg_setup( &cfg );
    MPUIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpuimu_init( &mpuimu, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----  MPU IMU Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mpuimu_default_cfg ( &mpuimu );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Measured Accel and Gyro coordinates (X,Y,Z) and Temperature in degrees C 
> which are being sent to the UART where you can track their changes. 
> All data logs on USB UART for every 1 sec.
> 

```c

void application_task ( void )
{
    mpuimu_read_accel( &mpuimu, &accel_data );
    Delay_ms ( 100 );
    mpuimu_read_gyro( &mpuimu, &gyro_data );
    Delay_ms ( 100 );
    temperature = mpuimu_read_temperature( &mpuimu );
    Delay_ms ( 100 );
    
    log_printf( &logger, "    Accel    |    Gyro    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " X = %d  | X = %d \r\n", accel_data.accel_x, gyro_data.gyro_x );
    log_printf( &logger, " Y = %d  | Y = %d \r\n", accel_data.accel_y, gyro_data.gyro_y );
    log_printf( &logger, " Z = %d  | Z = %d \r\n", accel_data.accel_z, gyro_data.gyro_z );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      TEMP = %0.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" ); 
    
    software_reset ( &mpuimu );
    Delay_ms ( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MpuImu

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
