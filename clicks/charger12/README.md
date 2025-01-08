
---
# CHARGER 12 Click

> [CHARGER 12 Click](https://www.mikroe.com/?pid_product=MIKROE-3744) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3744&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application charges the batery.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger12

### Example Key Functions

- `charger12_cfg_setup` Config Object Initialization function. 
```c
void charger12_cfg_setup ( charger12_cfg_t *cfg );
``` 
 
- `charger12_init` Initialization function. 
```c
err_t charger12_init ( charger12_t *ctx, charger12_cfg_t *cfg );
```

- `charger12_generic_transfer` Generic transfer. 
```c
void charger12_generic_transfer ( charger12_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t tx_len, uint8_t rx_len );
```
 
- `charger12_mode_select` Charger mode selection. 
```c
uint8_t charger12_mode_select ( charger12_t *ctx, uint8_t mode_select );
```

- `charger12_spi_set_register` This function set spi register. 
```c
void charger12_spi_set_register ( charger12_t *ctx, uint8_t register_address, uint16_t register_value  );
```

### Application Init

> Iniztializes SPI driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    charger12_cfg_t cfg;

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

    charger12_cfg_setup( &cfg );
    CHARGER12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger12_init( &charger12, &cfg );

    Delay_ms ( 100 );
    charger12_mode_select( &charger12, CHARGER12_MODE_DISABLE );
    Delay_ms ( 100 );
    log_printf( &logger, "> App init done" );
}
```

### Application Task

> Executes additional functions based on user input.

```c
void application_task ( void )
{
    charger12_case_plus( );
    Delay_ms ( 1 );

    charger12_case_minus( );
    Delay_ms ( 1 );

    charger12_case_one( );
    Delay_ms ( 1 );     

    charger12_case_two( );
    Delay_ms ( 1 );   

    charger12_case_three( );
    Delay_ms ( 1 );

    charger12_case_four( );
    Delay_ms ( 1 );
}
```

### Note

> Additional Functions :

  - charger12_case_Plus()  - Increments Wiper position.
  - charger12_case_Minus() - Decrements Wiper position.
  - charger12_case_One()   - Selects 1st mode of operation.
  - charger12_case_Two()   - Selects 2nd mode of operation.
  - charger12_case_Three() - Selects 3rd mode of operation.
  - charger12_case_Four()  - Selects 4th mode of operation.

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
