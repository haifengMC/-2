#pragma once
#include <zinx.h>
#include <map>

class CmdPrsP :
	public Iprotocol
{
public:
	virtual ~CmdPrsP();
	static CmdPrsP& getInstance();
	static void addRole(const std::string name, Irole* r);
private:
	static CmdPrsP s_cmdPrs;
	std::map<std::string, Irole*> roleMap;
	CmdPrsP();


	// Í¨¹ý Iprotocol ¼Ì³Ð
	virtual UserData * raw2request(std::string _szInput) override;

	virtual std::string * response2raw(UserData & _oUserData) override;

	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;

	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;

};

