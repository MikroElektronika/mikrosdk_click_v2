\mainpage Main Page
  
---
# RTC click

> RTC Click is an accessory board in mikroBus™ form factor. It features the PCF8583 serial real-time clock (RTC). 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc Click driver.

#### Standard key functions :

- `rtc_c_cfg_setup` Config Object Initialization function.
```c
void rtc_c_cfg_setup ( rtc_c_cfg_t *cfg ); 
```

- `rtc_c_init` Initialization function.
```c
err_t rtc_c_init ( rtc_c_t *ctx, rtc_c_cfg_t *cfg );
```

#### Example key functions :

- `rtc_c_set_time` Function sets time: hours, minutes and seconds data to the target register address of PCF8583 chip on RTC Click.
```c
void rtc_c_set_time ( rtc_c_t *ctx );
```

- `rtc_c_get_time` Function gets time: hours, minutes and seconds data from the target register address of PCF8583 chip on RTC Click.
```c
void rtc_c_get_time ( rtc_c_t *ctx );
```

- `rtc_c_enable_disable_counting` Function that enables or disables counting on RTC Click.
```c
void rtc_c_enable_disable_counting ( rtc_c_t *ctx, uint8_t en_dis );
```

## Example Description

> This application enables setup and measurement of time with RTC click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set start time, enable counting and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc_c_cfg_t cfg;

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

    // Click initialization.
    rtc_c_cfg_setup( &cfg );
    RTC_C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc_c_init( &rtc_c, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "     RTC Click    \r\n" );
    log_printf( &logger, "------------------\r\n" );

    // Set Time: 23h, 59 min, 50 sec and 10 ms
    rtc_c.time.time_hours = 23;
    rtc_c.time.time_minutes = 59;
    rtc_c.time.time_seconds = 50;
    rtc_c.time.time_hun_sec = 10;

    rtc_c_set_time( &rtc_c );
    Delay_100ms( );
    
    // Start counting
    rtc_c_enable_disable_counting( &rtc_c, 1 );
    Delay_100ms( );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> This is an example which demonstrates the use of RTC Click board.
> RTC Click communicates with register via I2C by write to register and read from register.
> This example show time when the value of time_seconds is changed.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 1 sec.

```c

void application_task ( void )
{
    static uint8_t time_seconds_new = 0xFF;

    rtc_c_get_time( &rtc_c );

    if ( time_seconds_new != rtc_c.time.time_seconds )
    {
        log_printf( &logger, " Time : %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) rtc_c.time.time_hours, 
                    ( uint16_t ) rtc_c.time.time_minutes, 
                    ( uint16_t ) rtc_c.time.time_seconds );

        log_printf( &logger, "------------------\r\n" );

        time_seconds_new = rtc_c.time.time_seconds;
    }

    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc

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
