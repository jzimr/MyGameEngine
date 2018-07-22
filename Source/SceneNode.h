#pragma once
#include "stdafx.h"

class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
							SceneNode();

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);		//	Returns the child after detaching it

	void					update(float dt);

private:
	virtual void			updateCurrent(float dt);
	virtual void			updateChildren(float dt);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;
};
