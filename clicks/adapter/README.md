
---
# Adapter Click

> [Adapter Click](https://www.mikroe.com/?pid_product=MIKROE-1432) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1432&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> Adapter Click is a breakout board which simplifies connection of add-on boards. 
> There are two ways of establishing connection: using male or female IDC10 connectors. 
> Male header must be soldered on the top side of Adapter Click to connect the add-on board 
> directly or via flat cable. Female header can be soldered either on the top, or the bottom 
> side, depending on which one is more convenient in given circumstances.  
> There are two jumpers for SPI/I2C selection and one for selection of power supply range.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adapter

### Example Key Functions

- `adapter_cfg_setup` Config Object Initialization function. 
```c
void adapter_cfg_setup ( adapter_cfg_t *cfg );
``` 
 
- `adapter_init` Initialization function. 
```c
err_t adapter_init ( adapter_t *ctx, adapter_cfg_t *cfg );
```

- `adapter_generic_write` This function writes data to the desired register. 
```c
void adapter_generic_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `adapter_generic_read` This function reads data from the desired register. 
```c
void adapter_generic_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initalizes I2C or SPI driver and makes an initial log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adapter_cfg_t cfg;

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

    adapter_cfg_setup( &cfg );
    ADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adapter_init( &adapter, &cfg );
}
```

### Application Task

> This is an example that shows the use of the Adapter Click board (SPI mode -  set as default). 
> In I2C mode we are reading internal temperature from another device (THERMO 5 Click board).
> In SPI mode example we are writing "mikroElektronika" on SRAM Click board, 
> and than reading from the same memory location.

```c
void application_task ( void )
{
    float temp_value;

    if ( adapter.master_sel == ADAPTER_MASTER_SPI )
    {
        log_printf( &logger, " Writing text :\r\n" );
   
        for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
        {
            sram_write_byte( &adapter, n_cnt, send_buffer[ n_cnt ] );
            Delay_ms ( 100 );
            log_printf( &logger, "%c", send_buffer[ n_cnt ] );
        }
    
    
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " Read text :\r\n" );
        for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
        {
            mem_data[ n_cnt ] = sram_read_byte( &adapter, n_cnt );
            Delay_ms ( 100 );
            log_printf( &logger, "%c", mem_data[ n_cnt ] );
        }   
        log_printf( &logger, "\r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    
        Delay_ms ( 1000 );
    }
    else if ( adapter.master_sel == ADAPTER_MASTER_I2C )
    {
        temp_value = thermo5_read_inter_temp( &adapter );

        log_printf( &logger, " Thermo 5 internal temperature :  %.2f\r\n", temp_value );
        log_printf( &logger, "--------------------------\r\n" );
    
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
