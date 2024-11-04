\mainpage Main Page

---
# ISM RX Click

> ISM RX Click is a compact add-on board that contains a complete wireless RF digital data receiver. This board features the MAX1471, a low-power CMOS RF dual-channel receiver configurable through SPI serial interface from Maxim Integrated. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ism_rx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ism-rx-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ISMRX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISMRX Click driver.

#### Standard key functions :

- `ismrx_cfg_setup` Config Object Initialization function.
```c
void ismrx_cfg_setup ( ismrx_cfg_t *cfg );
```

- `ismrx_init` Initialization function.
```c
err_t ismrx_init ( ismrx_t *ctx, ismrx_cfg_t *cfg );
```

- `ismrx_default_cfg` Click Default Configuration function.
```c
err_t ismrx_default_cfg ( ismrx_t *ctx );
```

#### Example key functions :

- `ismrx_generic_write` ISM RX data writing function.
```c
err_t ismrx_generic_write ( ismrx_t *ctx, uint8_t reg, uint8_t data_in )
```

- `ismrx_master_reset` This sends command for resetting device.
```c
err_t ismrx_master_reset ( ismrx_t *ctx );
```

- `ismrx_get_data` ISM RX get miso pin state.
```c
uint8_t ismrx_get_data ( ismrx_t *ctx )
```

## Example Description

> This application shows capability of ISM RX Click board. 
It sets default configuration, and collects and processes
data from signal that received from ISM TX Click board. 
It can collect and process data from 2 type of the signal 
modulation( FSK and ASK ).

**The demo application is composed of two sections :**

### Application Init

> Initialization of log and communication, set's signal 
modulation(FSK/ASK), recive mode(continuous/discontinuous), 
default configuration for selected modulation, and 
reinitializes device for receiving mode.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx_cfg_t ismrx_cfg;  /**< Click config object. */

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
    ismrx_cfg_setup( &ismrx_cfg );
    ISMRX_MAP_MIKROBUS( ismrx_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ismrx_init( &ismrx, &ismrx_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    Delay_ms ( 1000 );

    ismrx_master_reset( &ismrx );

    ismrx.modulation = ISMRX_MODULATION_FSK;
    ismrx.receive_mode = ISMRX_RECEIVE_MODE_RX;

    if ( ismrx_default_cfg ( &ismrx ) < 0 )
    {
        log_error( &logger, " Default configuration error. " );
        log_info( &logger, " Please, select signal modulation and/or receive mode... " );
        for ( ; ; );
    }

    if ( ismrx_task_init( &ismrx, &ismrx_cfg ) < 0 )
    {
        log_error( &logger, " Application Task Error. " );
    }

    log_info( &logger, " Application Task " );

    if ( ISMRX_RECEIVE_MODE_DRX == ismrx.receive_mode )
    {
       ismrx_start_drx( &ismrx );
    }
}

```

### Application Task

> Collects samples of data from data line(MISO) when buffer 
is full converts samples to manchester encoded data, 
and checks for preamble(sync) data. If data is valid 
decodes data and converts bits to valid data and logs 
result of received decoded data.

```c

void application_task ( void )
{
    uint8_t transition = 0;
    
    clear_buffers ( );
    wait_for_data ( );
    Delay_50us ( );

    while ( manchester_cnt < MAN_BUF_SIZE )
    {
        transition = ismrx_get_data ( &ismrx );
        while ( transition == ismrx_get_data ( &ismrx ) );
        
        if ( transition )
        {
            manchester_buf[ manchester_cnt++ ] = '1';
            manchester_buf[ manchester_cnt++ ] = '0';
        }
        else
        {
            manchester_buf[ manchester_cnt++ ] = '0';
            manchester_buf[ manchester_cnt++ ] = '1';
        }
        Delay_500us ( );
        Delay_50us ( );
    }
    
    man_to_hex_array ( );
    
    for ( uint16_t byte_cnt = 0; byte_cnt < data_cnt; byte_cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) data_buf[ byte_cnt ] );
    }

    if ( data_cnt )
    {
        log_printf( &logger, "\r\n%s\r\n", &data_buf[ 2 ] );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX

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
