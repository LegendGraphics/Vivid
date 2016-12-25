#include "common/Component.h"

 namespace te
 {
	 Component::Component()
		 :_enabled(true)
	 {

	 }

	 Component::Component(const Component& component, const CopyOperator& copyop)
		 :_enabled(component._enabled)
	 {
	 }

	 Component::~Component() {}

	 void Component::init()
	 {
	 }

	 void Component::update()
	 {

	 }

	 void Component::setEnabled(bool enabled)
	 {
		 _enabled = enabled;
	 }

	 void Component::setName(const std::string& name)
	 {
		 _name = name;
	 }
 }







