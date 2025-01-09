
---
# SRAM Click

> [SRAM Click](https://www.mikroe.com/?pid_product=MIKROE-1902) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1902&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> SRAM Click write and read data from 23LC1024 Serial RAM device.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Sram

### Example Key Functions

- `sram_cfg_setup` Config Object Initialization function. 
```c
void sram_cfg_setup ( sram_cfg_t *cfg );
``` 
 
- `sram_init` Initialization function. 
```c
err_t sram_init ( sram_t *ctx, sram_cfg_t *cfg );
```

- `sram_default_cfg` Click Default Configuration function. 
```c
void sram_default_cfg ( sram_t *ctx );
```

- `sram_write_byte` Function write the 8-bit data to the target 24-bit register address of 23LC1024 chip. 
```c
void sram_write_byte ( sram_t *ctx, uint32_t reg_address, uint8_t write_data );
```
 
- `sram_read_byte` Function read the 8-bit data to the target 24-bit register address of 23LC1024 chip. 
```c
uint8_t sram_read_byte ( sram_t *ctx, uint32_t reg_address );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    sram_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    sram_cfg_setup( &cfg );
    SRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sram_init( &sram, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ SRAM Click  ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> SRAM Click communicates with register via SPI protocol by write data to and read data from 23LC1024 Serial RAM device. 
> Results are being sent to the UART where you can track their changes. 
> All data logs on USB UART for aproximetly every 5 sec.
> 

```c
void application_task ( void )
{
    log_printf( &logger, " Writing text :\r\n" );
   
    for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        sram_write_byte( &sram, n_cnt, send_buffer[ n_cnt ] );
        Delay_ms ( 100 );
        
        log_printf( &logger, "%c", send_buffer[ n_cnt ] );

        mem_data[ n_cnt ] = sram_read_byte( &sram, n_cnt );
    }
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, " Read text :\r\n" );
    log_printf( &logger, "%s", &mem_data[ 0 ] );
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
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
