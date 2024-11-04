
---
# RTC 17 Click

> RTC 17 Click is a compact add-on board that accurately keeps the time of a day. This board features the RV5C387A, a CMOS real-time clock with a built-in interrupt generation function from Nisshinbo Micro Devices Inc, to perform serial transmission of time and calendar data to the MCU. The BU9873 provides information like year, month, day, weekday, hours, minutes, and seconds based on a 32.768kHz quartz crystal through an I2C serial interface to transmit time and calendar data to the MCU. It also has an alarm function that outputs an interrupt signal to the MCU when the day of the week, hour, or minute matches with the preset time.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 17 Click driver.

#### Standard key functions :

- `rtc17_cfg_setup` Config Object Initialization function.
```c
void rtc17_cfg_setup ( rtc17_cfg_t *cfg );
```

- `rtc17_init` Initialization function.
```c
err_t rtc17_init ( rtc17_t *ctx, rtc17_cfg_t *cfg );
```

- `rtc17_default_cfg` Click Default Configuration function.
```c
err_t rtc17_default_cfg ( rtc17_t *ctx );
```

#### Example key functions :

- `rtc17_set_time` This function sets the starting time values - second, minute and hour.
```c
err_t rtc17_set_time ( rtc17_t *ctx, rtc17_time_t *time );
```

- `rtc17_read_time` This function reads the current time values - second, minute and hour.
```c
err_t rtc17_read_time ( rtc17_t *ctx, rtc17_time_t *time );
```

- `rtc17_read_date` This function reads the current date values - day of week, day, month and year.
```c
err_t rtc17_read_date ( rtc17_t *ctx, rtc17_date_t *date );
```

## Example Description

> This example demonstrates the use of RTC 17 Click board by reading and displaying the time and date values.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the Click default configuration which sets 24h time mode and interrupt to be synchronized with second count-up.
And after that setting the starting time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc17_cfg_t rtc17_cfg;  /**< Click config object. */

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
    rtc17_cfg_setup( &rtc17_cfg );
    RTC17_MAP_MIKROBUS( rtc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc17_init( &rtc17, &rtc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC17_ERROR == rtc17_default_cfg ( &rtc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC17_OK == rtc17_set_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC17_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC17_OK == rtc17_set_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the second count-up interrupt and then reads and displays the current time and date values on the USB UART.

```c
void application_task ( void )
{
    // Wait for interrupt which is synchronized with second count-up
    while ( rtc17_get_int_pin ( &rtc17 ) );
    
    rtc17_clear_interrupts ( &rtc17 );
    if ( RTC17_OK == rtc17_read_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC17_OK == rtc17_read_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
