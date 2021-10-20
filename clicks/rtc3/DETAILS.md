 
---
# RTC 3 click

RTC3 click carries BQ32000, a real time clock with an integrated trickle charge circuit for automatic switchover to a backup power supply (the circuit maintains the backup charge with an onboard super capacitor).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-3-click)

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

- Config Object Initialization function.
> void rtc3_cfg_setup ( rtc3_cfg_t *cfg ); 
 
- Initialization function.
> RTC3_RETVAL rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg );

- Click Default Configuration function.
> void rtc3_default_cfg ( rtc3_t *ctx );


#### Example key functions :

- Function sets time: hours, minutes and seconds data to
- the target register address of PCF8583 chip on RTC 3 Click.
> void rtc3_set_time ( rtc3_t *ctx );
 
- Function gets time: hours, minutes and seconds data from
-  the target register address of PCF8583 chip on RTC 3 Click.
> void rtc3_get_time ( rtc3_t *ctx );

- Function set calibration by write CAL_CFG1 register of BQ32000 chip.
> void rtc3_set_calibration ( rtc3_t *ctx, uint8_t cal_sign, uint8_t cal_mumber );

## Examples Description

> This application enables time measurment over RTC3 click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C,
> set start time and date, enable counting and start write log.

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc3_cfg_setup( &cfg );
    RTC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc3_init( &rtc3, &cfg );

    /// Set Time: 23h, 59 min, 50 sec

    rtc3.time.time_hours = 23;
    rtc3.time.time_minutes = 59;
    rtc3.time.time_seconds = 50;

    rtc3_set_time( &rtc3 );

    // Set Date: 1 ( Day of the week ), 31 ( day ), 12 ( month ) and 2018 ( year )

    rtc3.date.day_of_the_week = 1;
    rtc3.date.date_day = 31;
    rtc3.date.date_month = 12;
    rtc3.date.date_year = 2018;

    rtc3_set_date( &rtc3 );

    // Start counting
   
    rtc3_enable_disable_counting( &rtc3, 1 );
    Delay_100ms( );
    
    Delay_ms( 1000 );
}
  
```

### Application Task

> This is a example which demonstrates the use of RTC 3 Click board.
> RTC 3 Click communicates with register via I2C by write to register and read from register,
> set time and date, get time and date, enable and disable counting
>  and set frequency by write configuration register.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 1 sec.

```c

void application_task ( void )
{
    //  Task implementation.

    uint8_t time_seconds_new = 0xFF;
    
     

    rtc3_get_time( &rtc3 );

    rtc3_get_date( &rtc3 );

    if ( time_seconds_new != rtc3.time.time_seconds )
    {
        if ( ( ( rtc3.time.time_hours | rtc3.time.time_minutes | rtc3.time.time_seconds ) == 0 )  && ( ( rtc3.date.date_day | rtc3.date.date_month ) == 1 ) )
        {
            log_printf( &logger, "  Happy New Year  \r\n" );
            log_printf( &logger, "------------------\r\n" );
        }

        log_printf( &logger, " Time : %d:%d:%d \r\n Date: %d.%d.20%d.\r\n------------------\r\n", rtc3.time.time_hours, rtc3.time.time_minutes,
                                                                                            rtc3.time.time_seconds, 
                                                                                            rtc3.date.date_day, rtc3.date.date_month, rtc3.date.date_year );

        time_seconds_new = rtc3.time.time_seconds;
    }

    Delay_ms( 200 );
} 

```

## Note

> Time stats measuring correctly but from 0 seconds, after 10 seconds.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc3

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
