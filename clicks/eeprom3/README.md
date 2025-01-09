
---
# EEPROM 3 Click

> [EEPROM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1989) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1989&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the process of reading and writing to the EEPROM.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom3

### Example Key Functions

- `eeprom3_cfg_setup` Config Object Initialization function.
```c
void eeprom3_cfg_setup ( eeprom3_cfg_t *cfg ); 
```

- `eeprom3_init` Initialization function.
```c
err_t eeprom3_init ( eeprom3_t *ctx, eeprom3_cfg_t *cfg );
```

- `eeprom3_write_byte` This function writes data to the desired register.
```c
void eeprom3_write_byte ( eeprom3_t *ctx, uint16_t reg_address, uint8_t data_in );
```
 
- `eeprom3_write_page` This function writes given number of data to the desired register.
```c
void eeprom3_write_page( eeprom3_t *ctx, uint16_t reg_address, uint8_t* data_in, uint8_t count );
```

- `eeprom3_read` This function reads data from the desired register.
```c
void eeprom3_read ( eeprom3_t *ctx, uint16_t reg_address, uint8_t *data_out, uint16_t count );
```

### Application Init

> Initializes EEPROM 3 driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom3_cfg_t cfg;

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
    eeprom3_cfg_setup( &cfg );
    EEPROM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom3_init( &eeprom3, &cfg );
}
```

### Application Task

> Writing data to EEPROM, reading that data and displaying it via UART

```c
void application_task ( void )
{
    eeprom3_write_page( &eeprom3, 0x100, text, 6 );
    log_printf( &logger, "Writing Mikroe to EEPROM 3 Click\r\n" );
    Delay_ms ( 1000 );
    
    eeprom3_read( &eeprom3, 0x100, mem_value, 6 );
    log_printf( &logger, "Data read: %s\r\n", mem_value );
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
