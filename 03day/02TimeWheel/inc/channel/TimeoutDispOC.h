#pragma once
#include "zinx.h"
class TimeoutDispOC :
	public Ichannel
{
public:
	TimeoutDispOC();
	virtual ~TimeoutDispOC();

	int getIFd();

	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
private:
	int pipefd[2] = { 0 };

};

