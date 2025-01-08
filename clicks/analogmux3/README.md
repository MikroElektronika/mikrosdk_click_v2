
---
# Analog MUX 3 Click

> [Analog MUX 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4580) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4580&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Analog MUX 3 Click board.
> This application controls the multiplexing of a single input channel
> with an eight-channel matrix switch.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMux3

### Example Key Functions

- `analogmux3_cfg_setup` Config Object Initialization function.
```c
void analogmux3_cfg_setup ( analogmux3_cfg_t *cfg );
```

- `analogmux3_init` Initialization function.
```c
err_t analogmux3_init ( analogmux3_t *ctx, analogmux3_cfg_t *cfg );
```

- `analogmux3_default_cfg` Click Default Configuration function.
```c
void analogmux3_default_cfg ( analogmux3_t *ctx );
```

- `analogmux3_generic_write` Analog MUX 3 data writing function.
```c
err_t analogmux3_generic_write ( analogmux3_t *ctx, uint8_t data_in );
```

- `analogmux3_set_channel` Analog MUX 3 set channel function.
```c
err_t analogmux3_set_channel ( analogmux3_t *ctx, uint8_t mux_ch );
```

- `analogmux3_read_an_pin_voltage` Analog MUX 3 read AN pin voltage level function.
```c
err_t analogmux3_read_an_pin_voltage ( analogmux3_t *ctx, float *data_out );
```

### Application Init

> Initializes SPI and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
> set the default configuration and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux3_cfg_t analogmux3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    analogmux3_cfg_setup( &analogmux3_cfg );
    ANALOGMUX3_MAP_MIKROBUS( analogmux3_cfg, MIKROBUS_1 );
    
    // Vref STM32F407ZG
    analogmux3_cfg.vref = 2.048;
    
    // Vref PIC18F97J94
    // analogmux3_cfg.vref = 3.3;
    
    err_t init_flag  = analogmux3_init( &analogmux3, &analogmux3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    analogmux3_default_cfg ( &analogmux3 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Analog MUX 3 Click board.
> In this example, we switch from channel AN0 to channel AN7, 
> read and display the analog value and voltage on the active channel.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t ch_pos = ANALOGMUX3_SET_CHANNEL_0; ch_pos <= ANALOGMUX3_SET_CHANNEL_7; ch_pos++ ) {
        analogmux3_set_channel( &analogmux3, ch_pos );
        Delay_ms ( 1000 );
        
        uint16_t analogmux3_an_value = 0;
    
        log_printf( &logger, "   CHANNEL    : AN%u     \r\n", ch_pos );
        log_printf( &logger, "- - - - - - - - - - - - - \r\n" );

        if ( analogmux3_read_an_pin_value ( &analogmux3, &analogmux3_an_value ) != ADC_ERROR ) {
            log_printf( &logger, "   ADC Value  : %u\r\n", analogmux3_an_value );
        }
    
        float analogmux3_an_voltage = 0;

        if ( analogmux3_read_an_pin_voltage ( &analogmux3, &analogmux3_an_voltage ) != ADC_ERROR ) {
            log_printf( &logger, "   AN Voltage : %.3f V \r\n", analogmux3_an_voltage );
        }
        
        log_printf( &logger, "-------------------------\r\n" );
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
