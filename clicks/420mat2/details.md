
---
# 4-20mA T 2 click

> 4-20mA T 2 Click is a compact add-on board for transmitting an analog output current over an industry-standard 4-20mA current loop. This board features DAC161S997, a low-power 16-bit ΣΔ digital-to-analog converter (DAC) from Texas Instruments. It has a programmable Power-Up condition and loop-error detection/reporting accessible via simple 4-wire SPI for data transfer and configuration of the DAC functions. In addition, it is characterized by low power consumption and the possibility of simple Highway Addressable Remote Transducer (HART) modulator interfacing, allowing the injection of FSK-modulated digital data into the 4-20mA current loop.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/420mat2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4-20ma-t-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the 4-20mA T 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 4-20mA T 2 Click driver.

#### Standard key functions :

- `c420mat2_cfg_setup` Config Object Initialization function.
```c
void c420mat2_cfg_setup ( c420mat2_cfg_t *cfg );
```

- `c420mat2_init` Initialization function.
```c
err_t c420mat2_init ( c420mat2_t *ctx, c420mat2_cfg_t *cfg );
```

- `c420mat2_default_cfg` Click Default Configuration function.
```c
err_t c420mat2_default_cfg ( c420mat2_t *ctx );
```

#### Example key functions :

- `c420mat2_set_output_current` 4-20mA T 2 set output current function.
```c
err_t c420mat2_set_output_current ( c420mat2_t *ctx, float current_ma );
```

- `c420mat2_get_status` 4-20mA T 2 set status function.
```c
err_t c420mat2_get_status ( c420mat2_t *ctx, c420mat2_status_t *status );
```

- `c420mat2_set_lower_limit` 4-20mA T 2 set lower limit function.
```c
err_t  c420mat2_set_lower_limit ( c420mat2_t *ctx, float lower_limit_ma );
```

## Example Description

> This example demonstrates the use of 4-20mA T 2 Click board™.
> This driver provides functions to configure 
> analog output current transfer over an industry standard 4-20mA current loop.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c420mat2_cfg_t c420mat2_cfg;  /**< Click config object. */

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
    c420mat2_cfg_setup( &c420mat2_cfg );
    C420MAT2_MAP_MIKROBUS( c420mat2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c420mat2_init( &c420mat2, &c420mat2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( C420MAT2_ERROR == c420mat2_default_cfg ( &c420mat2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------------\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> This example demonstrates the use of the 4-20mA T 2 Click board™.
> This example periodically changes the analog output current transfer 
> from 4mA to 20mA and display status every 5 seconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 4.0 ) )
    {
        log_printf( &logger, " Loop Current:  4.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 10.0 ) )
    {
        log_printf( &logger, " Loop Current: 10.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 15.0 ) )
    {
        log_printf( &logger, " Loop Current: 15.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 20.0 ) )
    {
        log_printf( &logger, " Loop Current: 20.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.c420mAT2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
