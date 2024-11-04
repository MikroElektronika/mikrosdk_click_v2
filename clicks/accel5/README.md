\mainpage Main Page
 
 

---
# Accel 5 Click

Accel 5 Click features an ultra-low power triaxial accelerometer sensor, labeled as the BMA400. This Click board™ allows linear motion and gravitational force measurements in ranges of ±2 g, ±4 g, ±8, and ±16 g in three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel5_cfg_setup ( accel5_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL5_RETVAL accel5_init ( accel5_t *ctx, accel5_cfg_t *cfg );

- Click Default Configuration function.
> void accel5_default_cfg ( accel5_t *ctx );


#### Example key functions :

- Functions for write one byte in register
> void accel5_write_byte ( accel5_t *ctx, uint8_t reg, uint8_t reg_data );
 
- Functions for read byte from register.
> uint8_t accel5_read_byte ( accel5_t *ctx, uint8_t reg );

- Functions for read data from register.
> uint16_t accel5_read_data ( accel5_t *ctx, uint8_t reg );

## Examples Description
 
> This application allows linear motion and gravitational force measurements. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and settings accelerometer data range and mode.

```c

void application_init ( void )
{
log_cfg_t log_cfg;
    accel5_cfg_t cfg;

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

    accel5_cfg_setup( &cfg );
    ACCEL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel5_init( &accel5, &cfg );
}
  
```

### Application Task

> Reads the accel X / Y / Z axis data, every 500 ms.

```c

void application_task ( void )
{
    x_axis_data = accel5_get_axis( &accel5, ACCEL5_X_AXIS );
    log_printf ( &logger, " X axis : %d \r\n  ", x_axis_data );
    
    y_axis_data = accel5_get_axis( &accel5, ACCEL5_Y_AXIS );
    log_printf ( &logger, " Y axis : %d \r\n  ", y_axis_data );

    z_axis_data = accel5_get_axis( &accel5, ACCEL5_Z_AXIS );
    log_printf ( &logger, " Z axis : %d \r\n  ", z_axis_data );
    
    Delay_ms ( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel5

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
