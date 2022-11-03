/**
  **************************************************************************
  * @file     msc_diskio.h
  * @version  v2.0.7
  * @date     2022-08-16
  * @brief    usb mass storage disk interface header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MSC_DISKIO_H
#define __MSC_DISKIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "usb_conf.h"
#include "usb_std.h"

/** @addtogroup AT32F415_periph_examples
  * @{
  */

/** @addtogroup 415_USB_device_virtual_msc_iap
  * @{
  */
#define INTERNAL_FLASH_LUN               0
#define SPI_FLASH_LUN                    1
#define SD_LUN                           2

#define USB_FLASH_ADDR_OFFSET  0x08004000

uint8_t *get_inquiry(uint8_t lun);
usb_sts_type msc_disk_read(uint8_t lun, uint32_t addr, uint8_t *read_buf, uint32_t len);
usb_sts_type msc_disk_write(uint8_t lun, uint32_t addr, uint8_t *buf, uint32_t len);
usb_sts_type msc_disk_capacity(uint8_t lun, uint32_t *blk_nbr, uint32_t *blk_size);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif


