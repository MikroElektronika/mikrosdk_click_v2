
---
# TDC 2 Click

> TDC 2 Click is a compact add-on board that recognizes events and provides a digital representation of the time they occurred. This board features ScioSense’s AS6500, a four-channel time-to-digital converter (TDC) frontend with high measurement performance and high data throughput. The AS6500 is characterized by simple data post-processing thanks to calibrated results (calculates calibrated stop measurements referenced to the applied reference clock).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tdc2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/tdc-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the TDC 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TDC 2 Click driver.

#### Standard key functions :

- `tdc2_cfg_setup` Config Object Initialization function.
```c
void tdc2_cfg_setup ( tdc2_cfg_t *cfg );
```

- `tdc2_init` Initialization function.
```c
err_t tdc2_init ( tdc2_t *ctx, tdc2_cfg_t *cfg );
```

- `tdc2_default_cfg` Click Default Configuration function.
```c
err_t tdc2_default_cfg ( tdc2_t *ctx );
```

#### Example key functions :

- `tdc2_read_results` TDC 2 results data reading function.
```c
err_t tdc2_read_results( tdc2_t *ctx, uint8_t reg, uint32_t *reference_index, uint32_t *stop_result );
```

- `tdc2_start_measuring` TDC 2 start measuring function.
```c
err_t tdc2_start_measuring ( tdc2_t *ctx );
```

- `tdc2_set_resolution` TDC 2 set resolution function.
```c
err_t tdc2_set_resolution ( tdc2_t *ctx, uint32_t resolution );
```

## Example Description

> This library contains API for TDC 2 Click driver.
> The library initializes and defines the SPI bus drivers to write and read data from registers, as well as the default configuration for a reading time between two STOP signals.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver after that resets the device and performs default configuration and sets the device in read mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tdc2_cfg_t tdc2_cfg;  /**< Click config object. */

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
    tdc2_cfg_setup( &tdc2_cfg );
    TDC2_MAP_MIKROBUS( tdc2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == tdc2_init( &tdc2, &tdc2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TDC2_ERROR == tdc2_default_cfg ( &tdc2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    tdc2_start_measuring ( &tdc2 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the TDC 2 Click board by 
measuring the time between two STOP signals. This example is set up to
generate stop signals until FIFO fil's up which is indicated by interrupt pin going to low state.
After that FIFO buffer is completely emptied by reading, and that data is used to calculate 
the time between STOP signals.

```c
void application_task ( void )
{
    uint32_t reference_index [ 18 ] = { 0 };
    uint32_t stop_result [ 18 ] = { 0 };
    uint8_t cnt = 0;
    
    tdc2_reset_index( &tdc2 );
    Delay_ms ( 10 );
    
    while ( tdc2_get_int_state( &tdc2 ) == 1 )
    {
        dev_generate_stop( &tdc2 );
        Delay_ms ( 100 );
    }
    
    while ( tdc2_get_int_state( &tdc2 ) == 0 )
    {
        tdc2_read_results( &tdc2, TDC2_REG_INDEX_CH1_BYTE3, &reference_index[ cnt ], &stop_result[ cnt ] );
        
        log_printf( &logger, "CH1: Reference Index[%d]: %lu, Stop Result[%d]: %lu \r\n", ( uint16_t ) cnt, 
                    reference_index[ cnt ], ( uint16_t ) cnt, stop_result[ cnt ] ); 
        Delay_ms ( 10 ); 
        
        if ( cnt )
        {
            uint32_t time = 0;
            tdc2_get_time_between_stops ( &tdc2, stop_result[ cnt - 1 ], reference_index[ cnt - 1 ],
                                          stop_result[ cnt ], reference_index[ cnt ], &time );
            log_printf( &logger, "Time between STOP %d and STOP %d is %lu ms \r\n", 
                        ( uint16_t ) ( cnt - 1 ), ( uint16_t ) cnt, time / TDC2_uS_TO_mS ); 
            Delay_ms ( 10 );
        }
        cnt++;
    }
    log_printf( &logger, "---------------------------------------------- \r\n" ); 
}
```

## Note

> In order to test this example, you will need to connect STOP1 with the DIS pin. Disable pin is 
disabled by software and it isn't going to affect the working state of the TDC 2 Click Bord.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TDC2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
