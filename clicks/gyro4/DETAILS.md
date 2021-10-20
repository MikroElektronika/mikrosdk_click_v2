
---
# Gyro 4 click

Gyro 4 Click  is a two-axis MEMS gyroscope for optical image stabilization applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Gyro4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gyro4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gyro4_cfg_setup ( gyro4_cfg_t *cfg ); 
 
- Initialization function.
> GYRO4_RETVAL gyro4_init ( gyro4_t *ctx, gyro4_cfg_t *cfg );

- Click Default Configuration function.
> void gyro4_default_cfg ( gyro4_t *ctx );


#### Example key functions :

- Getting register content
> uint8_t gyro4_spi_get ( gyro4_t *ctx, uint8_t register_address, uint8_t * register_buffer, uint16_t n_registers );
 
- Getting die temperature value
> uint8_t gyro4_get_temperature ( gyro4_t *ctx, float * temperature );

- Getting axes values
> uint8_t gyro4_get_axes( gyro4_t *ctx, float * x_axis, float * y_axis );

## Examples Description

> This application is a two-axis MEMS gyroscope for optical image stabilization.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI device

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro4_cfg_t cfg;
    uint8_t initialize_flag;

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

    gyro4_cfg_setup( &cfg );
    GYRO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro4_init( &gyro4, &cfg );

    Delay_ms( 500 );
    initialize_flag = gyro4_initialize( &gyro4 );
    if ( initialize_flag == 1 )
    {
        log_printf( &logger, "> App init fail \r\n" );
    }
    else if ( initialize_flag == 0 )
    {
        log_printf( &logger, "> App init done \r\n" );
    }
}
  
```

### Application Task

> Checks for data ready interrupt, gets axes and temperature data and logs those values

```c

void application_task ( )
{
    uint8_t int_flag;
    float x_axis;
    float y_axis;
    float die_temperature;
    char degrees_celsius[ 4 ] = { ' ', 176, 'C', 0x00 };
    char degrees_per_second[ 5 ] = { ' ', 176, '/', 's', 0x00 };

    int_flag = gyro4_int_get( &gyro4 );
    while ( int_flag == 1 )
    {
        int_flag = gyro4_int_get( &gyro4 );
    }
    
    gyro4_get_temperature( &gyro4, &die_temperature );
    gyro4_get_axes( &gyro4, &x_axis, &y_axis );

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "> Die temperature : %.2f %c \r\n", die_temperature, degrees_celsius );
    log_printf( &logger, "> X axis : %.2f %c \r\n", x_axis, degrees_per_second );
    log_printf( &logger, "> Y axis : %.2f %c \r\n", y_axis, degrees_per_second );

    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro4

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
