
---
# Boost-inv 2 Click

> [Boost-inv 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3123) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3123&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> First increse positiv voltage by 2V every 3 seconda, 
> then decrese negative value for -2v every 3 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boostinv2

### Example Key Functions

- `boostinv2_cfg_setup` Config Object Initialization function. 
```c
void boostinv2_cfg_setup ( boostinv2_cfg_t *cfg );
``` 
 
- `boostinv2_init` Initialization function. 
```c
err_t boostinv2_init ( boostinv2_t *ctx, boostinv2_cfg_t *cfg );
```

- `boostinv2_default_cfg` Click Default Configuration function. 
```c
void boostinv2_default_cfg ( boostinv2_t *ctx );
```

- `boostinv2_set_positive_voltage` Functions for set positive output voltage. 
```c
void boostinv2_set_positive_voltage ( boostinv2_t *ctx, uint16_t voltage );
```
 
- `boostinv2_set_negative_voltage` Functions for set negative output voltage. 
```c
void boostinv2_set_negative_voltage ( boostinv2_t *ctx, uint16_t voltage );
```

- `boostinv2_generic_transfer` Generic transfer function. 
```c
void boostinv2_generic_transfer ( boostinv2_t *ctx, spi_master_transfer_data_t *block );
```

### Application Init

> Initializes Driver init and enable chip

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv2_cfg_t cfg;

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

    boostinv2_cfg_setup( &cfg );
    BOOSTONV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv2_init( &boostinv2, &cfg );
    
    boostinv2_enable( &boostinv2 );   
} 
```

### Application Task

> Changes the positive and negative output voltage. 
> Positive output voltage goes from 5V to 15V. 
> Negative output voltage goes from -5V to -15V

```c
void application_task ( void )
{
     // Positive output voltage 
     log_printf( &logger, "VOUT = 6V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_6V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = 14V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_14V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     
     // Negative output voltage 
     
     log_printf( &logger, "VOUT = -5V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_5V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = -13V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_13V );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     Delay_ms ( 1000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms ( 1000 );
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
