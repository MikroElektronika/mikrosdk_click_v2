\mainpage Main Page
 
 

---
# Heart Rate 8 Click

Heart Rate 8 Click is an optical biosensor Click board™, designed for heart-rate monitoring (HRM). This Click board™ employs a specialized sensor that incorporates three LED drivers and two photo-sensing elements, sensitive to green and IR light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/heart-rate-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate8_cfg_setup ( heartrate8_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE8_RETVAL heartrate8_init ( heartrate8_t *ctx, heartrate8_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate8_default_cfg ( heartrate8_t *ctx );


#### Example key functions :

- Function gets the selected data from the determined LED Data registers.

> uint8_t heartrate8_get_data ( heartrate8_t *ctx, uint8_t data_select, uint16_t *led_out_on, uint16_t *led_out_off );

 
- Function checks INT pin, is interrupt occured or not.
> uint8_t heartrate8_check_int ( heartrate8_t *ctx );


- Function performs the measurement synchronization.
> void heartrate8_meas_sync ( heartrate8_t *ctx );


## Examples Description

> This example demonstrates the use of Hearth rate 8 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Performs the device reset.  The device is configured to work in Single Measurement Mode with LED pulsing.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate8_cfg_t cfg;

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
    log_info( &logger, "---- Application Initializing ----" );

    //  Click initialization.

    heartrate8_cfg_setup( &cfg );
    HEARTRATE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate8_init( &heartrate8, &cfg );
    Delay_ms ( 500 );
    heartrate8_default_cfg( &heartrate8 );
    i = 0;

    log_printf( &logger, "HeartRate 8 is initialized\n");
}
  
```

### Application Task

> Sends command to start measurement cycle, then waits until measurement cycle is finished. When measurement cycle is done, gets LED ON and LED OFF Data for the selected LED driver (GREEN or IR LED) and performs data plotting on serial plotter every 35ms.
 

```c

void application_task ( void )
{
    heartrate8_start_measure( &heartrate8 );
    
    int_check = heartrate8_check_int( &heartrate8 );
    while (int_check != HEARTRATE8_INT_ACTIVE)
    {
        int_check = heartrate8_check_int( &heartrate8 );
    }
    
    heartrate8_get_data( &heartrate8, HEARTRATE8_GREEN_DATA_GET, &led_data_on, &led_data_off );
    plot_res( led_data_on );
    int_check = heartrate8_int_clear( &heartrate8 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate8

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
