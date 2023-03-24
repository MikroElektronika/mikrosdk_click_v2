
---
# Analog MUX 4 click

> Analog MUX 4 Click is a compact add-on board that switches one of many analog inputs to one digital output. This board features the TMUX1308, a general-purpose 8:1 single-ended CMOS multiplexer (MUX) from Texas Instruments. The TMUX1308 has an internal injection current control which eliminates the need for external diode and resistor networks to protect the switch and keep the input signals within the supply voltage. It also supports bidirectional analog and digital signals ranging from 0 to 5V, alongside several protection features allowing a reliable operation and protecting the device from potential damage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/analogmux4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/analog-mux-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the AnalogMUX4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AnalogMUX4 Click driver.

#### Standard key functions :

- `analogmux4_cfg_setup` Config Object Initialization function.
```c
void analogmux4_cfg_setup ( analogmux4_cfg_t *cfg );
```

- `analogmux4_init` Initialization function.
```c
err_t analogmux4_init ( analogmux4_t *ctx, analogmux4_cfg_t *cfg );
```

#### Example key functions :

- `analogmux4_enable_input` This function enables analog inputs.
```c
void analogmux4_enable_input ( analogmux4_t *ctx )
```

- `analogmux4_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t analogmux4_read_an_pin_voltage ( analogmux4_t *ctx, float *data_out );
```

- `analogmux4_set_input_channel` This function sets the analog input channel.
```c
void analogmux4_set_input_channel ( analogmux4_t *ctx, uint8_t channel );
```

## Example Description

> This example demonstrates the use of Analog MUX 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the analog inputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux4_cfg_t analogmux4_cfg;  /**< Click config object. */

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
    analogmux4_cfg_setup( &analogmux4_cfg );
    ANALOGMUX4_MAP_MIKROBUS( analogmux4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == analogmux4_init( &analogmux4, &analogmux4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    analogmux4_enable_input ( &analogmux4 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the voltage of all channels on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float analogmux4_an_voltage = 0;
    
    for ( uint8_t cnt = ANALOGMUX4_CHANNEL_0; cnt <= ANALOGMUX4_CHANNEL_7; cnt++ )
    {
        analogmux4_set_input_channel ( &analogmux4, cnt );
        if ( ADC_ERROR != analogmux4_read_an_pin_voltage ( &analogmux4, &analogmux4_an_voltage ) ) 
        {
            log_printf( &logger, " AN%u voltage : %.3f V\r\n", ( uint16_t ) cnt, analogmux4_an_voltage );
        }
    }
    log_printf( &logger, "\r\n" );
    Delay_ms( 1000 );
}

```

## Note

> The channel's voltage will "float" when the voltage source is not connected to it.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
