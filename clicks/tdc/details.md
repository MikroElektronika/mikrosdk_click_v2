
---
# TDC click

TDC Click is a compact add-on board that recognizes events and provides a digital representation of the time they occurred. This board features the TDC7200, a time-to-digital converter from Texas Instruments. The Time to Digital Converter (TDC) performs the function of a stopwatch and measures the elapsed time (time-of-flight or TOF) between a START pulse and up to five STOP pulses. The ability to measure from START to multiple STOPs gives users the flexibility to select which STOP pulse yields the best echo performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tdc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tdc-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Tdc Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Tdc Click driver.

#### Standard key functions :

- `tdc_cfg_setup` Config Object Initialization function.
```c
void tdc_cfg_setup ( tdc_cfg_t *cfg );
```

- `tdc_init` Initialization function.
```c
TDC_RETVAL tdc_init ( tdc_t *ctx, tdc_cfg_t *cfg );
```

- `tdc_default_cfg` Click Default Configuration function.
```c
void tdc_default_cfg ( tdc_t *ctx );
```

#### Example key functions :

- `tdc_gen_pulse` TDC pulse generation function.
```c
void tdc_gen_pulse ( tdc_t *ctx, uint32_t u_sec, uint8_t n_stops );
```

- `tdc_setup_measurement` DC setup measurement function.
```c
TDC_RETVAL tdc_setup_measurement ( tdc_t *ctx, uint8_t cal_periods, uint8_t avg_cycles, uint8_t num_stops, uint8_t mode );
```

- `tdc_get_measurement` TDC get measurement function.
```c
err_t tdc_get_measurement ( tdc_t *ctx, uint8_t clock_mode, uint8_t measure_num_stop, uint32_t *time, uint32_t *clock_countn, uint32_t *tof );
```

## Example Description

> This library contains an API for the TDC Click driver.
> This demo application shows the use of a TDC Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app set default settings and 
> the configures the measurement ( set the pulse to 100 us ).

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tdc_cfg_t tdc_cfg;  /**< Click config object. */
    tdc_cfg_t tdc_cfg1;
    static uint8_t cal_periods;
    static uint8_t avg_cycles;
    static uint8_t sel_mode;

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

    tdc_cfg_setup( &tdc_cfg );
    TDC_MAP_MIKROBUS( tdc_cfg, MIKROBUS_1 );
    tdc_cfg_setup( &tdc_cfg1 );
    TDC_MAP_MIKROBUS( tdc_cfg1, MIKROBUS_2 );
    err_t init_flag  = tdc_init( &tdc, &tdc_cfg );
    init_flag  |= tdc_init( &tdc_pulse,  &tdc_cfg1 );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    tdc_default_cfg ( &tdc );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    cal_periods = 10;
    avg_cycles = 1;
    num_stops = 3;
    sel_mode = 1;
    pulse_us = 100;
    count_stop = 1;
    tdc_setup_measurement( &tdc, cal_periods, avg_cycles, num_stops, sel_mode );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a TDC Click board™.
> In this example, after the START signal, the app sends 3 STOP signals per 100 microseconds.
> The application reads and displays the value of Time, Clock count and 
> Time-of-Flight values of three performed measurements.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static uint32_t p_time[ 5 ];
    static uint32_t p_clock_count[ 5 ];
    static uint32_t p_tof[ 5 ];
    
    tdc_start_measurement( &tdc );

    while ( tdc_get_trg( &tdc ) == 0 );
   
    tdc_gen_pulse( &tdc_pulse, pulse_us, num_stops );
   
    while ( tdc_get_interrupt( &tdc ) == 1 );
   
    tdc_get_measurement( &tdc, TDC_MCU_CLOCK_MODE_168_MHZ, count_stop, p_time, p_clock_count, p_tof );
    
    log_printf( &logger, " Time[ 0 ]        = %lu\r\n", p_time[ 0 ] ); 
    log_printf( &logger, " Time[ 1 ]        = %lu\r\n", p_time[ 1 ] ); 
    log_printf( &logger, " Time[ 2 ]        = %lu\r\n", p_time[ 2 ] );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    log_printf( &logger, " Clock count[ 0 ] = %lu\r\n", p_clock_count[ 0 ] );
    log_printf( &logger, " Clock count[ 1 ] = %lu\r\n", p_clock_count[ 1 ] );
    log_printf( &logger, " Clock count[ 2 ] = %lu\r\n", p_clock_count[ 2 ] );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );

    log_printf( &logger, " TOF[ 0 ]         = %u us\r\n", p_tof[ 0 ] ); 
    log_printf( &logger, " TOF[ 1 ]         = %u us\r\n", p_tof[ 1 ] );  
    log_printf( &logger, " TOF[ 2 ]         = %u us\r\n", p_tof[ 2 ] );    
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Tdc

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
