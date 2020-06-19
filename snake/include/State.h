#ifndef STATE_H
#define STATE_H


class State
{
public:
	State();
	~State();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Handle();
	virtual void Exit();
};

#endif // !STATE_H

