
---
# Fram Click

> [Fram Click](https://www.mikroe.com/?pid_product=MIKROE-1486) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1486&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This app writing data to Click memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fram

### Example Key Functions

- `fram_cfg_setup` Config Object Initialization function. 
```c
void fram_cfg_setup ( fram_cfg_t *cfg );
``` 
 
- `fram_init` Initialization function. 
```c
err_t fram_init ( fram_t *ctx, fram_cfg_t *cfg );
```

- `fram_default_cfg` Click Default Configuration function. 
```c
void fram_default_cfg ( fram_t *ctx );
```

- `fram_write_enable` This function that sends write enable command to the chip. 
```c
void fram_write_enable ( fram_t *ctx );
```
 
- `fram_read` This function reads sequential memory locations to buffer. 
```c
void fram_read ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );
```

- `fram_write` This function writes to sequential memory locations from buffer. 
```c
void fram_write ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fram_cfg_t cfg;

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

    fram_cfg_setup( &cfg );
    FRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram_init( &fram, &cfg );
    fram_erase_all( &fram );
}
```

### Application Task

> Writing data to Click memory and displaying the read data via UART. 

```c
void application_task ( void )
{
    char wr_data[ 10 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
    char rd_data[ 10 ];

    log_printf( &logger, "Writing MikroE to  Fram memory, from address 0x0150: \r\n" );
    fram_write( &fram, 0x0150, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of Fram memory, from address 0x0150: \r\n" );
    fram_read( &fram, 0x0150, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %c \r\n", rd_data );
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
