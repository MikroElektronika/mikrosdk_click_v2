
---
# POT 4 Click

> POT 4 Click is a compact add-on board with accurate selectable reference voltage output. This board features the PRS11R-425F-S103B1, a high-quality 11mm rotary 10k potentiometer from Bourns. The PRS11R-425F-S103B1 features a small form factor, offers an push-on momentary switch, a flatted shaft style, and a wide operating temperature range. It comes with a high-resolution 12-bit ADC, detecting even the slightest move while digitizing its position, alongside a rail-to-rail buffering operational amplifier, which provides constant input and output impedance. Besides, the user can process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pot-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the POT 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for POT 4 Click driver.

#### Standard key functions :

- `pot4_cfg_setup` Config Object Initialization function.
```c
void pot4_cfg_setup ( pot4_cfg_t *cfg );
```

- `pot4_init` Initialization function.
```c
err_t pot4_init ( pot4_t *ctx, pot4_cfg_t *cfg );
```

#### Example key functions :

- `pot4_get_switch_pin` This function returns the switch (SW) pin logic state.
```c
uint8_t pot4_get_switch_pin ( pot4_t *ctx );
```

- `pot4_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pot4_read_voltage ( pot4_t *ctx, float *voltage );
```

- `pot4_convert_voltage_to_percents` This function converts analog voltage to potentiometer position in percents.
```c
uint8_t pot4_convert_voltage_to_percents ( pot4_t *ctx, float voltage );
```

## Example Description

> This example demonstrates the use of POT 4 Click board by reading and displaying the potentiometer position.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot4_cfg_t pot4_cfg;  /**< Click config object. */

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
    pot4_cfg_setup( &pot4_cfg );
    POT4_MAP_MIKROBUS( pot4_cfg, MIKROBUS_1 );
    err_t init_flag = pot4_init( &pot4, &pot4_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the potentiometer position in forms of voltage and percents once per second only when the potentiometer switch is active.

```c

void application_task ( void )
{
    if ( !pot4_get_switch_pin ( &pot4 ) )
    {
        float voltage = 0;
        if ( POT4_OK == pot4_read_voltage ( &pot4, &voltage ) ) 
        {
            log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
            log_printf( &logger, " Potentiometer : %u %%\r\n\n", 
                        ( uint16_t ) pot4_convert_voltage_to_percents ( &pot4, voltage ) );
            Delay_ms ( 1000 );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.POT4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
