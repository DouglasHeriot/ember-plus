/*
    Copyright (C) 2012-2016 Lawo GmbH (http://www.lawo.com).
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "ElementVisitor.h"
#include "IntegerParameter.h"

namespace model
{
   IntegerParameter::IntegerParameter(int number, Element* parent, std::string identifier, NotificationSink* notificationSink, int minimum, int maximum)
      : Parameter(number, parent, identifier, notificationSink)
      , m_minimum(minimum)
      , m_maximum(maximum)
      , m_enumeration()
      , m_enumerationMap()
   {}

   void IntegerParameter::accept(ElementVisitor* visitor)
   {
      visitor->visit(this);
   }

   void IntegerParameter::onValueChanged()
   {
      auto notificationSink = this->notificationSink();

      if(notificationSink != nullptr)
         notificationSink->notifyParameterValueChanged(path(), value());
   }

   void IntegerParameter::setEnumeration(std::string const& enumeration)
   {
      m_enumeration = enumeration;
   }
}
