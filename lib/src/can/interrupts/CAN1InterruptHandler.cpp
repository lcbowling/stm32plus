/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if !defined(STM32PLUS_F0)

#include "config/can.h"


using namespace stm32plus;


// static initialisers for the hack that forces the IRQ handlers to be linked

template<> CANInterruptFeatureEnabler<1>::FPTR CANInterruptFeatureEnabler<1>::_forceLinkageRX0=nullptr;
template<> CANInterruptFeatureEnabler<1>::FPTR CANInterruptFeatureEnabler<1>::_forceLinkageTX=nullptr;

#if defined(USE_CAN1_INTERRUPT)

extern "C" {

#if defined(STM32PLUS_F1) and !defined(STM32PLUS_F1_CL)
	void __attribute__ ((interrupt("IRQ"))) USB_LP_CAN1_RX0_IRQHandler(void)
#else
	void __attribute__ ((interrupt("IRQ"))) CAN1_RX0_IRQHandler(void)
#endif
    {
      CANInterruptFeature<1>::_canInstance->CANInterruptEventSender.raiseEvent(CANEventType::EVENT_RECEIVE_RX0);
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }

#if defined(STM32PLUS_F1) and !defined(STM32PLUS_F1_CL)
	void __attribute__ ((interrupt("IRQ"))) USB_HP_CAN1_TX_IRQHandler(void)
#else
	void __attribute__ ((interrupt("IRQ"))) CAN1_TX_IRQHandler(void)
#endif
    {
      CANInterruptFeature<1>::_canInstance->CANInterruptEventSender.raiseEvent(CANEventType::EVENT_TRANSMIT_TME);
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }

}

#endif

#endif // extern "C"

