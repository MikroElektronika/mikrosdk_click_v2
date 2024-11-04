\mainpage Main Page
 
---
# Gyro 2 Click

The Gyro 2 Click is a three-axis digital angular rate sensor which can sense the angular movement and velocity in three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gyro-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Gyro2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gyro2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gyro2_cfg_setup ( gyro2_cfg_t *cfg ); 
 
- Initialization function.
> GYRO2_RETVAL gyro2_init ( gyro2_t *ctx, gyro2_cfg_t *cfg );

- Click Default Configuration function.
> void gyro2_default_cfg ( gyro2_t *ctx );


#### Example key functions :

- Function will return the ID from the ID register
> uint8_t gyro2_get_id ( gyro2_t *ctx );
 
- Function will read the X, Y and Z axis registers.
- Data that is read is storred the 3 16bit array.
> void gyro2_get_axisraw ( gyro2_t *ctx, int16_t *axis_data );

- Function for calculating raw axis data.
> void gyro2_calc_axis ( int16_t *axis_data );

## Examples Description

> This application enables usage of 3 angular movement and velocity sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialize the communication interface and configure the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro2_cfg_t cfg;
    uint8_t temp;

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

    gyro2_cfg_setup( &cfg );
    GYRO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    gyro2_init( &gyro2, &cfg );

    temp = gyro2_default_cfg( &gyro2 );

    if ( temp == 1 )
    {
        log_printf( &logger, "Gyro 2 present\r\n" );
    }
    else if ( temp == 2 )
    {
        log_printf( &logger, "Error\r\n" );
    }
    Delay_ms ( 100 );
}
  
```

### Application Task

> Read the x,y,z and temperature data from the Click board and display the resoults on the
> serial port.

```c

void application_task ( void )
{
    //  Task implementation.

    int16_t axis_data[ 3 ];
    uint8_t temperature;

    gyro2_get_axisraw( &gyro2, axis_data );
    gyro2_calc_axis( axis_data );

    log_printf( &logger, "x: %d \r\ny: %d \r\nz: %d \r\n", axis_data[ 0 ], axis_data[ 1 ], axis_data[ 2 ] );

    temperature = gyro2_read_temperature( &gyro2 );

    log_printf( &logger, "Temperature: %d C\r\n ++ \r\n", temperature );

    Delay_ms ( 200 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro2

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