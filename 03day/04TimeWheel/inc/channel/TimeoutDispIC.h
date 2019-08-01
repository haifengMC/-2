#pragma once
#include "zinx.h"
class TimeoutDispIC :
	public Ichannel
{
public:
	TimeoutDispIC();
	virtual ~TimeoutDispIC();

	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
private:
	int fd;
};

