\mainpage Main Page
 
 

---
# Magneto 7 click

Magneto 7 Click is a high-resolution magnetic sensor Click board™ which allows contactless orientation sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto7_cfg_setup ( magneto7_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO7_RETVAL magneto7_init ( magneto7_t *ctx, magneto7_cfg_t *cfg );

- Click Default Configuration function.
> void magneto7_default_cfg ( magneto7_t *ctx );


#### Example key functions :

- This function returns INT pin state
> uint8_t magneto7_int_get ( magneto7_t *ctx );
 
- This function gets register value(s).
> uint8_t magneto7_get_register ( magneto7_t *ctx, uint8_t register_address, uint8_t * data_buffer, uint8_t n_data );

- This function gets raw device temperature value.
> void magneto7_get_temperature ( magneto7_t *ctx, uint16_t *device_temperature );

## Examples Description

> This demo application reads position of a magnet above the sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto7_cfg_t cfg;
    uint8_t init_status;

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

    magneto7_cfg_setup( &cfg );
    MAGNETO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto7_init( &magneto7, &cfg );
    Delay_ms( 300 );

    init_status = magneto7_default_cfg( &magneto7 );
    if ( init_status == 0)
    {
        log_printf( &logger, "> app init done\r\n" );
    }
    else if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
        for ( ; ; );
    }
}
```

### Application Task

> Waits for INT pin to go LOW, gets raw data, converts it to uT and logs results.

```c
void application_task ( void )
{
    uint8_t int_status;
    float converted_data;

    int16_t data_x;
    int16_t data_y;
    int16_t data_z;

    int_status = magneto7_int_get( &magneto7 );
    
    if ( int_status == 0 )
    {
        magneto7_get_data( &magneto7, &data_x, &data_y, &data_z );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_x, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> X Axis : %f [uT]\r\n", converted_data );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_y, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Y Axis : %f [uT]\r\n", converted_data );

        converted_data = magneto7_convert_to_ut( &magneto7, data_z, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Z Axis : %f [uT]\r\n", converted_data );

        log_printf( &logger, "\r\n" );
        
        Delay_ms( 300 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto7

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
