\mainpage Main Page

---
# RTC 4 Click

> RTC 4 Click carries DS2417, a real time clock/calendar with a 1-Wire MicroLAN interface and a programmable interrupt for system output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-4-click)

---


#### Click library

- **Author**        : Aleksandra Cvjeticanin
- **Date**          : Mar 2022.
- **Type**          : One Wire type


# Software Support

We provide a library for the RTC 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 4 Click driver.

#### Standard key functions :

- `rtc4_cfg_setup` Config Object Initialization function.
```c
void rtc4_cfg_setup ( rtc4_cfg_t *cfg );
```

- `rtc4_init` Initialization function.
```c
err_t rtc4_init ( rtc4_t *ctx, rtc4_cfg_t *cfg );
```

#### Example key functions :

- `rtc4_get_interrupt` This function checks the interrupt state of the DS2417 Real time clock/calendar.
```c
uint8_t rtc4_get_interrupt ( rtc4_t *ctx );
```

- `rtc4_set_date_time` This function sets date and time structure along with interrupt interval.
```c
err_t rtc4_set_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time, uint8_t int_interval );
```

- `rtc4_get_date_time` This function gets RTC4 time and date structure. 
```c
err_t rtc4_get_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time );
```

## Example Description

> This example demonstrates the use of the RTC 4 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and then sets the starting time to 23:59:50 and date to 31.12.2022.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc4_cfg_t rtc4_cfg;  /**< Click config object. */

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
    rtc4_cfg_setup( &rtc4_cfg );
    RTC4_MAP_MIKROBUS( rtc4_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == rtc4_init( &rtc4, &rtc4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC4_ERROR == rtc4_check_communication ( &rtc4 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    time.hours = 23;
    time.min = 59; 
    time.sec = 50; 
    
    date.day = 31;
    date.month = 12; 
    date.year = 2022; 
    
    rtc4_set_date_time ( &rtc4, &date, &time, RTC4_DCB_INTERVAL_1S ); 
    
    log_info( &logger, " Application Task " );
}    

```

### Application Task

> With the usage of rtc4_get_date_time we get the time and date from the register and display them on the UART Terminal. The counter increments once per second. 

```c
void application_task ( void ) 
{
    while ( rtc4_get_interrupt ( &rtc4 ) ); 
    
    if ( RTC4_OK == rtc4_get_date_time ( &rtc4, &date, &time ) ) 
    {
        log_printf( &logger, "Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec ); 
        log_printf( &logger, "Date: %.2u/%.2u/%u\r\n", 
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year ); 
        log_printf( &logger, "------------------------\r\n\n"); 
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
