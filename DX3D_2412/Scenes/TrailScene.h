#pragma once

class TrailScene : public Scene
{
public:
	TrailScene();
	~TrailScene();
		
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Transform* start;
	Transform* end;
	Sphere* sphere;

	Trail* trail;
};