/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

/**
 * @file
 * Include this config file to get access to the USB peripheral.
 */

// ST driver includes

#include "usblib/device/core/inc/usbd_def.h"
#include "usblib/device/core/inc/usbd_core.h"

// usb depends on ...

#include "config/event.h"
#include "config/timing.h"
#include "config/smartptr.h"


#if defined(STM32PLUS_F4)

  #include "usb/phy/UsbInternalFsPhy.h"
  #include "usb/core/UsbCore.h"

  #include "usb/device/UsbDeviceDescriptor.h"
  #include "usb/device/UsbLanguageDescriptor.h"
  #include "usb/device/UsbEndpointType.h"

  #include "usb/device/events/UsbDeviceEventDescriptor.h"
  #include "usb/device/events/UsbDeviceSdkNotifyEvent.h"
  #include "usb/device/events/UsbDeviceSdkEndpointEvent.h"
  #include "usb/device/events/UsbDeviceSdkOpenEndpointEvent.h"
  #include "usb/device/events/UsbDeviceSdkIsStalledEndpointEvent.h"
  #include "usb/device/events/UsbDeviceSdkDataEndpointEvent.h"
  #include "usb/device/events/UsbDeviceSdkGetLastTransferredSizeEndpointEvent.h"
  #include "usb/device/events/UsbDeviceGetDeviceDescriptorEvent.h"
  #include "usb/device/events/UsbDeviceGetLanguageDescriptorEvent.h"

  #include "usb/device/UsbDeviceEventSource.h"
  #include "usb/device/UsbDevice.h"
  #include "usb/device/UsbHidDevice.h"

  #include "usb/device/features/UsbDeviceFeatureBase.h"
  #include "usb/device/features/UsbStringFeatureBase.h"
  #include "usb/device/features/UsbManufacturerFeature.h"
  #include "usb/device/features/UsbProductFeature.h"
  #include "usb/device/features/UsbSerialNumberFeature.h"

#endif

