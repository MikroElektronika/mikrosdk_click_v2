
---
# EEPROM 4 Click

> [EEPROM 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2536) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2536&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click is a memmory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom4

### Example Key Functions

- `eeprom4_cfg_setup` Config Object Initialization function. 
```c
void eeprom4_cfg_setup ( eeprom4_cfg_t *cfg );
``` 
 
- `eeprom4_init` Initialization function. 
```c
err_t eeprom4_init ( eeprom4_t *ctx, eeprom4_cfg_t *cfg );
```

- `eeprom4_default_cfg` Click Default Configuration function. 
```c
void eeprom4_default_cfg ( eeprom4_t *ctx );
```

- `eeprom4_write_status_reg` Status register write function. 
```c
void eeprom4_write_status_reg( eeprom4_t *ctx, uint8_t data_value );
```
 
- `eeprom4_write_memory` Memory array write function. 
```c
void eeprom4_write_memory( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_input, uint8_t n_bytes );
```

- `eeprom4_read_memory` Memory array read function. 
```c
void eeprom4_read_memory( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_output, uint8_t n_bytes );
```

### Application Init

>
> Initializes Click driver and configures Click that all memory block > is unprotected.
> Also configures that HOLD operation is disabled, and the memory and > status register are writable.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom4_cfg_t cfg;

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

    eeprom4_cfg_setup( &cfg );
    EEPROM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom4_init( &eeprom4, &cfg );
}
```

### Application Task

>
> Enables writting to memory array, writes data from buffer to memory,
> checks if the part is in a write cycle, and if is not reads data >  > from memory array and stores data to buffer.
> Storaged data shows on USB UART.
> 

```c
void application_task (  )
{
    uint8_t data_write[ 13 ] = { 'M', 'i', 'K', 'r', 'O', 'e', 0 };
    uint8_t data_read[ 255 ] = { 0 };
    uint8_t cnt;
    uint8_t check_state;

    eeprom4_send_command( &eeprom4, EEPROM4_SET_WRITE_ENABLE_LATCH_COMMAND );
    eeprom4_write_memory( &eeprom4, EEPROM4_FIRST_MEMORY_LOCATION, data_write, 
6 );

    cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
    check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    
    while ( cnt | check_state )
    {
        cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
        check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    }
    
    eeprom4_read_memory( &eeprom4, 0x00000000, data_read, 6 );

    for ( cnt = 0; cnt < 6; cnt++ )
    {
        log_printf( &logger, " %c ", data_read[cnt] );
    }
    log_printf( &logger, "-----   \r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
