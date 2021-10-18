\mainpage Main Page

---
# I2C Extend click

> I2C Extend Click is a compact add-on board for applications that require extending the I2C communication bus over a long distance. This board features the LTC4331 - an I2C slave device extender over a rugged differential link, from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cextend_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-extend-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the I2CExtend Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2CExtend Click driver.

#### Standard key functions :

- `i2cextend_cfg_setup` Config Object Initialization function.
```c
void i2cextend_cfg_setup ( i2cextend_cfg_t *cfg );
```

- `i2cextend_init` Initialization function.
```c
err_t i2cextend_init ( i2cextend_t *ctx, i2cextend_cfg_t *cfg );
```

#### Example key functions :

- `i2cextend_rmt_multi_read` Generic multi read data in Remote Mode function.
```c
void i2cextend_rmt_multi_read ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );
```

- `i2cextend_set_config` Set the configuration function.
```c
void i2cextend_set_config ( i2cextend_t *ctx, uint8_t intr_mode, uint8_t ctrl_sel );
```

- `i2cextend_set_out_slave_address` Set out slave address function.
```c
void i2cextend_set_out_slave_address ( i2cextend_t *ctx, uint8_t out_slave_address );
```

## Example Description

> This is an example which demonstrates the use of I2C Extend Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C,  check communication with device 6DOF IMU 11 Click  connected to the I2C Extend Click ( Remote Mode ), set default configuration and start measurement.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cextend_cfg_t i2cextend_cfg;  /**< Click config object. */

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
    i2cextend_cfg_setup( &i2cextend_cfg );
    I2CEXTEND_MAP_MIKROBUS( i2cextend_cfg, MIKROBUS_1 );
    err_t init_flag = i2cextend_init( &i2cextend, &i2cextend_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( i2cbuffer2_rmt_read( &i2cextend, C6DOFIMU11_I2C_SLAVE_ADDRESS_GND, C6DOFIMU11_REG_WHO_AM_I ) == C6DOFIMU11_WHO_AM_I_WIA_ID ) {
        log_printf( &logger, "        SUCCESS         \r\n" );
        log_printf( &logger, "------------------------\r\n" );
    } else {
        log_printf( &logger, "         ERROR          \r\n" );
        log_printf( &logger, "    Reset the device    \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        for ( ; ; );
    }
    i2cbuffer2_rmt_write( &i2cextend, C6DOFIMU11_I2C_SLAVE_ADDRESS_GND, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE |
                                                                                  C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE |
                                                                                  C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE );

    i2cbuffer2_rmt_write ( &i2cextend, C6DOFIMU11_I2C_SLAVE_ADDRESS_GND, C6DOFIMU11_REG_INC3, C6DOFIMU11_INC3_IEL2_FIFO_TRIG | 
                                                                                  C6DOFIMU11_INC3_IEL1_FIFO_TRIG );

    i2cbuffer2_rmt_write ( &i2cextend, C6DOFIMU11_I2C_SLAVE_ADDRESS_GND, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_GSEL_8G | 
                                                                                   C6DOFIMU11_CNTL2_RES_MAX2 | 
                                                                                   C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE | 
                                                                                   C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}

```

### Application Task

> In this example, we read Accel and Mag axis of the connected  6DOF IMU 11 Click boards to the I2C Extend Click ( Remote Mode ) which is connected by a LAN cable to I2C Extend Click ( Local Mode ). Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes for every 2 sec.

```c

void application_task ( void ) {
    log_printf( &logger, "\t   Accel   \t|\t    Mag    \r\n" );
    log_printf( &logger, "------------------------------------------------\r\n" );
    
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_ACCEL_XOUT_L );
    log_printf( &logger, "\t Accel X: %d\t|", axis );
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_MAG_XOUT_L );
    log_printf( &logger, "\t Mag X: %d\r\n", axis );
    
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_ACCEL_YOUT_L );
    log_printf( &logger, "\t Accel Y: %d\t|", axis );
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_MAG_YOUT_L );
    log_printf( &logger, "\t Mag Y: %d\r\n", axis );
    
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_ACCEL_ZOUT_L );
    log_printf( &logger, "\t Accel Z: %d\t|", axis );
    i2cbuffer2_6dofimu11_get_axis( &i2cextend, C6DOFIMU11_REG_MAG_ZOUT_L );
    log_printf( &logger, "\t Mag Z: %d\r\n", axis );
    
    log_printf( &logger, "------------------------------------------------\r\n" );
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CExtend

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
