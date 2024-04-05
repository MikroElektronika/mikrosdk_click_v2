
---
# LR 9 click

> LR 9 Click is a compact add-on board designed for ultra-long-range spread spectrum communication tasks within the LPWAN domain. This board is based on the RA-08, a LoRaWAN module from Ai-Thinker Technology, featuring the ASR6601 system-on-chip (SoC) that combines RF transceivers, modems, and a 32-bit RISC microcontroller (MCU). This module excels with its support for LoRa and (G)FSK modulation, a frequency range of 410MHz to 525MHz, and embedded storage of 128KB FLASH and 16KB SRAM, ensuring robust and versatile communication capabilities. Moreover, it's equipped with UART and I2C interfaces for easy programming and integration and an SMA antenna connector for enhanced connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LR 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR 9 Click driver.

#### Standard key functions :

- `lr9_cfg_setup` Config Object Initialization function.
```c
void lr9_cfg_setup ( lr9_cfg_t *cfg );
```

- `lr9_init` Initialization function.
```c
err_t lr9_init ( lr9_t *ctx, lr9_cfg_t *cfg );
```

#### Example key functions :

- `lr9_send_data_frame` This function sends the desired data frame by using the UART serial interface.
```c
err_t lr9_send_data_frame ( lr9_t *ctx, uint8_t confirm, uint8_t nbtrials, uint8_t *data_frame );
```

- `lr9_inquire_command` Using the UART serial interface, this function writes the desired query command with or without the included equals symbol.
```c
err_t lr9_inquire_command ( lr9_t *ctx, uint8_t *command, lr9_en_set_t en_set );
```

- `lr9_write_command` This function writes a desired command and parameter by using the UART serial interface.
```c
err_t lr9_write_command ( lr9_t *ctx, uint8_t *command, uint8_t *param );
```

## Example Description

> This example demonstrates the use of LR 9 click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs a hardware reset of the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr9_cfg_t lr9_cfg;  /**< Click config object. */

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
    lr9_cfg_setup( &lr9_cfg );
    LR9_MAP_MIKROBUS( lr9_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr9_init( &lr9, &lr9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr9_hw_reset( &lr9 );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CTXADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " > Transmitter < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CTX , LR9_RF_CFG_DEFAULT_TX );
    lr9_log_response( );
    Delay_ms ( 500 );
#else
    log_printf( &logger, " > Receiver < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CRXS , LR9_RF_CFG_DEFAULT_RX );
    lr9_log_response( );
    Delay_ms ( 500 );
#endif

    lr9_log_response( );
    Delay_ms ( 500 );
}
```

### Application Task

> Depending on the selected mode, the application demo 
> receives and processes all incoming data or sends the LoRa packet demo string.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr9_send_data_frame( &lr9, LR9_DTRX_CONFIG_DATA, LR9_NB_TRIALS_2, LR9_DEMO_STRING );
    lr9_log_response( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    lr9_log_receiver( );
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
