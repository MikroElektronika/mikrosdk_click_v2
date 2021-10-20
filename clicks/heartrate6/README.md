\mainpage Main Page
 
---
# Heart rate 6 click

Heart rate 6 Click is an optical biosensor Click board™ designed for heart-rate monitoring (HRM). This Click board™ employs a specialized sensor that incorporates two LED drivers and photo-sensing elements which are the most sensitive to green light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate6_cfg_setup ( heartrate6_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE6_RETVAL heartrate6_init ( heartrate6_t *ctx, heartrate6_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate6_default_cfg ( heartrate6_t *ctx );


#### Example key functions :

- Function reads the LED Data as 16bit unsigned value.
> void heartrate6_get_data ( heartrate6_t *ctx, uint16_t *led_off_data, uint16_t *led_on_data );
 
- Function sets the data reading frequency and the LED pulse frequency.
> void heartrate6_set_freq ( heartrate6_t *ctx, uint8_t freq_data );

- Function starts measurement cycle.
> void heartrate6_start_measure ( heartrate6_t *ctx );

## Examples Description

> The example demonstrates the use of Heart rate 6 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes interface and performs the device configuration and reset.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate6_cfg_t cfg;

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

    heartrate6_cfg_setup( &cfg );
    HEARTRATE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate6_init( &heartrate6, &cfg );
    Delay_ms( 500 );

    heartrate6_default_cfg( &heartrate6 );
    log_printf( &logger, " Heart rate 6 is initialized. \r\n");
    Delay_ms( 500 );
}
  
```

### Application Task

> Waits until measurement cycle is finished and data is ready for reading. 
> Then reads the LED data and performs the data plotting on USB UART.

```c

void application_task ( void )
{
    heartrate6_wait_measure( &heartrate6 );
    
    heartrate6_get_data( &heartrate6,  &led_data_off, &led_data_on );
    
    counter++;
    if ( led_data_off < 200 )
    {
        log_printf( &logger, "%u;\r\n", led_data_on );
        counter = 200;
    }
    else if ( counter > 200 )
    {
        log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
        counter = 0;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate6

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
