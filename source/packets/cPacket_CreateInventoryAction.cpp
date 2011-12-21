#include "cPacket_CreateInventoryAction.h"
#include "cPacket_ItemData.h"

cPacket_CreateInventoryAction::cPacket_CreateInventoryAction( const cPacket_CreateInventoryAction & a_Copy )
{
	m_PacketID = E_CREATE_INVENTORY_ACTION;
	m_Slot	 = a_Copy.m_Slot;
	m_ItemID = a_Copy.m_ItemID;
	m_Quantity = 0;
	m_Damage = 0;
}

bool cPacket_CreateInventoryAction::Parse(cSocket & a_Socket)
{
	m_Socket = a_Socket;
	if( !ReadShort	( m_Slot ) ) return false;
	/*
	if( !ReadShort	( m_ItemID ) ) return false;
	if( !ReadShort	( m_Quantity ) ) return false;
	if( !ReadShort	( m_Damage ) ) return false;
	*/

	cPacket_ItemData Item;

	Item.Parse(m_Socket);

	m_ItemID = Item.m_ItemID;
	m_Quantity = Item.m_ItemCount;
	m_Damage = Item.m_ItemUses;


	return true;
}

bool cPacket_CreateInventoryAction::Send(cSocket & a_Socket)
{
	//LOG("InventoryChange:");
	unsigned int TotalSize = c_Size;

	cPacket_ItemData Item;

	TotalSize += Item.GetSize(m_ItemID);

	char* Message = new char[TotalSize];

	if( m_ItemID <= 0 ) m_ItemID = -1; // Fix, to make sure no invalid values are sent.
                        // WARNING: HERE ITS -1, BUT IN NAMED ENTITY SPAWN PACKET ITS 0 !!
	//LOG("cPacket_CreateInventoryAction: Sending Creative item ID: %i", m_ItemID );

	unsigned int i = 0;
	AppendByte	 ( (char)m_PacketID,	Message, i );
	AppendShort  ( m_Slot,		Message, i );

	Item.AppendItem(Message, i, m_ItemID, m_Quantity, m_Damage);

	bool RetVal = !cSocket::IsSocketError( SendData( a_Socket, Message, TotalSize, 0 ) );
	delete [] Message;
	return RetVal;
}
