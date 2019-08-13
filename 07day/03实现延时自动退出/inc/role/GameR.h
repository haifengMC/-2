#pragma once



#include <zinx.h>
#include "../protocol/GameMsgData.h"
#include "../AOI.h"



class GameR :
	public Irole, public AOIObj
{
	Iprotocol* p_gameP = NULL;
	mutable SyncPlyrIdData plyrData;
	mutable PlyrPosData plyrPosData;
public:
	GameR();
	virtual ~GameR();
	
	void bindProtocol(Iprotocol * &&p_gameP) { this->p_gameP = p_gameP; }

	const int& getPlyrId() const;
	const string& getUsrName() const;
	const PlyrPosData& getPlyrPos() const;
	Iprotocol* const& getProtocol() const;

	// 通过 Irole 继承
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;

	// 通过 AOIObj 继承
	virtual float & getX() const override;
	virtual float & getY() const override;
	virtual void setXY(const float & x, const float & y) override;
private:
	char convertBuf[64];

	char* const& convG2U(string& strBuf);
	char* const& convG2U(const char* const& c_str);
	int codeConvert(
		const char *const &from_charset, 
		const char *const &to_charset, 
		const char *const &inbuf, 
		const size_t &inlen, 
		char *const &outbuf, 
		const size_t &outlen);

};



