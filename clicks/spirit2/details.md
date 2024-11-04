
---
# SPIRIT 2 Click

SPIRIT 2 Click features the SP1ML-915, an ultra-low power, fully integrated RF module, which operates at 915 MHz ISM band. This Click board™ can be used to add wireless connectivity to any application, requiring no extensive RF communication experience. The module integrates all the required components, including the 32-bit STM32L1 MCU, a compact chip antenna, and accompanying circuitry. The SP1ML-915 module supports several types of modulation schemes, including 2-FSK, GFSK, GMSK, OOK, and ASK, allowing it to fulfill different RF transmission requirements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spirit2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spirit-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : UART type


# Software Support

We provide a library for the SPIRIT2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPIRIT2 Click driver.

#### Standard key functions :

- `spirit2_cfg_setup` Config Object Initialization function.
```c
void spirit2_cfg_setup ( spirit2_cfg_t *cfg );
```

- `spirit2_init` Initialization function.
```c
err_t spirit2_init ( spirit2_t *ctx, spirit2_cfg_t *cfg );
```

#### Example key functions :

- `spirit2_power_module` Function for power mode of SPIRIT 2 Click.
```c
void spirit2_power_module ( spirit2_t *ctx, uint8_t power_state );
```

- `spirit2_reset` Function for reseting SPIRIT 2 Click.
```c
void spirit2_reset ( spirit2_t *ctx );
```

- `spirit2_set_mode` Function for setting mode of SPIRIT 2 Click.
```c
void spirit2_set_mode ( spirit2_t *ctx, uint8_t mode );
```

## Example Description

> This example reads and processes data from SPIRIT2 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;
    spirit2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    spirit2_cfg_setup( &cfg );
    SPIRIT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit2_init( &spirit2, &cfg );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit2_power_module( &spirit2, SPIRIT2_MODULE_WAKE_UP );
    spirit2_reset( &spirit2 );
    spirit2_set_mode( &spirit2, SPIRIT2_OPERATING_MODE );
    Delay_ms ( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_COMMAND_MODE );
    spirit2_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_READ_MODULE_VERSION );
    spirit2_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit2_send_cmd_with_parameter( &spirit2, SPIRIT2_CMD_CFG_TXRX_LED, SPIRIT2_PCFG_TXRXLED_OPEN_DRAIN );
    spirit2_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_STORE_CURRENT_CONFIG );
    spirit2_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_OPERATING_MODE );
    spirit2_process( );
    log_info( &logger, "---- The module has been configured ----" );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif 
    Delay_ms ( 1000 );
}

```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void ) {
#ifdef DEMO_APP_RECEIVER
    spirit2_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit2_generic_write( &spirit2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIRIT2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
