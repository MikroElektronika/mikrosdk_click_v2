
---
# ATA663254 Click

> [ATA663254 Click](https://www.mikroe.com/?pid_product=MIKROE-2872) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2872&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This application demonstates the use of ATA663254 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata663254

### Example Key Functions

- `ata663254_cfg_setup` Config Object Initialization function. 
```c
void ata663254_cfg_setup ( ata663254_cfg_t *cfg );
``` 
 
- `ata663254_init` Initialization function. 
```c
err_t ata663254_init ( ata663254_t *ctx, ata663254_cfg_t *cfg );
```

- `ata663254_enable` Chip enable function. 
```c
void ata663254_enable ( ata663254_t *ctx, uint8_t state );
```

- `ata663254_get_rst_state` Undervoltage detect function. 
```c
uint8_t ata663254_get_rst_state ( ata663254_t *ctx );
```

- `ata663254_generic_write` Generic multi write function. 
```c
void ata663254_generic_write ( ata663254_t *ctx, char *data_buf,  uint16_t len );
```

- `ata663254_generic_read` Generic multi read function. 
```c
int32_t ata663254_generic_read ( ata663254_t *ctx, char *data_buf,  uint16_t len );
```

### Application Init

> Initializes the Click driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663254_cfg_t cfg;

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

    ata663254_cfg_setup( &cfg );
    ATA663254_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663254_init( &ata663254, &cfg );
    
    ata663254_enable( &ata663254, 1 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message each 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling
    
    int32_t len = ata663254_generic_read( &ata663254, rec_buf, 50 );
    if ( len > 6 )
    {
        log_printf( &logger, "Received data: " );
        for ( int32_t cnt = 0; cnt < len; cnt++  )
        {
            log_printf( &logger, "%c", rec_buf[ cnt ] );
        }
        memset( rec_buf, 0 , 50 );
    }
    Delay_ms ( 100 );
#endif
#ifdef DEMO_APP_TRANSMITTER

    // TRANSMITER - TX each 2 sec
       
    ata663254_generic_write( &ata663254, demo_message, 9 );
    log_info( &logger, "--- Data sent ---" );

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
