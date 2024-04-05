
---
# Analog MUX 3 click

Analog MUX 3 Click is a compact add-on board that switches one of the eight inputs to one output. This board features the ADG738, a CMOS analog matrix switch with a serially-controlled SPI interface from Analog Devices. In an active state, the ADG738 conducts equally well in both directions, making it suitable for multiplexing and demultiplexing applications. It can also be configured as a type of switch array where any, all, or none of eight switches may be closed any time. All channels exhibit ‘break-before-make switching action, preventing momentary shorting when switching channels. This Click board™ is suitable for a wide range of applications, from industrial and instrumentation to medical, consumer, communications, and automotive systems.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/analog_mux_3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/analog-mux-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the AnalogMux3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AnalogMux3 Click driver.

#### Standard key functions :

- `analogmux3_cfg_setup` Config Object Initialization function.
```c
void analogmux3_cfg_setup ( analogmux3_cfg_t *cfg );
```

- `analogmux3_init` Initialization function.
```c
ANALOGMUX3_RETVAL analogmux3_init ( analogmux3_t *ctx, analogmux3_cfg_t *cfg );
```

- `analogmux3_default_cfg` Click Default Configuration function.
```c
void analogmux3_default_cfg ( analogmux3_t *ctx );
```

#### Example key functions :

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

## Example Description

> This is an example that demonstrates the use of the Analog MUX 3 click board.
> This application controls the multiplexing of a single input channel
> with an eight-channel matrix switch.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
> set the default configuration and start to write log.

```c

void application_init ( void ) {
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

> This is an example that shows the use of a Analog MUX 3 click board.
> In this example, we switch from channel AN0 to channel AN7, 
> read and display the analog value and voltage on the active channel.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMux3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
