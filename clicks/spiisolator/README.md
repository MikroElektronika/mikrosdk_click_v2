
---
# SPI Isolator Click

> [SPI Isolator Click](https://www.mikroe.com/?pid_product=MIKROE-2583) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2583&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> TThe Click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over SPI interface.
> In this example we have used an 8x8 Click board connected to a SPI Isolator Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Spiisolator

### Example Key Functions

- `spiisolator_cfg_setup` Config Object Initialization function. 
```c
void spiisolator_cfg_setup ( spiisolator_cfg_t *cfg );
``` 
 
- `spiisolator_init` Initialization function. 
```c
err_t spiisolator_init ( spiisolator_t *ctx, spiisolator_cfg_t *cfg );
```

- `spiisolator_generic_transfer` Generic transfer function. 
```c
void spiisolator_generic_transfer ( spiisolator_t *ctx, spi_master_transfer_data_t *block );
```
 
- `spiisolator_write_byte` Write the byte of data function. 
```c
void spiisolator_write_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t write_data );
```

- `spiisolator_read_byte` Read the byte of data function. 
```c
uint8_t spiisolator_read_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd );
```

### Application Init

> Initialization driver enables - SPI, set default configuration, also write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    spiisolator_cfg_t cfg;

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

    spiisolator_cfg_setup( &cfg );
    SPIISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spiisolator_init( &spiisolator, &cfg );
    
    c8x8_default_cfg( &spiisolator );

    Delay_100ms( );
}
```

### Application Task

> Controls an 8x8 Click board and displays the steps on UART Terminal.

```c
void application_task ( void )
{
    log_info( &logger, "> Display Character ..." );
    c8x8_display_byte( &spiisolator, demo_char );
    Delay_ms ( 1000 );

    log_info( &logger, "> Display String ..." );
    c8x8_display_string( &spiisolator, &demo_string[ 0 ] );
    Delay_ms ( 1000 );

    log_info( &logger, "> Display Image ON ..." );
    c8x8_display_image( &spiisolator, &demo_img_on[ 0 ] );
    Delay_ms ( 500 );

    log_info( &logger, "> Display Image OFF ..." );
    c8x8_display_image( &spiisolator, &demo_img_off[ 0 ] );
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
