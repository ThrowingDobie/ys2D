#include <iostream>


#pragma pack(1)

namespace PACKET
{
	const int HEADER_SIZE = 8;
	enum eType{
		TYPE_START = 0,
		CG_REQ_CHAT = 1,
		CG_REQ_LOGIN = 2,
		CG_ACK_MOVE = 3 // ĳ���� �̵� Broadcasting 
	};

	struct PACKET_BASE
	{
		int size;		
		int type;
	};

	struct CG_CHAT
	{
		PACKET_BASE base;
		char chatData[256];		
	};

	struct CG_MOVE
	{
		PACKET_BASE base;
		int uID; // ���� ���� ����ũ ID
		int subType;
		float startX;
		float startY;
		//float StartZ;
		float dirX;
		float dirY;
		//float dirX;
		float speed;
	};

}
#pragma pack()