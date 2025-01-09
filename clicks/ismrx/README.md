
---
# ISM RX Click

> [ISM RX Click](https://www.mikroe.com/?pid_product=MIKROE-4499) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4499&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This application shows capability of ISM RX Click board. 
It sets default configuration, and collects and processes
data from signal that received from ISM TX Click board. 
It can collect and process data from 2 type of the signal 
modulation( FSK and ASK ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX

### Example Key Functions

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
