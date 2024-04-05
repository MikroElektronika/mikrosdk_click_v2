\mainpage Main Page

---
# RS485 5V click

RS485 click 5V is an RS422/485 transceiver Click board™, which can be used as an interface between the TTL level UART and the RS422/485 communication bus. It features a half-duplex communication capability, bus Idle, open, and short-circuit detection, thermal shutdown, and more. It is well suited for transmitting data packets over long distances and noisy areas, using the twisted wire bus, which offers good electromagnetic interferences (EMI) immunity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4855v_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-5v-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the RS4855V Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS4855V Click driver.

#### Standard key functions :

- `rs4855v_cfg_setup` Config Object Initialization function.
```c
void rs4855v_cfg_setup ( rs4855v_cfg_t *cfg );
```

- `rs4855v_init` Initialization function.
```c
err_t rs4855v_init ( rs4855v_t *ctx, rs4855v_cfg_t *cfg );
```

#### Example key functions :

- `rs4855v_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rs4855v_generic_read ( rs4855v_t *ctx, char *data_buf, uint16_t max_len );
```

- `rs4855v_send_command` This function sends a command by using UART serial interface.
```c
void rs4855v_send_command ( rs4855v_t *ctx, char *command );
```

## Example Description

> This example reads and processes data from RS485 5V clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;
    rs4855v_cfg_t cfg;

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

    //  Click initialization.

    rs4855v_cfg_setup( &cfg );
    RS4855V_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855v_init( &rs4855v, &cfg );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Transmit data   \r\n" );
    Delay_ms ( 1000 );

#endif
    
#ifdef DEMO_APP_RECEIVER 
    log_printf( &logger, "------------------\r\n" );

    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
        
    log_printf( &logger, "------------------\r\n" );
}

```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void ) {  
#ifdef DEMO_APP_RECEIVER 
    
    rs4855v_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        rs4855v_clear_current_rsp_buf( );
    }
    
#endif 

#ifdef DEMO_APP_TRANSMITTER
      
    rs4855v_send_command( &rs4855v, &demo_message[ 0 ] );
    log_printf( &logger, "\t%s",  &demo_message[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------\r\n" ); 
    
#endif   
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4855V

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
