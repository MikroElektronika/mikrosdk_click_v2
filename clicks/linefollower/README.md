\mainpage Main Page
 
 

---
# Line Follower Click

Line Follower Click carries an array of five QRE1113 miniature reflective object sensors. As the name implies, Line Follower Click is best used for line following robots and cars.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/linefollower_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/line-follower-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the LineFollower Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LineFollower Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void linefollower_cfg_setup ( linefollower_cfg_t *cfg ); 
 
- Initialization function.
> LINEFOLLOWER_RETVAL linefollower_init ( linefollower_t *ctx, linefollower_cfg_t *cfg );

- Click Default Configuration function.
> void linefollower_default_cfg ( linefollower_t *ctx );


#### Example key functions :

- Get status of all pin function
> void linefollower_data_track ( linefollower_t *ctx, linefollower_direction_t *data_track );

## Examples Description

> Line Follower Click carries an array of five QRE1113 
> miniature reflective object sensors,
> reading staus of AN, RST, PWM, TX and RX pins and reading tracking data.

**The demo application is composed of two sections :**

### Application Init 

> Application Init performs logger and Click Initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    linefollower_cfg_t cfg;

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
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " - Application Init -\r\n" );

    //  Click initialization.
    linefollower_cfg_setup( &cfg );
    LINEFOLLOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linefollower_init( &linefollower, &cfg );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Line Follower  Click \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}
  
```

### Application Task

> Application Task shows the functionality of the Line Follower Click.
> Each one of the QRE1113 sensors consist of an
> infrared transmitter and infrared receiver. 
> By default the sensor output a Logic Level 1, until they encounter a 
> white surface which changes the output signal to 0.

```c

void application_task ( void )
{
    linefollower_direction_t data_track;
    
    linefollower_data_track ( &linefollower, &data_track );
    
    log_printf( &logger, " %u\t%u\t%u\t%u\t%u\r\n", 
                (uint16_t) data_track.u1, 
                (uint16_t) data_track.u2, 
                (uint16_t) data_track.u3, 
                (uint16_t) data_track.u4, 
                (uint16_t) data_track.u5);
    
    Delay_ms ( 100 );
} 

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LineFollower

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
