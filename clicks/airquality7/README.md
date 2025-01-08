
---
# Air Quality 7 Click

> [Air Quality 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4196) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4196&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Aug 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application measures air quality.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality7

### Example Key Functions

- `airquality7_cfg_setup` Config Object Initialization function. 
```c
void airquality7_cfg_setup ( airquality7_cfg_t *cfg );
``` 
 
- `airquality7_init` Initialization function. 
```c
err_t airquality7_init ( airquality7_t *ctx, airquality7_cfg_t *cfg );
```

- `airquality7_get_status` Get Status function. 
```c
airquality7_err_t airquality7_get_status ( airquality7_t *ctx, uint16_t *tvoc_ppb, uint16_t *co2_ppm, uint32_t *res_val_ohm, uint8_t *err_byte );
```
 
- `airquality7_get_revision` Get Revision function. 
```c
airquality7_err_t airquality7_get_revision ( airquality7_t *ctx, uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *ascii_code );
```

- `airquality7_get_r0_calib` Get R0 Calibration function. 
```c
airquality7_err_t airquality7_get_r0_calib ( airquality7_t *ctx, uint16_t *r0_kohm );
```

### Application Init

> Initializes I2C driver and reads revision date of the module. 
> If CRC check is OK allows the program to go on, otherwise, it displays a message that
> the program needs to be restarted.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality7_cfg_t cfg;
    
    uint8_t airquality7_rev_year       = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_month      = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_day        = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_ascii_code = AIRQUALITY7_DUMMY;

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

    airquality7_cfg_setup( &cfg );
    AIRQUALITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality7_init( &airquality7, &cfg );

    
    airquality7_tvoc_ppb    = AIRQUALITY7_DUMMY;
    airquality7_co2_ppm     = AIRQUALITY7_DUMMY;
    airquality7_res_val_ohm = AIRQUALITY7_DUMMY;

    airquality7_err_code = airquality7_get_revision( &airquality7, 
                                                     &airquality7_rev_year,
                                                     &airquality7_rev_month,
                                                     &airquality7_rev_day,
                                                     &airquality7_rev_ascii_code );
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        log_printf( &logger, " Revision date: %.2u.%.2u.%.2u\r\n", ( uint16_t ) airquality7_rev_day, 
                                                                   ( uint16_t ) airquality7_rev_month,
                                                                   ( uint16_t ) airquality7_rev_year );
        log_printf( &logger, " ASCII code for a charter: %u \r\n", ( uint16_t ) airquality7_rev_ascii_code );
    }
    else
    {
        log_printf( &logger, "CRC ERROR READING REVISION. \r\n" );
        Delay_ms ( 1000 );
        
        for ( ; ; )
        {
            log_printf( &logger, "PLEASE, RESTART YOUR SYSTEM...\r\n" );
            Delay_ms ( 1000 );
            log_printf( &logger, " \r\n \r\n " );
            Delay_ms ( 1000 );
        }
    }
    
    log_printf( &logger, "----------------------------------------- \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads air quality status every 1500ms and shows the results on the USB UART.

```c
void application_task ( void )
{
    airquality7_err_code = airquality7_get_status( &airquality7, 
                                                   &airquality7_tvoc_ppb, 
                                                   &airquality7_co2_ppm,
                                                   &airquality7_res_val_ohm, 
                                                   AIRQUALITY7_NULL );
        
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        uint8_t cnt;

        log_printf( &logger, " tVOC [ppb] = %u \r\n", airquality7_tvoc_ppb );

        log_printf( &logger, " CO2 [ppm] = %u \r\n", airquality7_co2_ppm );

        log_printf( &logger, " Resistor value [ohm] = %lu \r\n", airquality7_res_val_ohm );
        log_printf( &logger, "----------------------------------------- \r\n" );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
