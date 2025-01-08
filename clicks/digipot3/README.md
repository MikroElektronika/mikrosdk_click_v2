
---
# DIGI POT 3 Click

> [DIGI POT 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3016) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3016&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app get value from digital potentiometer and stored to the EEMEM memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot3

### Example Key Functions

- `digipot3_cfg_setup` Config Object Initialization function. 
```c
void digipot3_cfg_setup ( digipot3_cfg_t *cfg );
``` 
 
- `digipot3_init` Initialization function. 
```c
err_t digipot3_init ( digipot3_t *ctx, digipot3_cfg_t *cfg );
```

- `digipot3_default_cfg` Click Default Configuration function. 
```c
void digipot3_default_cfg ( digipot3_t *ctx );
```

- `digipot3_store_eemem` This function stores 16-bit data to the desired EEMEM (non volatile) memory location. 
```c
uint8_t digipot3_store_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t transfer_data );
```
 
- `digipot3_send_command` This function executes the desired command. 
```c
uint8_t digipot3_send_command ( digipot3_t *ctx, uint8_t command_byte );
```

- `digipot3_write_dac` This function writes 10-bit value to DAC register and determines the wiper position. 
```c
uint8_t digipot3_write_dac ( digipot3_t *ctx, uint16_t value_dac );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    digipot3_cfg_setup( &cfg );
    DIGIPOT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot3_init( &digipot3, &cfg );

    Delay_ms ( 200 );
    
    digipot3_read_dac(  &digipot3, &digital_value );
    digipot3_read_eemem( &digipot3, DIGIPOT3_RDAC_EEMEM_LOC, &eemem_value );
    
    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM );
    }

    log_printf( &logger, "DIGI POT 3 is initialized \r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Increments the wiper position by 6dB every 2 seconds. When wiper position
> reaches the desired value (0x0200), then the wiper position be decremented by 6dB every 2 seconds, until position 
> value reaches the new desired value (0x0002). After that the new position value will be stored to the EEMEM memory,
> if that value does not already exist in the EEMEM memory.

```c
void application_task ( void )
{
    while ( digital_value < 0x0200 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_INCREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    while ( digital_value > 0x0002 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_DECREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM );
        eemem_value = digital_value;
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
