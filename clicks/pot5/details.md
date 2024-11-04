
---
# POT 5 Click

> POT 5 Click is a compact add-on board with accurate selectable reference voltage output. This board features the PDB081-P10-103B1, a high-quality 8mm micro rotary 10k potentiometer from Bourns. The PDB081-P10-103B1 potentiometers operate over a wide temperature range, withstanding 50V maximum voltage. This rotary potentiometer offers 5Ω maximum resistance, 0.03W power rating, and 100mV maximum sliding noise.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pot-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the POT 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for POT 5 Click driver.

#### Standard key functions :

- `pot5_cfg_setup` Config Object Initialization function.
```c
void pot5_cfg_setup ( pot5_cfg_t *cfg );
```

- `pot5_init` Initialization function.
```c
err_t pot5_init ( pot5_t *ctx, pot5_cfg_t *cfg );
```

#### Example key functions :

- `pot5_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pot5_read_voltage ( pot5_t *ctx, float *voltage );
```

- `pot5_convert_voltage_to_percents` This function converts analog voltage to potentiometer position in percents.
```c
uint8_t pot5_convert_voltage_to_percents ( pot5_t *ctx, float voltage );
```

- `pot5_set_vref` This function sets the voltage reference for POT 5 Click driver.
```c
err_t pot5_set_vref ( pot5_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of POT 5 Click board by reading and displaying the potentiometer position.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot5_cfg_t pot5_cfg;  /**< Click config object. */

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
    pot5_cfg_setup( &pot5_cfg );
    POT5_MAP_MIKROBUS( pot5_cfg, MIKROBUS_1 );
    err_t init_flag = pot5_init( &pot5, &pot5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the potentiometer position in forms of voltage and percents once per second.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( POT5_OK == pot5_read_voltage ( &pot5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Potentiometer : %u %%\r\n\n", 
                    ( uint16_t ) pot5_convert_voltage_to_percents ( &pot5, voltage ) );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.POT5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
