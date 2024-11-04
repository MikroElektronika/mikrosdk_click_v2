\mainpage Main Page
 
---
# 9DOF 3 Click

9DOF 3 Click introduces the BMX055, a small-scale absolute orientation sensor in the class of low-noise 9-axis measurement units, from Bosch Sensortec. It comprises the full functionality of a triaxial, low-g acceleration sensor, a triaxial angular rate sensor and a triaxial geomagnetic sensor. All three sensor components of the BMX055 can be operated and addressed independently from each other. On top, the BMX055 integrates a multitude of features that facilitate its use especially in the area of motion detection applications, such as device orientation measurement, gaming, HMI or menu browser control. 9DOF 3 Click offers both SPI and I2C digital interfaces for easy and fast system integration.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/9dof3_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/9dof-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 9Dof3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 9Dof3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c9dof3_cfg_setup ( c9dof3_cfg_t *cfg ); 
 
- Initialization function.
> C9DOF3_RETVAL c9dof3_init ( c9dof3_t *ctx, c9dof3_cfg_t *cfg );

- Click Default Configuration function.
> void c9dof3_default_cfg ( c9dof3_t *ctx );


#### Example key functions :

- The function check device ID for accelerometer, gyroscope and magnetometer.
> uint8_t c9dof3_check_communication ( c9dof3_t *ctx );
 
- Function read Accel, Gyro and Mag X-axis, Y-axis data and Z-axis data.
> void c9dof3_get_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data, c9dof3_gyro_t *gyro_data, c9dof3_mag_t *mag_data );

- This function reads data from the desired register.
> void c9dof3_generic_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This Click introduces a small-scale absolute orientation sensor in the class of low-noise 
> 9-axis measurement units. It comprises the full functionality of a triaxial, low-g acceleration 
> sensor, a triaxial angular rate sensor and a triaxial geomagnetic sensor. All three sensor 
> components can be operated and addressed independently from each other. 9DOF 3 Click offers 
> both SPI and I2C digital interfaces

**The demo application is composed of two sections :**

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


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.9Dof3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
