\mainpage Main Page
 
 

---
# Compass Click

Compass Click is an add-on board in mikroBUS form factor. It features LSM303DLHC ultra compact high performance e-compass module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/compass-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Compass Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void compass_cfg_setup ( compass_cfg_t *cfg ); 
 
- Initialization function.
> COMPASS_RETVAL compass_init ( compass_t *ctx, compass_cfg_t *cfg );

- Click Default Configuration function.
> void compass_default_cfg ( compass_t *ctx );


#### Example key functions :

- This function reads data for megnetic axes.
> void compass_read_magnet_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
 
- This function reads data for accelerometer axes.
> void compass_read_accel_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

- This function writes magnet data to the desired register.
> void compass_magnet_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This application measures magnetic and accelerometer axes data and shows them over USBUART

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and init chip

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass_cfg_t cfg;

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

    compass_cfg_setup( &cfg );
    COMPASS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass_init( &compass, &cfg );
    compass_default_config( &compass );
}
  
```

### Application Task

> Read magnet axis data and accel axis data and logs data on USBUART every 1 sec. 

```c
void application_task ( void )
{
    int16_t accel_axis[ 3 ];
    int16_t magnet_axis[ 3 ];
    
    compass_read_magnet_axis( &compass, &magnet_axis[ 0 ], &magnet_axis[ 1 ], &magnet_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", magnet_axis[ 0 ], magnet_axis[ 1 ], magnet_axis[ 2 ] );
  
    compass_read_accel_axis ( &compass, &accel_axis[ 0 ], &accel_axis[ 1 ], &accel_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", accel_axis[ 0 ], accel_axis[ 1 ], accel_axis[ 2 ] );
   
    log_printf( &logger, " \r\n");
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass

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
