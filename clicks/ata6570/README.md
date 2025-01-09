
---
# ATA6570 Click

> [ATA6570 Click](https://www.mikroe.com/?pid_product=MIKROE-2900) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2900&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is interfaces a Controller Area Network (CAN) protocol controller and the physical two-wire CAN bus.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata6570

### Example Key Functions

- `ata6570_cfg_setup` Config Object Initialization function. 
```c
void ata6570_cfg_setup ( ata6570_cfg_t *cfg );
``` 
 
- `ata6570_init` Initialization function. 
```c
err_t ata6570_init ( ata6570_t *ctx, ata6570_cfg_t *cfg );
```

- `ata6570_write_reg` Write Register. 
```c
void ata6570_write_reg( ata6570_t *ctx, const uint8_t address, uint8_t input );
```
 
- `ata6570_read_reg` Read Register. 
```c
uint8_t ata6570_read_reg( ata6570_t *ctx, const uint8_t address );
```

### Application Init

> In addition to this module is palced inside normal working mode cappable of tranmission and reception of data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ata6570_cfg_t cfg;

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

    ata6570_cfg_setup( &cfg );
    ATA6570_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata6570_init( &ata6570, &cfg );
    ata6570_write_reg( &ata6570, ATA6570_DMCR, ATA6570_OPMODE_NORMAL );
    Delay_ms ( 500 );
}
```

### Application Task

> Tranismiter/Receiver task depend on uncommented code
  Receiver logging each received byte to the UART for data logging, while transmiter send message each
  2 seconds.

```c
void application_task ( void )
{
     //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER
       // RECEIVER - UART polling
      rsp_size = ata6570_generic_read( &ata6570, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

      if ( rsp_size > 0 )
        {  
            log_printf( &logger, "%s", uart_rx_buffer );
            memset( uart_rx_buffer, 0, rsp_size );
        }  
#endif
       
#ifdef DEMO_APP_TRANSMITER
       // TRANSMITER - TX each 2 sec
       for( uint8_t i = 0; i < 8; i++ )
       {
           ata6570_generic_write( &ata6570, &demo_message[ i ], 1 );
       }
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
#endif
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
