
---
# EEPROM 2 Click

> [EEPROM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1909) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1909&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the process of writing and
> reading of data from EEPROM.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom2

### Example Key Functions

- `eeprom2_cfg_setup` Config Object Initialization function.
```c
void eeprom2_cfg_setup ( eeprom2_cfg_t *cfg ); 
```

- `eeprom2_init` Initialization function.
```c
err_t eeprom2_init ( eeprom2_t *ctx, eeprom2_cfg_t *cfg );
```

- `eeprom2_write` This function writes a single byte of data to the given memory address.
```c
void eeprom2_write ( eeprom2_t *ctx, uint32_t memory_address, uint8_t value );
```
 
- `eeprom2_write_bytes` This function writes bytes of data to the given memory address.
```c
void eeprom2_write_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );
```

- `eeprom2_read_bytes` This function reads bytes from the given memory address.
```c
void eeprom2_read_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );
```

### Application Init

> Initializes EEPROM 2 driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom2_cfg_t cfg;

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
    eeprom2_cfg_setup( &cfg );
    EEPROM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom2_init( &eeprom2, &cfg );
}
```

### Application Task

> Writing data to EEPROM and then reading that data and writing it via UART.
 

```c
void application_task ( void )
{
    eeprom2_write_bytes ( &eeprom2, 0x01, text, 6 );
    log_printf ( &logger, "Writing Mikroe to EEPROM 2 Click\r\n" );
    Delay_ms ( 1000 );
    eeprom2_read_bytes ( &eeprom2, 0x01 , mem_value, 6 );
    log_printf ( &logger, "Data read: %s\r\n", mem_value );
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
