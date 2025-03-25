#pragma once

class ModelAnimationInstancingScene : public Scene
{
public:
	ModelAnimationInstancingScene();
	~ModelAnimationInstancingScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	ModelAnimatorInstancing* modelInstancing;

	int instanceIndex = 0;
	int clip = 0;
};
