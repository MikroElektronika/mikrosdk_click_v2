
---
# RS232 Isolator 2 click

RS232 Isolator 2 Click is a compact add-on board that contains a fully isolated transceiver used to provide secure and easy UART to RS232 conversion. This board features the ICL3221, a 3.3V powered RS232 transmitter/receiver that provides ±15kV ESD protection on its RS232 pins from Renesas. This Click board™ is characterized by an assured minimum data rate of 250kbps. It features an automatic power-down function and uses high-speed digital optocouplers to isolate the RS232 interface for 3.75kV isolation. It also possesses an LED indicator that indicates a valid RS232 signal at any of the receiver inputs. This Click board™ is suitable for isolation of RS232 signals, portable equipment, and where the low operational power consumption and even lower standby power consumption are critical.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232isolator2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-isolator-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : UART type


# Software Support

We provide a library for the Rs232Isolator2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rs232Isolator2 Click driver.

#### Standard key functions :

- `rs232isolator2_cfg_setup` Config Object Initialization function.
```c
void rs232isolator2_cfg_setup ( rs232isolator2_cfg_t *cfg );
```

- `rs232isolator2_init` Initialization function.
```c
RS232ISOLATOR2_RETVAL rs232isolator2_init ( rs232isolator2_t *ctx, rs232isolator2_cfg_t *cfg );
```

- `rs232isolator2_default_cfg` Click Default Configuration function.
```c
void rs232isolator2_default_cfg ( rs232isolator2_t *ctx );
```

#### Example key functions :

- `rs232isolator2_generic_write` RS 232 Isolator 2 data writing function.
```c
err_t rs232isolator2_generic_write ( rs232isolator2_t *ctx, char *data_buf, uint16_t len );
```

- `rs232isolator2_generic_read` RS 232 Isolator 2 data reading function.
```c
err_t rs232isolator2_generic_read ( rs232isolator2_t *ctx, char *data_buf, uint16_t max_len );
```

- `rs232isolator2_send_data` RS 232 Isolator 2 data writing function.
```c
err_t rs232isolator2_send_data ( rs232isolator2_t *ctx, char *tx_data );
```

## Example Description

> This library contains API for RS 232 Isolator 2 Click driver.
> This example transmits/receives and processes data from RS 232 Isolator 2 clicks.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data. 

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs232isolator2_cfg_t rs232isolator2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    rs232isolator2_cfg_setup( &rs232isolator2_cfg );
    RS232ISOLATOR2_MAP_MIKROBUS( rs232isolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = rs232isolator2_init( &rs232isolator2, &rs232isolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms( 1000 );

    #endif
        
    #ifdef RECIEVER

        log_printf( &logger, "   Receive data  \r\n" );
        Delay_ms( 2000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

```

### Application Task

> Transmitter/Receiver task depend on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 2 seconds.

```c

void application_task ( void ) {
    
    #ifdef TRANSMITTER
    
    rs232isolator2_send_data( &rs232isolator2, demo_message );
    log_printf( &logger, "%s", demo_message );
    Delay_ms( 2000 );
    log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
    rs232isolator2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        rs232isolator2_clear_app_buf(  );
    }
    
    #endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Isolator2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
