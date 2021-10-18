
---
# UART MUX 2 click

UART MUX 2 Click is a compact add-on board that enables pseudo-multidrop RS232 transmission. This board features the MAX399, a precise CMOS analog multiplexer that allows four remote RS-232 transceivers to share a single UART from Maxim Integrated. It offers fast switching speeds with a transition time of less than 250ns and low on-resistance less than 100Ω while retains CMOS-logic input compatibility and fast switching. Channel selection is performed through a set of specific GPIO pins and possesses additional functionality such as the manual ON/OFF feature. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uartmux2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uart-mux-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : UART type


# Software Support

We provide a library for the UartMux2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UartMux2 Click driver.

#### Standard key functions :

- `uartmux2_cfg_setup` Config Object Initialization function.
```c
void uartmux2_cfg_setup ( uartmux2_cfg_t *cfg );
```

- `uartmux2_init` Initialization function.
```c
UARTMUX2_RETVAL uartmux2_init ( uartmux2_t *ctx, uartmux2_cfg_t *cfg );
```

- `uartmux2_default_cfg` Click Default Configuration function.
```c
void uartmux2_default_cfg ( uartmux2_t *ctx );
```

#### Example key functions :

- `uartmux2_set_operation_mode` UART MUX 2 set operation mode function.
```c
err_t uartmux2_set_operation_mode ( uartmux2_t *ctx, uint8_t op_mode );
```

- `uartmux2_set_channel` UART MUX 2 set channel function.
```c
err_t uartmux2_set_channel ( uartmux2_t *ctx, uint8_t mux_ch );
```

- `uartmux2_send_data` UART MUX 2 data writing function.
```c
err_t uartmux2_send_data ( uartmux2_t *ctx, char *tx_data );
```

## Example Description

> This library contains API for UART MUX 2 Click driver.
> This example transmits/receives and processes data from UART MUX 2 clicks.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data. 

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and set UART channel module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    uartmux2_cfg_t uartmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n Application Init \r\n" );

    // Click initialization.

    uartmux2_cfg_setup( &uartmux2_cfg );
    UARTMUX2_MAP_MIKROBUS( uartmux2_cfg, MIKROBUS_1 );
    err_t init_flag  = uartmux2_init( &uartmux2, &uartmux2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uartmux2_default_cfg ( &uartmux2 );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, "\r\n Application Task \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 500 );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms( 1000 );

    #endif

    #ifdef RECIEVER

        uart_ch = UARTMUX2_CHANNEL_0;
        log_printf( &logger, "   Receive data  \r\n" );
        log_printf( &logger, "      UART%u \r\n", ( uint16_t ) uart_ch );
        uartmux2_set_channel( &uartmux2, uart_ch );
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
    
    for ( uart_ch = UARTMUX2_CHANNEL_0; uart_ch <= UARTMUX2_CHANNEL_3; uart_ch++ ) {
        uartmux2_set_channel( &uartmux2, uart_ch );
        Delay_ms( 100 );
        uartmux2_send_data( &uartmux2, demo_message );
        log_printf( &logger, "  UART%u : ", ( uint16_t ) uart_ch ); 
    
        for ( uint8_t cnt = 0; cnt < 9; cnt ++ ) {
            log_printf( &logger, "%c", demo_message[ cnt ] );
            Delay_ms( 100 );
        }
        
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
    
    #endif
    
    #ifdef RECIEVER
    
    uartmux2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        uartmux2_clear_app_buf(  );
    }
    
    #endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UartMux2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
