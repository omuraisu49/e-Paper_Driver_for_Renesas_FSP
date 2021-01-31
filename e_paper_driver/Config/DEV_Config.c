/*****************************************************************************
 * File         :   DEV_Config.c
 * Author       :   OMURAISU
 * Date         :   2021-01-30
 * Function     :   Hardware underlying interface
 * Info         :   Support Renesas Flexible Software Package (FSP)
 *                  This software is based on the following materials.
 *                  https://github.com/waveshare/e-Paper/tree/master/STM32
 *
 *                  Please refer to README.md for more detail/Usage info.
 *
 * The author(OMURAISU) does not take any responsibility caused by this material.
 * If you incorporate this material into your system, please be very careful.
 ****************************************************************************/
/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# ******************************************************************************
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"
#include "hal_data.h"

bsp_io_port_pin_t EPD_RST_PIN;
bsp_io_port_pin_t EPD_DC_PIN;
bsp_io_port_pin_t EPD_CS_PIN;
bsp_io_port_pin_t EPD_BUSY_PIN;

volatile bool DEV_spi_transfer_complete_flag = false;
spi_instance_t * DEV_spi_instance;

void DEV_SPI_WriteByte(UBYTE value)
{
    R_SPI_Write(DEV_spi_instance->p_ctrl, &value, 1, SPI_BIT_WIDTH_8_BITS);
    while(DEV_spi_transfer_complete_flag == false){}
    DEV_spi_transfer_complete_flag = false;
}

int DEV_Module_Init(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_Digital_Write(EPD_RST_PIN, 1);
		return 0;
}

void DEV_Module_Exit(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    //close 5V
    DEV_Digital_Write(EPD_RST_PIN, 0);
}

void DEV_Config_Set(spi_instance_t * _spi_instance, bsp_io_port_pin_t _rst_pin, bsp_io_port_pin_t _cs_pin, bsp_io_port_pin_t _dc_pin, bsp_io_port_pin_t _busy_pin)
{
    DEV_spi_instance = (spi_instance_t *)_spi_instance;
    EPD_RST_PIN = _rst_pin;
    EPD_CS_PIN = _cs_pin;
    EPD_DC_PIN = _dc_pin;
    EPD_BUSY_PIN = _busy_pin;

}

void DEV_Digital_Write(bsp_io_port_pin_t _pin, bsp_io_level_t _value)
{
    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(_pin, _value);
    R_BSP_PinAccessDisable();
}

bsp_io_level_t DEV_Digital_Read(bsp_io_port_pin_t _pin)
{
    bsp_io_level_t _pin_read_value;
    R_IOPORT_PinRead(&g_ioport_ctrl, _pin, &_pin_read_value);
    return _pin_read_value;
}

/* Callback function */
void spi_callback(spi_callback_args_t *p_args)
{
    if(p_args->event == SPI_EVENT_TRANSFER_COMPLETE)
    {
        DEV_spi_transfer_complete_flag = true;
    }
}
