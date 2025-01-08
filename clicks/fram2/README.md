
---
# FRAM 2 Click

> [FRAM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2768) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2768&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example performs write & read operation to certain register.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM2

### Example Key Functions

- `fram2_cfg_setup` Config Object Initialization function. 
```c
void fram2_cfg_setup ( fram2_cfg_t *cfg );
``` 
 
- `fram2_init` Initialization function. 
```c
err_t fram2_init ( fram2_t *ctx, fram2_cfg_t *cfg );
```

- `fram2_default_cfg` Click Default Configuration function. 
```c
void fram2_default_cfg ( fram2_t *ctx );
```

- `fram2_read` This function reads content from address and saves it to buffer. 
```c
void fram2_read ( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t count );
``` 

- `fram2_write` This function writes content from buffer to address. 
```c
void fram2_write ( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t counter );
```

- `fram2_read_status` This function reads content of FRAM status register. 
```c
uint8_t fram2_read_status ( fram2_t *ctx );
``` 

### Application Init

> Initiazlize device and enable write operation.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fram2_cfg_t cfg;

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

    fram2_cfg_setup( &cfg );
    FRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram2_init( &fram2, &cfg );
    fram2_default_cfg ( &fram2 );

}
```

### Application Task

> Write value 42 to register 0x10 and check if operation was done properly.

```c
void application_task ( void )
{
    log_info( &logger, "Writing value 42 into register 0x10..." );  
    test_addr = 0x0010;  
    fram2_write( &fram2, test_addr, data_to_write, 3 );
    Delay_ms ( 200 );

    log_info( &logger, "Reading from register 0x10..." );
    memset( read_buf, 0, 32 );
    Delay_ms ( 500 );
    
    fram2_read( &fram2, test_addr, read_buf, 3 );
    log_printf ( &logger, "Read value: %s\r\n\n", read_buf );
    Delay_ms ( 500 );
}
```

### Note

> If user doesn't see declarations of some variables in application_init() and application_task(),
they are declared as global in main.c file.

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
