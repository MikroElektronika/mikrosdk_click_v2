
---
# IrDA 2 click

IrDA2 click features the TFDU4101 infrared transceiver module as well as MCP2120 infrared encoder/decoder from Microchip connected with the 7.3728 MHz external crystal. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target board via UART interface and the following mikroBUS™ pins: AN, RST, CS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irda2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/irda2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the IrDA2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IrDA2 Click driver.

#### Standard key functions :

- `irda2_cfg_setup` Config Object Initialization function.
```c
void irda2_cfg_setup ( irda2_cfg_t *cfg );
```

- `irda2_init` Initialization function.
```c
err_t irda2_init ( irda2_t *ctx, irda2_cfg_t *cfg );
```

- `irda2_default_cfg` Click Default Configuration function.
```c
void irda2_default_cfg ( irda2_t *ctx );
```

#### Example key functions :

- `irda2_mode_setup` This function allows IrDA 2 click mode to be set.
```c
void irda2_mode_setup( irda2_t *ctx, irda2_mode_t state );
```

- `irda2_pwr_setup` This function allows IrDA 2 click power mode to be set.
```c
void irda2_pwr_setup( irda2_t *ctx, irda2_pwr_t state );
```

- `irda2_reset` This function executes a device reset operation.
```c
void irda2_reset( irda2_t *ctx );
```

## Example Description

> This example demonstrates the use of IrDA 2 click boards. The example can perform both roles, transmitter and receiver.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART driver and all used control pins. Also clears the response buffer.

```c

void application_init( void ) {
    irda2_cfg_t irda2_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_printf( &logger, "***  IrDA initialization done  ***\r\n" );
    log_printf( &logger, "**********************************\r\n" );
    
    //  Click initialization.
    
    irda2_cfg_setup( &irda2_cfg );
    IRDA2_MAP_MIKROBUS( irda2_cfg, MIKROBUS_1 );
    irda2_init( &irda2, &irda2_cfg );
    irda2_default_cfg( &irda2 );
    irda2_reset( &irda2 );

    //  Clear response.
    
    memset( rx_message, 0, sizeof( rx_message ) );
}

```

### Application Task

> Demonstrates the use of IrDA clicks which can be used as transmitter or receiver. There are four different examples in this project. 
Uncomment one of the below macros to select which example will be executed. By default the DEMO_APP_TRANSMITTER_1 example is selected.

```c

void application_task( void ) {

#ifdef DEMO_APP_RECEIVER_1
    rx_message[ 0 ] = irda2_generic_single_receive( &irda2 );

    if ( rx_message[ 0 ] != 0 ) {
        log_printf( &logger, "%c", ( char ) rx_message[ 0 ] );
    }
    Delay_ms( 100 );

#endif

#ifdef DEMO_APP_RECEIVER_2

    irda2_generic_multiple_receive( &irda2, rx_message, '\n' );

    log_printf( &logger, "RECEIVED MESSAGE : " );
    log_printf( &logger, "%s\r\n", rx_message );
    Delay_ms( 100 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_1

    irda2_generic_multiple_send( &irda2, tx_message );

    log_printf( &logger, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_2

    idx = 0;

    while ( tx_message[ idx ] != '\0' ) {
        irda2_generic_single_send( &irda2, tx_message[ idx++ ] );
    }

    log_printf( &logger, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif

}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
