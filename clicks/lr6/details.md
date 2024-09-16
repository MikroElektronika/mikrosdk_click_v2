
---
# LR 6 click

> LR 6 Click is a compact add-on board designed for ultra-long-distance spread-spectrum communication. This board features the Ra-01S, a LoRa™ wireless radio frequency module from Ai-Thinker Technology, featuring the SX1268 radio chip. This module provides exceptional sensitivity of over -148dBm, a power output of +22dBm, and supports multiple modulation methods, including LoRa™, within the 433MHz frequency band. The board offers robust anti-interference capabilities and low power consumption, making it ideal for applications requiring reliable long-range communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the LR 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LR 6 Click driver.

#### Standard key functions :

- `lr6_cfg_setup` Config Object Initialization function.
```c
void lr6_cfg_setup ( lr6_cfg_t *cfg );
```

- `lr6_init` Initialization function.
```c
err_t lr6_init ( lr6_t *ctx, lr6_cfg_t *cfg );
```

- `lr6_default_cfg` Click Default Configuration function.
```c
err_t lr6_default_cfg ( lr6_t *ctx );
```

#### Example key functions :

- `lr6_send_data` This function sends a desired number of data bytes to the buffer by using the selected mode using the SPI serial interface.
```c
err_t lr6_send_data ( lr6_t *ctx, uint8_t *send_data, uint8_t len, uint8_t mode );
```

- `lr6_receive_data` This function receives a desired number of data bytes to the buffer by using the SPI serial interface.
```c
err_t lr6_receive_data ( lr6_t *ctx, uint8_t *receive_data, uint16_t buff_len, uint8_t *rx_len );
```

- `lr6_set_lr_config` This function performs the desired LoRa configuration by using the SPI serial interface.
```c
err_t lr6_set_lr_config ( lr6_t *ctx, lr6_lora_cfg_t lora_cfg );
```

## Example Description

> This example demonstrates the use of LR 6 click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr6_cfg_t lr6_cfg;  /**< Click config object. */

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
    lr6_cfg_setup( &lr6_cfg );
    LR6_MAP_MIKROBUS( lr6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == lr6_init( &lr6, &lr6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LR6_ERROR == lr6_default_cfg ( &lr6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " --------------------\r\n" );
}
```

### Application Task

> The demo application is an echo example that sends a demo LoRa packet string 
> and receives and processes all incoming data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t rx_data[ 255 ] = { 0 };
    if ( LR6_OK == lr6_send_data( &lr6, LR6_DEMO_TEXT, strlen( LR6_DEMO_TEXT ), LR6_TX_MODE_SYNC ) ) 
    {
        log_info( &logger, " Send - success" );
        uint8_t rx_len = 0;
        do 
        {
            if ( LR6_OK == lr6_receive_data( &lr6, rx_data, strlen( LR6_DEMO_TEXT ), &rx_len ) )
            {
                if ( rx_len > 0 )
                { 
                    log_info( &logger, " Receive - success" );
                    log_printf( &logger, " > Receive: " );
                    for ( uint8_t cnt = 0; cnt < strlen( LR6_DEMO_TEXT ); cnt++ )
                    {
                        log_printf( &logger, "%c", rx_data[ cnt ] );
                    }

                    int8_t rssi, snr;
                    if ( LR6_OK == lr6_get_packet_status( &lr6, &rssi, &snr ) )
                    {
                        log_printf( &logger, " Rssi Pkt: %d dBm\r\n", ( int16_t ) rssi );
                        log_printf( &logger, " Snr Pkt : %d dB\r\n", ( int16_t ) snr );
                        log_printf( &logger, " --------------------\r\n" );
                        break;
                    }
                }
            }
        } 
		while ( rx_len == 0 );
    }
    else
    {
        log_info( &logger, "Send - fail" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LR6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
