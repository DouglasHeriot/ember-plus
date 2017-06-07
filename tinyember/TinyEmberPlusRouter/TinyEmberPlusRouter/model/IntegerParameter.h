/*
    Copyright (C) 2012-2016 Lawo GmbH (http://www.lawo.com).
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef __TINYEMBERROUTER_MODEL_INTEGERPARAMETER_H
#define __TINYEMBERROUTER_MODEL_INTEGERPARAMETER_H

#include "Parameter.h"
#include <algorithm>
#include <string>
#include <map>

namespace model
{
   /**
     * Simple integer parameter.
     */
   class IntegerParameter : public Parameter<int>
   {
   public:
      /**
        * Creates a new instance of IntegerParameter.
        * @param number The number used for Ember+ automation.
        * @param parent Pointer to the parent of the new object - the ctor
        *     will enter the new object in the parent's collection of children.
        * @param identifier The identifier used for Ember+ automation.
        * @param notificationSink Pointer to the object receiving value change
        *     notifications.
        * @param minimum The parameter's minimum value.
        * @param maximum The parameter's maximum value.
        */
      IntegerParameter(int number, Element* parent, std::string identifier, NotificationSink* notificationSink, int minimum, int maximum);

      /**
        * Returns the parameter's minimum value.
        * @Return The parameter's minimum value.
        */
      inline int minimum() const { return m_minimum; }

      /**
        * Returns the parameter's maximum value.
        * @Return The parameter's maximum value.
        */
      inline int maximum() const { return m_maximum; }

      /**
        * Returns the enumeration string.
        * @Return The enumeration string.
        */
      inline const std::string &enumeration() const { return m_enumeration; }

      /**
        * Returns the enumeration map.
        * @Return The enumeration map.
        */
      inline const std::map<std::string, int> &enumerationMap() const { return m_enumerationMap; }

      /**
        * Overridden to call the appropriate visit() overload.
        */
      void accept(ElementVisitor* visitor);

      /**
        * Sets the enumeration property by concatenating the provided strings. The strings 
        * are separated by a '\n' character.
        * @param first First element to use in the enumeration.
        * @param last Points the the first element not being used.
        */
      template<typename InputIterator>
      void setEnumeration(InputIterator first, InputIterator last);

      /**
        * Sets the enumeration property.
        * @param enumeration The completed enumeration string containing all entries separated
        *      by the '\n' character.
        */
      void setEnumeration(std::string const& enumeration);

      /**
        * Sets the enumeration map. The map is used if a provider doesn't use consecutive 
        * indices for an enumerated parameter. If a map is set, the default enumeration property
        * must be ignored.
        * @param first The first enumeration entry containing the name-value pair.
        * @param last The end of the enumeration entry buffer.
        * @note The InputIterator must contain a pair of type std::pair<std::string, int>, where
        *      the string is the enumeration name and the int the enumeration value to send
        *      to the provider.
        */
      template<typename InputIterator>
      void setEnumerationMap(InputIterator first, InputIterator last);

   protected:
      /**
        * Overridden to call the appropriate notifyParameterValueChanged() overload
        * on the notificationSink.
        */
      virtual void onValueChanged();

   private:
      int m_minimum;
      int m_maximum;
      std::string m_enumeration;
      std::map<std::string, int> m_enumerationMap;
   };

   // Copied from GlowParameterBase.hpp
   template<typename InputIterator>
   inline void IntegerParameter::setEnumeration(InputIterator first, InputIterator last)
   {
      std::ostringstream stream;

      for(/** Nothing */; first != last; /** Nothing */)
      {
            stream << *first++;

            if (first != last)
               stream << "\n";
      }

      setEnumeration(stream.str());
   }

   template<typename InputIterator>
   inline void IntegerParameter::setEnumerationMap(InputIterator first, InputIterator last)
   {
      m_enumerationMap.clear();
      std::copy(first, last, m_enumerationMap.begin());
   }


}

#endif//__TINYEMBERROUTER_MODEL_INTEGERPARAMETER_H
