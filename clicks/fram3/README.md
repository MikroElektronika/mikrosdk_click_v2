
---
# FRAM 3 Click

> [FRAM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3817) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3817&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application writes data in memmory and reads data from memmory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM3

### Example Key Functions

- `fram3_cfg_setup` Config Object Initialization function. 
```c
void fram3_cfg_setup ( fram3_cfg_t *cfg );
``` 
 
- `fram3_init` Initialization function. 
```c
err_t fram3_init ( fram3_t *ctx, fram3_cfg_t *cfg );
```

- `fram3_read_free_access_memory` Memory read function. 
```c
uint8_t fram3_read_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );
```
 
- `fram3_write_free_access_memory` Memory write function. 
```c
uint8_t fram3_write_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );
```

### Application Init

> Initializes device init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fram3_cfg_t cfg;

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

    fram3_cfg_setup( &cfg );
    FRAM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram3_init( &fram3, &cfg );
}
```

### Application Task

> Writes and then reads data from memory

```c
void application_task (  )
{
    static char write_data[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };
    static char read_data[ 7 ];
    static uint8_t cnt;
    static uint8_t status_check;

    log_printf( &logger, " - Writing...  \r\n" );
    Delay_ms ( 500 );
    status_check = fram3_write_free_access_memory( &fram3, 0x00, &write_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR WRITING!!! \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, " - Reading... \r\n" );
    Delay_ms ( 500 );
    status_check = fram3_read_free_access_memory( &fram3, 0x00, &read_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR READING!!! \r\n" );
        for ( ; ; );
    }

    for ( cnt = 0; cnt < 7; cnt++ )
    {
        log_printf( &logger, " %c ", read_data[ cnt ] );
        Delay_ms ( 100 );
    }
    log_printf( &logger, " \r\n " );
    Delay_ms ( 1000 );
    log_printf( &logger, "__________________________\r\n " );
    Delay_ms ( 500 );
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
