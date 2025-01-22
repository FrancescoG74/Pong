#ifndef COMPONENT_H
#define COMPONENT_H

class actor;

class component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	component(actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~component();
	// Update this component by delta time
	virtual void update(float deltaTime);

	int getUpdateOrder() const { return mUpdateOrder; }

protected:
	// Owning actor
	actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};

#endif
