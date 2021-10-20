\mainpage Main Page

---
# SPIRIT click

SPIRIT click carries the SP1ML 868MHz ultra low-power RF module. The board is designed to use 3.3V power supply and 3.3V or 5V I/O voltage levels. It communicates with the target MCU over UART interface, with additional functionality provided by the following pins on the mikroBUS™ line: PWM, RST, CS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spirit_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spirit-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the SPIRIT Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPIRIT Click driver.

#### Standard key functions :

- `spirit_cfg_setup` Config Object Initialization function.
```c
void spirit_cfg_setup ( spirit_cfg_t *cfg );
```

- `spirit_init` Initialization function.
```c
err_t spirit_init ( spirit_t *ctx, spirit_cfg_t *cfg );
```

#### Example key functions :

- `spirit_power_module` Function for power mode of SPIRIT click.
```c
void spirit_power_module ( spirit_t *ctx, uint8_t power_state );
```

- `spirit_reset` Function for reseting SPIRIT click.
```c
void spirit_reset ( spirit_t *ctx );
```

- `spirit_set_mode` Function for setting mode of SPIRIT click.
```c
void spirit_set_mode ( spirit_t *ctx, uint8_t mode );
```

## Example Description

> This example reads and processes data from SPIRIT clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;
    spirit_cfg_t cfg;

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

    spirit_cfg_setup( &cfg );
    SPIRIT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit_init( &spirit, &cfg );
    Delay_ms( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit_power_module( &spirit, SPIRIT_MODULE_WAKE_UP );
    spirit_reset( &spirit );
    spirit_set_mode( &spirit, SPIRIT_OPERATING_MODE );
    Delay_ms( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_COMMAND_MODE );
    spirit_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_READ_MODULE_VERSION );
    spirit_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit_send_cmd_with_parameter( &spirit, SPIRIT_CMD_CFG_TXRX_LED, SPIRIT_PCFG_TXRXLED_OPEN_DRAIN );
    spirit_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_STORE_CURRENT_CONFIG );
    spirit_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_OPERATING_MODE );
    spirit_process( );
    log_info( &logger, "---- The module has been configured ----" );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif 
    Delay_ms( 1000 );
}

```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void ) {
#ifdef DEMO_APP_RECEIVER
    spirit_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit_generic_write( &spirit, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms( 2000 );
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIRIT

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
