#include <iostream>


#pragma pack(1)

namespace PACKET
{
	const int HEADER_SIZE = 8;
	enum eType{
		TYPE_START = 0,
		CG_REQ_CHAT = 1,
		CG_REQ_LOGIN = 2,
		CG_ACK_MOVE = 3 // 캐릭터 이동 Broadcasting 
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
		int uID; // 서버 기준 유니크 ID
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