\mainpage Main Page
 
---
# Index Counter click

Index Counter Click is a simple prototyping high precision Hall-Effect switch solution with direction detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/indexcounter_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/index-counter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the IndexCounter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IndexCounter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void indexcounter_cfg_setup ( indexcounter_cfg_t *cfg ); 
 
- Initialization function.
> INDEXCOUNTER_RETVAL indexcounter_init ( indexcounter_t *ctx, indexcounter_cfg_t *cfg );

- Click Default Configuration function.
> void indexcounter_default_cfg ( indexcounter_t *ctx );


#### Example key functions :

- This function returns a state of the direction DIR ( AN ) pin.
> uint8_t indexcounter_get_dir ( indexcounter_t *ctx );
 
- This function returns a state of the speed SPD ( RST ) pin.
> uint8_t indexcounter_get_speed ( indexcounter_t *ctx );

## Examples Description

> This application enables usage of Index counter click board which can be used to measure rotational speed.

**The demo application is composed of two sections :**

### Application Init 

> Initilaziation of GPIO and write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    indexcounter_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    indexcounter_cfg_setup( &cfg );
    INDEXCOUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    indexcounter_init( &indexcounter, &cfg );
}
  
```

### Application Task

> This is an example which demonstrates the use of the Index Counter click board.
> This example shows the direction of movement, Rotations Per Minute ( RPM or speed )
> of the three pairs of rotating poles positioned in the sensor operating range.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    //  Task implementation.

    speed_state = indexcounter_get_speed( &indexcounter );
    dir_state = indexcounter_get_dir( &indexcounter );

    if ( enable_speed && speed_state )
    {
        pulse_ms = time_cnt - start_timer;
        start_timer = time_cnt;
        speed_rpm = INDEXCOUNTER_ONE_MIN_CONV_MS / ( pulse_ms * n_pole_pairs );
        enable_speed = INDEXCOUNTER_SPEED_DISABLE;

        log_display ( speed_rpm );
    }

    if ( ( !enable_speed ) && ( !speed_state ) )
    {
        enable_speed = INDEXCOUNTER_SPEED_ENABLE;
    }

    Delay_1ms();
    time_cnt++;
}


```

## Note

> Additional Functions :
>       - void log_display ( float rpm_val ) - The function displays all results
>         and a float value with a comma with two decimal places.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IndexCounter

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
