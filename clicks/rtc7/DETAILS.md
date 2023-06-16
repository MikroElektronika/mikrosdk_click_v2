
---
# RTC 7 click

> RTC 7 Click is a real time clock module which has an extremely low power consumption, allowing it to be used with a single button cell battery or a super capacitor, for an extended period of time. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RTC7 Click driver.

#### Standard key functions :

- `rtc7_cfg_setup` Config Object Initialization function.
```c
void rtc7_cfg_setup ( rtc7_cfg_t *cfg ); 
```

- `rtc7_init` Initialization function.
```c
err_t rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg );
```

- `rtc7_default_cfg` Click Default Configuration function.
```c
err_t rtc7_default_cfg ( rtc7_t *ctx );
```

#### Example key functions :

- `rtc7_check_interrupt` This function returns the interrupt state, state of INTA pin.
```c
uint8_t rtc7_check_interrupt ( rtc7_t *ctx );
```

- `rtc7_read_reg` This function writes one byte data to the register.
```c
err_t rtc7_read_reg ( rtc7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `rtc7_get_local_time` This function gets the local time data including the determined time zone in calculations.
```c
err_t rtc7_get_local_time ( rtc7_t *ctx, rtc7_time_t *local_time );
```

## Examples Description

> This app is used to accurately measure time with low power consumption.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc7_cfg_t cfg;

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
    rtc7_cfg_setup( &cfg );
    RTC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc7_init( &rtc7, &cfg );
    Delay_ms( 300 );
    
    time_set.seconds = 40;
    time_set.minutes = 59;
    time_set.hours = 23;
    time_set.weekdays = 1;
    time_set.monthday = 31;
    time_set.month = 12;
    time_set.year = 22;
    
    err_t error_flag = rtc7_reset( &rtc7 );
    error_flag |= rtc7_init_time ( &rtc7, 0 );
    error_flag |= rtc7_set_gmt_time( &rtc7, &time_set );
    error_flag |= rtc7_set_osc( &rtc7, RTC7_ENABLE_OSC, RTC7_INPUT_FREQ_32768HZ, RTC7_OUTPUT_FREQ_32768HZ );
    error_flag |= rtc7_write_reg( &rtc7, RTC7_TIMER_INIT_REG, 15 );
    error_flag |= rtc7_set_timer( &rtc7, RTC7_TIMER_EN, RTC7_TIMER_FREQ_16HZ );
    Delay_ms( 100 );
    if ( RTC7_ERROR == error_flag )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Waits for a second count-up interrupt and then reads and logs the current time and date on the USB UART.

```c

void application_task ( void )
{
    // Wait for timer count-down interrupt which is set to 1Hz
    while ( rtc7_check_interrupt ( &rtc7 ) );

    // Clear interrupt status
    uint8_t int_status = 0;
    rtc7_read_reg( &rtc7, RTC7_INT_STATUS_REG, &int_status, 1 );
    
    // Read time
    if ( RTC7_OK == rtc7_get_local_time( &rtc7, &time_date ) )
    {
        // Display time
        rtc7_display_results( &rtc7 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC7

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
