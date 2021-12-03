\mainpage Main Page

---
# Turbidity click

> Turbidity Click is an adapter Click board™, used to interface a compatible turbidity sensor with the host MCU. This board features one 1x3 2.5mm connector suitable for connecting a TSD-10 Turbidity Sensor via an additional 3-wire cable for Turbidity Click specially made for this purpose. It allows users to upgrade their projects with a sensor that senses the cloudiness or haziness of a fluid caused by large numbers of individual particles invisible to the naked eye. This sensor also measures temperature as well as turbidity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/turbidity_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/turbidity-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Turbidity Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Turbidity Click driver.

#### Standard key functions :

- `turbidity_cfg_setup` Config Object Initialization function.
```c
void turbidity_cfg_setup ( turbidity_cfg_t *cfg );
```

- `turbidity_init` Initialization function.
```c
err_t turbidity_init ( turbidity_t *ctx, turbidity_cfg_t *cfg );
```

- `turbidity_default_cfg` Click Default Configuration function.
```c
err_t turbidity_default_cfg ( turbidity_t *ctx );
```

#### Example key functions :

- `turbidity_get_ntu` Turbidity get NTU function.
```c
err_t turbidity_get_ntu ( turbidity_t *ctx, float *ntu );
```

- `turbidity_read_adc` Turbidity read ADC function.
```c
err_t turbidity_read_adc ( turbidity_t *ctx, uint16_t *adc_val );
```

- `turbidity_get_adc_voltage` Turbidity get voltage function.
```c
err_t turbidity_get_adc_voltage ( turbidity_t *ctx, float *voltage );
```

## Example Description

> This library contains API for the Turbidity Click driver.
> The demo application reads ADC value, ADC voltage and 
> Nephelometric Turbidity Units ( NTU ).

**The demo application is composed of two sections :**

### Application Init

> nitialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    turbidity_cfg_t turbidity_cfg;  /**< Click config object. */

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
    turbidity_cfg_setup( &turbidity_cfg );
    TURBIDITY_MAP_MIKROBUS( turbidity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == turbidity_init( &turbidity, &turbidity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TURBIDITY_ERROR == turbidity_default_cfg ( &turbidity ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This example demonstrates the use of the Turbidity Click board™.
> In this example, we monitor and display Nephelometric Turbidity Units ( NTU ).
> Results are being sent to the Usart Terminal, where you can track their changes.

```c

void application_task ( void ) 
{
    static float ntu;
    
    turbidity_get_ntu( &turbidity, &ntu );
    log_printf( &logger, "\tNTU : %.2f\r\n", ntu );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Turbidity

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
