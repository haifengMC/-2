#pragma once
#include "zinx.h"

class StdoutC :
	public Ichannel
{
public:
	StdoutC();
	virtual ~StdoutC();

	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

