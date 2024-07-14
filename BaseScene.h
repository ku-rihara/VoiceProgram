#pragma once


class BaseScene{
protected:

static bool isChange_;
static bool isIncrement_;
static bool isDecrement_;
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void  Init() = 0;
	virtual void  Update() = 0;
	virtual void  Draw() = 0;

	static  bool GetIsChange() { return isChange_; }
	static 	void SetIsChange( bool is) { isChange_ = is; }

	static  bool GetIsIncrement() { return isIncrement_; }
	static 	void SetIsIncrement(bool is) { isIncrement_ = is; }

	static  bool GetIsDecrement() { return isDecrement_; }
	static 	void SetIsDecrement(bool is) { isDecrement_ = is; }
};

