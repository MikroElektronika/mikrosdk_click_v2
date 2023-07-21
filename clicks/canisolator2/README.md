\mainpage Main Page

---
# CAN Isolator 2 click

> CAN Isolator 2 Click is a compact add-on board that provides isolated CAN communication. 
> This board features the ISO1042, an isolated CAN transceiver from Texas Instruments. 
> This galvanically-isolated CAN transceiver meets the ISO11898-2 specifications 
> and offers a +/-70V DC bus fault protection, along with the +/-30V of common mode voltage range. 
> The transceiver supports two CAN modes, with speeds of up to 1Mbps in Classic CAN and flexible data rate (FD) CAN, 
> which allows much faster transfer of payload compared to the classic CAN with up to 5Mbps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canisolator2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-isolator-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : UART type


# Software Support

We provide a library for the CanIsolator2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CanIsolator2 Click driver.

#### Standard key functions :

- `canisolator2_cfg_setup` Config Object Initialization function.
```c
void canisolator2_cfg_setup ( canisolator2_cfg_t *cfg );
```

- `canisolator2_init` Initialization function.
```c
CANISOLATOR2_RETVAL canisolator2_init ( canisolator2_t *ctx, canisolator2_cfg_t *cfg );
```

- `canisolator2_default_cfg` Click Default Configuration function.
```c
void canisolator2_default_cfg ( canisolator2_t *ctx );
```

#### Example key functions :

- `canisolator2_generic_write` CAN Isolator 2 data writing function.
```c
err_t canisolator2_generic_write ( canisolator2_t *ctx, char *data_buf, uint16_t len );
```

- `canisolator2_generic_read` CAN Isolator 2 data reading function.
```c
err_t canisolator2_generic_read ( canisolator2_t *ctx, char *data_buf, uint16_t max_len );
```

- `canisolator2_send_data` CAN Isolator 2 send data function.
```c
err_t canisolator2_send_data ( canisolator2_t *ctx, char *tx_data );
```

## Example Description

> This example reads and processes data from CAN Isolator 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    canisolator2_cfg_t canisolator2_cfg;  /**< Click config object. */

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

    canisolator2_cfg_setup( &canisolator2_cfg );
    CANISOLATOR2_MAP_MIKROBUS( canisolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = canisolator2_init( &canisolator2, &canisolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canisolator2_default_cfg ( &canisolator2 );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
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
    
        canisolator2_send_data( &canisolator2, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms( 2000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canisolator2_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canisolator2_clear_app_buf(  );
        }
    
    #endif
}

```

## Additional Function

- `canisolator2_clear_app_buf` CAN Isolator 2 clear app buffer function.
```c
static void canisolator2_clear_app_buf ( void );
```

- `canisolator2_process` CAN Isolator 2 process function.
```c
 static err_t canisolator2_process ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CanIsolator2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
