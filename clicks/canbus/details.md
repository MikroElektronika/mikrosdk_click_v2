
---
# CAN Bus click

CAN Bus Click is a compact add-on board that provides a link between the CAN protocol controller and the physical wires of the bus lines in a control area network (CAN). This board features the MAX13054, an industry-standard, high-speed CAN transceiver with extended ±80V fault protection from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/can_bus_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-bus-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : UART type


# Software Support

We provide a library for the CanBus Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CanBus Click driver.

#### Standard key functions :

- `canbus_cfg_setup` Config Object Initialization function.
```c
void canbus_cfg_setup ( canbus_cfg_t *cfg );
```

- `canbus_init` Initialization function.
```c
CANBUS_RETVAL canbus_init ( canbus_t *ctx, canbus_cfg_t *cfg );
```

- `canbus_default_cfg` Click Default Configuration function.
```c
void canbus_default_cfg ( canbus_t *ctx );
```

#### Example key functions :

- `canbus_send_data` CAN Bus send data function.
```c
err_t canbus_send_data ( canbus_t *ctx, char *tx_data );
```

- `canbus_set_high_speed_mode` CAN Bus high speed mode function.
```c
err_t canbus_set_high_speed_mode ( canbus_t *ctx );
```

- `canbus_set_low_current_standby_mode` CAN Bus low current standby mode function.
```c
err_t canbus_set_low_current_standby_mode ( canbus_t *ctx );
```

## Example Description

> This library contains API for CAN Bus click board™.
> This example transmits/receives and processes data from CAN Bus click.
> The library initializes and defines the 
> UART bus drivers to transmit or receive data. 

**The demo application is composed of two sections :**

### Application Init

> Initializes driver, wake-up module, and set high-speed operation mode.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    canbus_cfg_t canbus_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    canbus_cfg_setup( &canbus_cfg );
    CANBUS_MAP_MIKROBUS( canbus_cfg, MIKROBUS_1 );
    err_t init_flag  = canbus_init( &canbus, &canbus_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canbus_default_cfg ( &canbus );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    canbus_set_high_speed_mode( &canbus );
    Delay_ms( 100 );
    
    #ifdef TRANSMIT
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      MikroE      \r\n" );
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

> Transmitter/Receiver task depends on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 2 seconds.

```c

void application_task ( void ) {
   #ifdef TRANSMIT
    
        canbus_send_data( &canbus, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms( 2000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canbus_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canbus_clear_app_buf(  );
        }
    
    #endif
}

```

## Additional Function

- `canbus_clear_app_buf` Function clears memory of app_buf.
```c
static void canbus_clear_app_buf ( void );
```

- `canbus_process` The general process of collecting presponce that a module sends.
```c
static err_t canbus_process ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CanBus

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
