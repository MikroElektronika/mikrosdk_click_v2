
---
# Analog MUX 2 Click

> [Analog MUX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4468) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4468&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application controls the multiplexing of a single input channel
with an eight-channel matrix switch.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMux2

### Example Key Functions

- `analogmux2_cfg_setup` Config Object Initialization function.
```c
void analogmux2_cfg_setup ( analogmux2_cfg_t *cfg );
```

- `analogmux2_init` Initialization function.
```c
err_t analogmux2_init ( analogmux2_t *ctx, analogmux2_cfg_t *cfg );
```

- `analogmux2_default_cfg` Click Default Configuration function.
```c
void analogmux2_default_cfg ( analogmux2_t *ctx );
```

- `analogmux2_set_channel` Analog MUX 2 set channel function.
```c
err_t analogmux2_set_channel ( analogmux2_t *ctx, uint8_t mux_ch );
```

- `analogmux2_read_an_pin_value` Analog MUX 2 read AN pin value function.
```c
err_t analogmux2_read_an_pin_value ( analogmux2_t *ctx, uint16_t *data_out );
```

- `analogmux2_read_an_pin_voltage` Analog MUX 2 read AN pin voltage level function.
```c
err_t analogmux2_read_an_pin_voltage ( analogmux2_t *ctx, float *data_out );
```

### Application Init

> Initializes I2C and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
set the default configuration and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux2_cfg_t analogmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    analogmux2_cfg_setup( &analogmux2_cfg );
    ANALOGMUX2_MAP_MIKROBUS( analogmux2_cfg, MIKROBUS_1 );
    
    // Vref STM32F407ZG
    analogmux2_cfg.vref = 2.048;
    
    err_t init_flag = analogmux2_init( &analogmux2, &analogmux2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    analogmux2_default_cfg ( &analogmux2 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Analog MUX 2 Click board.
In this example, we switch from channel AN0 to channel AN7, 
read and display the analog value and voltage on the active channel.
Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    for ( uint8_t ch_pos = ANALOGMUX2_SET_CHANNEL_0; ch_pos <= ANALOGMUX2_SET_CHANNEL_7; ch_pos++ ) {
        analogmux2_set_channel( &analogmux2, ch_pos );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        uint16_t analogmux2_an_value = 0;
    
        log_printf( &logger, "   CHANNEL    : AN%u     \r\n", ( uint16_t ) analogmux2_get_channel( &analogmux2 ) );
        log_printf( &logger, "- - - - - - - - - - - - - \r\n" );

        if ( analogmux2_read_an_pin_value ( &analogmux2, &analogmux2_an_value ) != ADC_ERROR ) {
            log_printf( &logger, "   ADC Value  : %u\r\n", analogmux2_an_value );
        }
    
        float analogmux2_an_voltage = 0;

        if ( analogmux2_read_an_pin_voltage ( &analogmux2, &analogmux2_an_voltage ) != ADC_ERROR ) {
            log_printf( &logger, "   AN Voltage : %.3f V \r\n", analogmux2_an_voltage );
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
