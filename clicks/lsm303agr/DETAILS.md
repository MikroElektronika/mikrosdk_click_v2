

---
# LSM303AGR click

LSM303AGR click is a magnetometer and accelerometer device, capable of sensing both the magnetic and gravitational field along three orthogonal axes. It uses the LSM303AGR from STMicroelectronics, an integrated MEMS IC with plenty of features that allow accurate and reliable sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lsm303agr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lsm303agr-click-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the LSM303AGR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LSM303AGR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lsm303agr_cfg_setup ( lsm303agr_cfg_t *cfg ); 
 
- Initialization function.
> LSM303AGR_RETVAL lsm303agr_init ( lsm303agr_t *ctx, lsm303agr_cfg_t *cfg );

- Click Default Configuration function.
> void lsm303agr_default_cfg ( lsm303agr_t *ctx );


#### Example key functions :

- Reading the raw X axis data and calculating the value
> float lsm303agr_get_acc_axis_x ( lsm303agr_t *ctx );
 
- Reading the raw X axis data and calculating the value
> float lsm303agr_get_mag_axis_x ( lsm303agr_t *ctx );

- Reading the raw Y axis data and calculating the value
> float lsm303agr_get_mag_axis_y ( lsm303agr_t *ctx );

## Examples Description

> This demo example returns magnetic and acceleration values from the LSM303AGR sensor.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization and setting operating modes of accelerometer and magnetometer.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm303agr_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lsm303agr_cfg_setup( &cfg );
    LSM303AGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm303agr_init( &lsm303agr, &cfg );
    lsm303agr_default_cfg ( &lsm303agr );
   
}
  
```

### Application Task

> Reading accelerometer and magnetometer axis X,Y,Z and displaying it on terminal.

```c

void application_task ( void )
{
    //  Task implementation.

    log_printf(&logger, "======== Accelerometer data ========\r\n");
    
    read_data = lsm303agr_get_acc_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %f\r\n", read_data);
    
    log_printf(&logger, "======== Mangetometer data ========\r\n");
    
    read_data = lsm303agr_get_mag_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %f\r\n", read_data);

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LSM303AGR

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
