#pragma once
#include <steam/steamnetworkingtypes.h>
#ifdef GODUM_MODULE
#include "core/io/packet_peer.h"
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/packet_peer.hpp>
using namespace godot;
#endif

class SteamPacketPeer : public PacketPeer {
	GDCLASS(SteamPacketPeer, PacketPeer);

private:
	HSteamNetConnection connection = k_HSteamNetConnection_Invalid;
	List<uint8_t *> packet_queue;
	uint8_t *last_packet = nullptr;
	int last_packet_size = 0;

	static void _bind_methods();
	Error _send(PackedByteArray p_packet, int p_flags);

protected:
	friend class SteamNetworking;
	void _queue_packet(const uint8_t *p_data, uint32_t p_size);

public:
	enum {
		FLAG_RELIABLE = k_nSteamNetworkingSend_Reliable,
		FLAG_UNRELIABLE = k_nSteamNetworkingSend_Unreliable,
		FLAG_ALLOWED = k_nSteamNetworkingSend_Reliable | k_nSteamNetworkingSend_Unreliable
	};

	enum PeerState {
		STATE_DISCONNECTED,
		STATE_CONNECTING,
		STATE_CONNECTED,
		STATE_CLOSING
	};

	int get_max_packet_size() const override { return 512 * 1024; } // Steam 默认消息大小限制
	int get_available_packet_count() const override { return packet_queue.size(); }
	Error get_packet(const uint8_t **r_buffer, int &r_buffer_size) override;
	Error put_packet(const uint8_t *p_buffer, int p_buffer_size) override;

	void disconnect(int reason = 0);
	PeerState get_state() const;

	CSteamID get_steam_id() const;
	int get_ping() const;

	SteamPacketPeer(HSteamNetConnection p_connection);
	~SteamPacketPeer();
};

VARIANT_ENUM_CAST(SteamPacketPeer::PeerState);