/********************************************************************
/ NOTE: This is based on class lecture Set6, slide 17

/ This class is a virtual base class for all Observer classes
/ Objects of this type must implement their own update function in order
/ to obtain crucial information on the objects they observe.
*********************************************************************/


#pragma once
class Observer
{
public:
	virtual ~Observer();
	virtual void update() = 0;
protected:
	// Make the constructor protected so that only derived classes can instantiate this
	Observer();
};

