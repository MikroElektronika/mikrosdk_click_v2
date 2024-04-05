\mainpage Main Page

---
# RTC 11 click

RTC 11 Click is a compact add-on board that contains a real-time clock IC designed to maximize battery life and reduce overall battery requirements in wearable applications. This board features the AB0815, an ultra-low-power coupled with a highly sophisticated feature set the real-time clock from Abracon LLC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-11-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RTC11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC11 Click driver.

#### Standard key functions :

- `rtc11_cfg_setup` Config Object Initialization function.
```c
void rtc11_cfg_setup ( rtc11_cfg_t *cfg );
```

- `rtc11_init` Initialization function.
```c
err_t rtc11_init ( rtc11_t *ctx, rtc11_cfg_t *cfg );
```

#### Example key functions :

- `rtc11_set_time` Set time hours, minutes and seconds function
```c
err_t rtc11_set_time ( rtc11_t *ctx, rtc11_time_t rtc_time );
```

- `rtc11_get_time` Get time hours, minutes and seconds function
```c
void rtc11_get_time ( rtc11_t *ctx, rtc11_time_t *rtc_time );
```

- `rtc11_set_date` Set date day of the week, day, month and year function
```c
err_t rtc11_set_date ( rtc11_t *ctx, rtc11_date_t rtc_date );
```

## Example Description

> This is an example that demonstrates the use of the RTC 11 click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes SPI, performs software reset, sets system time and date, and starts clocking system.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc11_cfg_t rtc11_cfg;  /**< Click config object. */

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

    rtc11_cfg_setup( &rtc11_cfg );
    RTC11_MAP_MIKROBUS( rtc11_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc11_init( &rtc11, &rtc11_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Software reset \r\n" );
    rtc11_soft_rst( &rtc11 );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 55;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
    rtc11_set_time ( &rtc11, time );
    Delay_ms ( 100 );
    
    date.day_of_week = 0;
    date.day = 19;
    date.month = 7;
    date.year = 21;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting date: %.2d/%.2d/%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    rtc11_set_date( &rtc11, date );
    Delay_ms ( 100 );
    
    rtc11_stp_sys_slk ( &rtc11, RTC11_PROP_DIS );
    log_info( &logger, " Application Task " );
    log_printf( &logger,"------------------------\r\n" );
}

```

### Application Task

> Demonstrates use of RTC 11 click board by reading and displaying time and date via USART terminal.

```c

void application_task ( void ) {
    rtc11_get_time ( &rtc11, &time );
    Delay_ms ( 10 );
    rtc11_get_date ( &rtc11, &date );
    Delay_ms ( 10 );
    
    if ( sec_flag != time.sec ) {
        log_printf( &logger, " Date: " );
        disp_day_of_the_week( date.day_of_week );
        log_printf( &logger, " %.2d/%.2d/20%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, " Time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger,"--------------------------\r\n" );
    }
    sec_flag = time.sec;
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
