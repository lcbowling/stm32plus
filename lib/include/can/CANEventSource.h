/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {

  /**
   * CAN event types
   */

  enum class CANEventType : uint8_t {
	  EVENT_RECEIVE_RX0,
	  EVENT_RECEIVE_RX1
  };


  /**
   * The signature for CAN events: void myHandler(CANEventType set);
   */

  DECLARE_EVENT_SIGNATURE(CANInterrupt,void(CANEventType));


  /**
   * Base structure that holds just the event subscriber/publisher for CAN
   */

  struct CANEventSource {
    DECLARE_EVENT_SOURCE(CANInterrupt);
  };
}
