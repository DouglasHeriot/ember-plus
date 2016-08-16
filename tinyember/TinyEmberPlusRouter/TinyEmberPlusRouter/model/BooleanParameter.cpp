/*
    Copyright (C) 2012-2016 Lawo GmbH (http://www.lawo.com).
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "ElementVisitor.h"
#include "BooleanParameter.h"

namespace model
{
   BooleanParameter::BooleanParameter(int number, Element* parent, std::string identifier, NotificationSink* notificationSink)
      : Parameter(number, parent, identifier, notificationSink)
   {}

   void BooleanParameter::accept(ElementVisitor* visitor)
   {
      visitor->visit(this);
   }

   void BooleanParameter::onValueChanged()
   {
      auto notificationSink = this->notificationSink();

      if(notificationSink != nullptr)
         notificationSink->notifyParameterValueChanged(path(), value());
   }
}
