\mainpage Main Page
  
---
# RTC 3 Click

> RTC3 Click carries BQ32000, a real time clock with an integrated trickle charge circuit for automatic switchover to a backup power supply (the circuit maintains the backup charge with an onboard super capacitor).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc3 Click driver.

#### Standard key functions :

- `rtc3_cfg_setup` Config Object Initialization function.
```c
void rtc3_cfg_setup ( rtc3_cfg_t *cfg ); 
```

- `rtc3_init` Initialization function.
```c
err_t rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg );
```

#### Example key functions :

- `rtc3_set_time` Set time hours, minutes, seconds function
```c
void rtc3_set_time ( rtc3_t *ctx );
```

- `rtc3_get_time` Get time hours, minutes, seconds function
```c
void rtc3_get_time ( rtc3_t *ctx );
```

- `rtc3_get_date` Get day of the week, day, month and year function
```c
void rtc3_get_date ( rtc3_t *ctx );
```

## Examples Description

> This example demonstrates the use of RTC 3 Click board by reading and displaying the time and date values.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger and then sets the starting time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc3_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.
    rtc3_cfg_setup( &cfg );
    RTC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc3_init( &rtc3, &cfg );
    Delay_ms ( 100 );
    
    // Stop counting
    rtc3_set_counting( &rtc3, 0 );

    // Set Time: 23h, 59 min, 50 sec
    rtc3.time.time_hours = 23;
    rtc3.time.time_minutes = 59;
    rtc3.time.time_seconds = 50;

    rtc3_set_time( &rtc3 );

    // Set Date: 6 ( Day of the week ), 31 ( day ), 12 ( month ) and 2022 ( year )
    rtc3.date.day_of_the_week = 6;
    rtc3.date.date_day = 31;
    rtc3.date.date_month = 12;
    rtc3.date.date_year = 22;

    rtc3_set_date( &rtc3 );

    // Start counting
    rtc3_set_counting( &rtc3, 1 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads and displays on the USB UART the current time and date values once per second.

```c

void application_task ( void )
{
    static uint8_t time_seconds = 0xFF;

    rtc3_get_time( &rtc3 );

    rtc3_get_date( &rtc3 );

    if ( time_seconds != rtc3.time.time_seconds )
    {
        display_log_day_of_the_week ( rtc3.date.day_of_the_week );
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n Date: %.2u.%.2u.20%.2u.\r\n------------------\r\n", 
                    ( uint16_t ) rtc3.time.time_hours, ( uint16_t ) rtc3.time.time_minutes,
                    ( uint16_t ) rtc3.time.time_seconds, ( uint16_t ) rtc3.date.date_day, 
                    ( uint16_t ) rtc3.date.date_month, ( uint16_t ) rtc3.date.date_year );

        time_seconds = rtc3.time.time_seconds;
    }

    Delay_ms ( 200 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc3

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
