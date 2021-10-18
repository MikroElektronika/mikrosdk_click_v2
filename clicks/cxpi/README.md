\mainpage Main Page

---
# CXPI click

> CXPI Click is a compact add-on board that contains a transceiver that supports the next-generation automotive communication protocol. This board features the BD41000AFJ-C, a transceiver for the CXPI (Clock Extension Peripheral Interface) communication from Rohm Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/cxpi_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cxpi-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : UART type


# Software Support

We provide a library for the CXPI Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CXPI Click driver.

#### Standard key functions :

- `cxpi_cfg_setup` Config Object Initialization function.
```c
void cxpi_cfg_setup ( cxpi_cfg_t *cfg );
```

- `cxpi_init` Initialization function.
```c
err_t cxpi_init ( cxpi_t *ctx, cxpi_cfg_t *cfg );
```

#### Example key functions :

- `cxpi_send_command` Send command.
```c
void cxpi_send_command ( cxpi_t *ctx, char *command );
```

- `cxpi_set_pwm_pin_state` Set PWM pin state function.
```c
void cxpi_set_pwm_pin_state ( cxpi_t *ctx, uint8_t pin_state );
```

- `cxpi_set_through_mode` Set through mode function.
```c
void cxpi_set_through_mode ( cxpi_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the CXPI Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART driver. In addition to this module is placed inside transmitter/receiver working mode cappable of transmission/receive the data.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    cxpi_cfg_t cxpi_cfg;  /**< Click config object. */

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

    // Click initialization.

    cxpi_cfg_setup( &cxpi_cfg );
    CXPI_MAP_MIKROBUS( cxpi_cfg, MIKROBUS_1 );
    err_t init_flag  = cxpi_init( &cxpi, &cxpi_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    cxpi_set_through_mode( &cxpi );

#ifdef DEMO_APP_TRANSMITER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    Delay_ms( 1000 );
#endif

#ifdef DEMO_APP_RECEIVER 
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms( 2000 );
#endif

    log_printf( &logger, "------------------\r\n" );
}

```

### Application Task

> Transmitter/Receiver task depend on uncommented code Receiver logging each received byte to the UART for data logging, while transmitted send messages every 5 seconds.

```c

void application_task ( void ) {
#ifdef DEMO_APP_RECEIVER 
    cxpi_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        cxpi_clear_current_rsp_buf( );
    }
#endif 

#ifdef DEMO_APP_TRANSMITER
    cxpi_send_command( &cxpi, &demo_message[ 0 ] );
    log_printf( &logger, " Sent data : %s",  &demo_message[ 0 ] );
    log_printf( &logger, "------------------\r\n" ); 
    Delay_ms( 5000 );
#endif
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CXPI

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
