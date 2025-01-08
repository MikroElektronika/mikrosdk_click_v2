
---
# Semper Flash Click

> [Semper Flash Click](https://www.mikroe.com/?pid_product=MIKROE-3823) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3823&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize and use the Semper Flash Click. The Click
  is a 512 Mbit SPI Flash memory module. Data can be stored in and read from the flash
  memory. There's also the option of erasing it's contents. Here's how to do it. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SemperFlash

### Example Key Functions

- `semperflash_cfg_setup` Config Object Initialization function. 
```c
void semperflash_cfg_setup ( semperflash_cfg_t *cfg );
``` 
 
- `semperflash_init` Initialization function. 
```c
err_t semperflash_init ( semperflash_t *ctx, semperflash_cfg_t *cfg );
```

- `semperflash_default_cfg` Click Default Configuration function. 
```c
void semperflash_default_cfg ( semperflash_t *ctx );
```

- `semperflash_write_memory ` This function writes data to the flash memory. 
```c
uint8_t semperflash_write_memory  ( semperflash_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size  );
```
 
- `semperflash_read_memory ` This function reads data from the flash memory. 
```c
uint8_t semperflash_read_memory  ( semperflash_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size  );
```

- `semperflash_erase_memory` This function erases data from the flash memory. 
```c
void semperflash_erase_memory ( semperflash_t *ctx, uint32_t addr );
```

### Application Init

> This function initializes and configures the Click and logger modules. Additional con-
  figuring is done in the default_cfg(...) function. The device ID should appear in the 
  UART console if the setup finishes successfully.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    semperflash_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    semperflash_cfg_setup( &cfg );
    SEMPERFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    semperflash_init( &semperflash, &cfg );
    semperflash_default_cfg( &semperflash );
    id_check( );
    Delay_ms ( 500 );
}
```

### Application Task

> This function first erases the contents of the flash memory and then writes, reads and
  prints two strings in the UART console. It does so every 2 seconds. 

```c
void application_task ( void )
{
    char write_data_com[ 7 ] = "MikroE";
    char write_data_clk[ 13 ] = "Semper Flash";
    char read_buf_data[ 13 ] = { 0 };

    semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
    semperflash_erase_memory( &semperflash, ADRESS_MEMORY );
    
    if ( COMPANY_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_com, 6 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 6 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = CLICK_FLAG;       
    }
    else if ( CLICK_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_clk, 12 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 12 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = COMPANY_FLAG;
    }

    log_printf( &logger, "....................\r\n" );
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
