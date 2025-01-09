
---
# MAGNETO 4 Click

> [MAGNETO 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3522) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3522&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> Reads and logs magnetic field strength values
> if magnetic field strength values bigger than 3000, 
> start magnetic linear position mode,   
> when moving the sensor from left to right the position for 1 step is reduced.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto4

### Example Key Functions

- `magneto4_cfg_setup` Config Object Initialization function. 
```c
void magneto4_cfg_setup ( magneto4_cfg_t *cfg );
``` 
 
- `magneto4_init` Initialization function. 
```c
err_t magneto4_init ( magneto4_t *ctx, magneto4_cfg_t *cfg );
```

- `magneto4_default_cfg` Click Default Configuration function. 
```c
void magneto4_default_cfg ( magneto4_t *ctx );
```

- `magneto4_get_magnetic_status` Get Magnetic measurement status. 
```c
uint8_t magneto4_get_magnetic_status ( magneto4_t *ctx, mag_status_t *mag_status );
```
 
- `magneto4_get_encoder_position` Encoder position. 
```c
void magneto4_get_encoder_position ( magneto4_t *ctx );
```

- `magneto4_get_encoder_direction` Encoder direction. 
```c
uint8_t magneto4_get_encoder_direction ( magneto4_t *ctx, mag_status_t *mag_status );
```

### Application Init

> Initializes Driver init and sets start encoder position on the zero.
> Reads and logs magnetic field strength values.
> For starting an encoder, it is necessary that the magnetic field strength 
> is greater than 3000.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto4_cfg_t cfg;

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

    magneto4_cfg_setup( &cfg );
    MAGNETO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto4_init( &magneto4, &cfg );
    
    magneto4_default_cfg ( &magneto4 );
    
    log_printf( &logger, " --- Please, bring the magnet close ---\r\n" );

    while ( magnetic_field < MAGNETO4_MAX_MAGNETIC_FIELD_VALUE )
    {
        magnetic_field = magneto4_get_magnetic_field( &magneto4 );
        log_printf( &logger, " Magnetic field strength : %d\r\n", magnetic_field );
        Delay_ms ( 1000 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
    log_printf( &logger, " --- Magnetic Linear Position ---\r\n" );
}
```

### Application Task

> When moving the sensor from left to right, one step is added 
> and when moving from right to left, the position for 1 step is reduced.

```c
void application_task ( void )
{
    //  Task implementation.
    
    magneto4_get_encoder_position( &magneto4 );
    
    enc_position = magneto4.encoder_position;

    if ( old_position != enc_position )
    {
        log_printf( &logger, " Encoder position : %d\r\n", enc_position );
        log_printf( &logger, " ------------------------\r\n" );
    }
    
    old_position = enc_position;
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
