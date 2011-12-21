#pragma once

#include "cPacket.h"
#include "PacketID.h"

//Sure it�s not Creative Inventory?

class cPacket_CreateInventoryAction : public cPacket
{
public:
	cPacket_CreateInventoryAction()
		: m_Slot( 0 )
		, m_ItemID( 0 )
		, m_Quantity( 0 )
		, m_Damage( 0 )
	{ m_PacketID = E_CREATE_INVENTORY_ACTION; m_Quantity = 1; }
	cPacket_CreateInventoryAction( const cPacket_CreateInventoryAction & a_Copy );
	virtual cPacket* Clone() const { return new cPacket_CreateInventoryAction(*this); }

	bool Parse(cSocket & a_Socket);
	bool Send(cSocket & a_Socket);

	short m_Slot; // 0 = hold 1-4 = armor
	short m_ItemID;
	char m_Quantity; //Byte not short ;)
	short m_Damage;

	static const unsigned int c_Size = 1 + 2;
};
