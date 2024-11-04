
---
# ISM TX Click

> ISM TX Click is a compact add-on board that contains an ASK and (G)FSK transmitter with a programmable SPI interface. This board features the MAX41460, a UHF sub-GHz ISM/SRD transmitter designed to transmit On-Off Keying (OOK), Amplitude- Shift Keying (ASK), Frequency-Shift Keying (FSK), and Gaussian (G)FSK (or 2GFSK) data from Maxim Integrated. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ismtx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ism-tx-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ISMTX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISMTX Click driver.

#### Standard key functions :

- `ismtx_cfg_setup` Config Object Initialization function.
```c
void ismtx_cfg_setup ( ismtx_cfg_t *cfg );
```

- `ismtx_init` Initialization function.
```c
err_t ismtx_init ( ismtx_t *ctx, ismtx_cfg_t *cfg );
```

- `ismtx_default_cfg` Click Default Configuration function.
```c
err_t ismtx_default_cfg ( ismtx_t *ctx );
```

#### Example key functions :

- `ismtx_set_cfg` ISM TX writing configuration.
```c
err_t ismtx_set_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t cfg_value )
```

- `ismtx_set_frequency` Setting specific frequency for transmission.
```c
err_t ismtx_set_frequency ( ismtx_t *ctx, uint32_t freq )
```

- `ismtx_transmit_data` Function for transmitting data with preamble byte and lenght.
```c
err_t ismtx_transmit_data ( ismtx_t *ctx, uint8_t preamble_byte, uint8_t *tx_data, uint8_t tx_data_len );
```

## Example Description

> This application shows capability of ISM TX Click board. 
It sets default configuration, and transmits data in 
manchester encoding with FSK or ASK signal modulation.

**The demo application is composed of two sections :**

### Application Init

> Initialization of log and communication, set's signal modulation, 
 resets device, and set's default configuration for selected modulation.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ismtx_cfg_t ismtx_cfg;  /**< Click config object. */

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
    ismtx_cfg_setup( &ismtx_cfg );
    ISMTX_MAP_MIKROBUS( ismtx_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ismtx_init( &ismtx, &ismtx_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    ismtx.modulation = ISM_TX_MODULATION_FSK;

    ismtx_soft_reset( &ismtx );
    
    if ( ismtx_default_cfg ( &ismtx ) < 0 )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, select correct signal modulation... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Transmits data via external antenna in span of 100ms.

```c

void application_task ( void ) 
{
    log_info( &logger, " Data sent: %s", tx_data_buf );
    ismtx_transmit_data( &ismtx, PREAMBLE_BYTE, tx_data_buf, sizeof( tx_data_buf ) );
    Delay_ms ( 100 );
}

```

## Note

> Default configuration configures device and set's transmission frequency to 433.92 MHz.
 If selected modulation is FSK frequency deviation is set to 40kHz.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMTX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
