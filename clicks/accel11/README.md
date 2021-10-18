\mainpage Main Page
 
 

---
# Accel 11 click

Accel 11 click features an ultra-low power triaxial accelerometer sensor with embedded intelligence, labeled as the BMA456.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel11_cfg_setup ( accel11_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL11_RETVAL accel11_init ( accel11_t *ctx, accel11_cfg_t *cfg );

- Click Default Configuration function.
> void accel11_default_cfg ( accel11_t *ctx );


#### Example key functions :

- This function reads accel axis.
> int16_t accel11_get_axis_data ( accel11_t *ctx, uint8_t axis );
 
- This function test comunication.
> uint8_t accel11_test_comunication ( accel11_t *ctx );

- This function for power on chip.
> void accel11_power_on_procedure ( accel11_t *ctx );

## Examples Description

> This demo application reads X / Y / Z axis acceleration data.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    uint8_t tmp;
    log_cfg_t log_cfg;
    accel11_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    accel11_cfg_setup( &cfg );
    ACCEL11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel11_init( &accel11, &cfg );

    tmp = accel11_test_comunication( &accel11 );
    if ( tmp == ACCEL11_TEST_COMUNICATION_OK )
    {
        log_printf( &logger, " Comunication OK !!!\r\n" );
    }
    else
    {
        log_printf( &logger, " Comunication ERROR !!!\r\n" );
        for ( ; ; );
    }
    accel11_default_cfg( &accel11 );
}
  
```

### Application Task

> Reads X / Y / Z axis acceleration data and it logs to USBUART every 1500ms.

```c

void application_task ( void )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_X_AXIS );
    log_printf( &logger, " X axis : %d\r\n", x_axis );

    y_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Y_AXIS );
    log_printf( &logger, " Y axis : %d\r\n", y_axis );

    z_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Z_AXIS );
    log_printf( &logger, " Z axis : %d\r\n", z_axis );

    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 1500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel11

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
