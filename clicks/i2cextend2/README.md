\mainpage Main Page

---
# I2C Extend 2 click

> I2C Extend 2 Click is a compact add-on board suitable for I2C communication bus extension. This board features the PCA9615, a 2-channel multipoint differential I2C bus buffer with hot-swap logic from NXP Semiconductors. The PCA9615 converts the two default I2C signals into four differential signals, two for SCL and two for SDA.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cextend2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-extend-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the I2CExtend2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2CExtend2 Click driver.

#### Standard key functions :

- `i2cextend2_cfg_setup` Config Object Initialization function.
```c
void i2cextend2_cfg_setup ( i2cextend2_cfg_t *cfg );
```

- `i2cextend2_init` Initialization function.
```c
err_t i2cextend2_init ( i2cextend2_t *ctx, i2cextend2_cfg_t *cfg );
```

#### Example key functions :

- `i2cextend2_rmt_write` Generic write data in Remote Mode function.
```c
void i2cextend2_rmt_write ( i2cextend2_t *ctx, uint8_t reg, uint8_t tx_data );
```

- `i2cextend2_rmt_read` Generic read data in Remote Mode function.
```c
uint8_t i2cextend2_rmt_read ( i2cextend2_t *ctx, uint8_t reg );
```

- `i2cextend2_enable` Enable extend function.
```c
void i2cextend2_enable ( i2cextend2_t *ctx, uint8_t en_extend );
```

## Example Description

> This is an example which demonstrates the use of I2C Extend 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C,  check communication with device 6DOF IMU 11 Click  connected to the I2C Extend 2 Click ( Remote Mode ), set default configuration and start measurement.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cextend2_cfg_t i2cextend2_cfg;  /**< Click config object. */

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
    i2cextend2_cfg_setup( &i2cextend2_cfg );
    I2CEXTEND2_MAP_MIKROBUS( i2cextend2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cextend2_init( &i2cextend2, &i2cextend2_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    i2cextend2_enable( &i2cextend2, I2CEXTEND2_EXTEND_ENABLE );

    if ( C6DOFIMU11_WHO_AM_I_WIA_ID == i2cextend2_rmt_read( &i2cextend2, C6DOFIMU11_REG_WHO_AM_I ) ) 
    {
        log_printf( &logger, "        SUCCESS         \r\n" );
        log_printf( &logger, "------------------------\r\n" );
    } 
    else 
    {
        log_printf( &logger, "         ERROR          \r\n" );
        log_printf( &logger, "    Reset the device    \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        for ( ; ; );
    }
    i2cextend2_rmt_write ( &i2cextend2, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE |
                                                              C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE |
                                                              C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE );

    i2cextend2_rmt_write ( &i2cextend2, C6DOFIMU11_REG_INC3, C6DOFIMU11_INC3_IEL2_FIFO_TRIG |
                                                             C6DOFIMU11_INC3_IEL1_FIFO_TRIG );

    i2cextend2_rmt_write ( &i2cextend2, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_GSEL_8G |
                                                              C6DOFIMU11_CNTL2_RES_MAX2 |
                                                              C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE |
                                                              C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}

```

### Application Task

> In this example, we read Accel and Mag axis of the connected  6DOF IMU 11 Click boards to the I2C Extend 2 Click ( Remote Mode ) which is connected by a LAN cable to I2C Extend 2 Click ( Local Mode ). Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes for every 2 sec.

```c

void application_task ( void ) 
{
    log_printf( &logger, "\t   Accel   \t|\t    Mag    \r\n" );
    log_printf( &logger, "------------------------------------------------\r\n" );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_XOUT_L );
    log_printf( &logger, "\t Accel X: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_XOUT_L );
    log_printf( &logger, "\t Mag X: %d\r\n", axis );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_YOUT_L );
    log_printf( &logger, "\t Accel Y: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_YOUT_L );
    log_printf( &logger, "\t Mag Y: %d\r\n", axis );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_ZOUT_L );
    log_printf( &logger, "\t Accel Z: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_ZOUT_L );
    log_printf( &logger, "\t Mag Z: %d\r\n", axis );

    log_printf( &logger, "------------------------------------------------\r\n" );
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CExtend2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
