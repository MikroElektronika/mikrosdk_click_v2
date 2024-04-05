\mainpage Main Page

---
# LR 10 click

> LR 10 Click is a compact add-on board designed for the Internet of Things (IoT) applications requiring low power consumption and long-range connectivity. This board features the Wio-E5, a LoRa wireless module from Seeed Technology. The Wio-E5 integrates the STM32WLE5JC system-level chip and the SX126X LoRa® chip alongside an Arm® Cortex® M4 MCU, ensuring ultra-low power usage and high performance. It supports multi-mode operations, including (G)FSK and LoRa®, and can operate across a frequency range of 868 to 928MHz with robust signal strength and sensitivity. These characteristics make the LR 10 Click ideal for various IoT scenarios, such as wireless sensor networks, remote meter readings, and other applications with crucial low-power, wide-area network connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-10-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LR 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR 10 Click driver.

#### Standard key functions :

- `lr10_cfg_setup` Config Object Initialization function.
```c
void lr10_cfg_setup ( lr10_cfg_t *cfg );
```

- `lr10_init` Initialization function.
```c
err_t lr10_init ( lr10_t *ctx, lr10_cfg_t *cfg );
```

#### Example key functions :

- `lr10_write_cmd` This function writes a desired command by using UART serial interface.
```c
err_t lr10_write_cmd ( lr10_t *ctx, uint8_t *command );
```

- `lr10_write_cmd_sub_param` This function writes a desired command, subcommands and parameter by using UART serial interface.
```c
err_t lr10_write_cmd_sub_param ( lr10_t *ctx, uint8_t *command, uint8_t *sub_param, 
                                              uint8_t *param, lr10_en_quote_t en_quote );
```

## Example Description

> This example demonstrates the use of LR 10 click board 
> by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs a hardware reset of the device
> and a group of commands for getting the FW version, the serial number, and the DevEUI. 
> After that, the demo app sets the RF configuration: 
> frequency, SF, bandwidth, TX preamble, RX preamble, and TX power settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr10_cfg_t lr10_cfg;  /**< Click config object. */

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
    lr10_cfg_setup( &lr10_cfg );
    LR10_MAP_MIKROBUS( lr10_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr10_init( &lr10, &lr10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lr10_hw_reset( &lr10 );
    Delay_ms ( 500 );

    lr10_generic_write( &lr10, LR10_CMD_AT, strlen(LR10_CMD_AT) );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_VER );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_ID );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );
    
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_MODE, LR10_SUB_CMD_MODE_TEST, 
                                     LR10_SYMBOL_NULL, LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_TEST );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_inquire_cmd( &lr10, LR10_CMD_MODE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RFCFG, 
                                     "868,SF7,125,8,8,14,ON,OFF,OFF", LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );
#endif  
}
```

### Application Task

> Depending on the selected mode, the application demo receives 
> and processes all incoming data or sends the LoRa packet demo string.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_TX_STR, 
                                     LR10_DEMO_STRING, LR10_QUOTE_ENABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
#else
    lr10_write_cmd_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RX );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_receiver( );
        lr10_clear_app_buf( );
    }
#endif
    Delay_ms ( 1000 );   
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
