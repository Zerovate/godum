// #include "steam_packet_peer.h"

// std::unordered_map<CSteamID, SteamPacketPeer*> SteamPacketPeer::active_peers;

// Error SteamPacketPeer::send_packet(int channel, const uint8_t *data, int len, bool reliable) {
//     if (state != STATE_CONNECTED) 
//         return ERR_CONNECTION_ERROR;

//     EP2PSend send_type = reliable ? 
//         k_EP2PSendReliable : k_EP2PSendUnreliableNoDelay;

//     if (!SteamNetworking()->SendP2PPacket(
//         steam_id, data, len, send_type, channel)) {
//         packets_lost++;
//         return ERR_UNAVAILABLE;
//     }

//     packets_sent++;
//     return OK;
// }

// Error SteamPacketPeer::get_packet(const uint8_t ​**​r_buffer, int &r_buffer_size) {
//     std::lock_guard<std::mutex> lock(queue_mutex);
    
//     if (packet_queue.empty())
//         return ERR_UNAVAILABLE;

//     auto &packet = packet_queue.front();
//     *r_buffer = packet.data();
//     r_buffer_size = packet.size();
//     packet_queue.pop();
//     return OK;
// }

// Error SteamPacketPeer::put_packet(const uint8_t *p_buffer, int p_buffer_size) {
//     // Steamworks P2P通信是双向的，发送需要指定目标
//     // 这里重定向到send_packet方法
//     return send_packet(0, p_buffer, p_buffer_size, 
//         get_transfer_mode() == TRANSFER_MODE_RELIABLE);
// }

// void SteamPacketPeer::peer_disconnect() {
//     SteamNetworking()->CloseP2PSessionWithUser(steam_id);
//     state = STATE_DISCONNECTED;
// }

// SteamPacketPeer::PeerState SteamPacketPeer::get_state() const {
//     // 检查实际连接状态
//     P2PSessionState_t session_state;
//     if (SteamNetworking()->GetP2PSessionState(steam_id, &session_state)) {
//         if (session_state.m_bConnectionActive)
//             return STATE_CONNECTED;
//         if (session_state.m_bConnecting)
//             return STATE_CONNECTING;
//     }
//     return STATE_DISCONNECTED;
// }

// // Steam回调处理
// void SteamPacketPeer::OnP2PSessionRequest(CSteamID remote_id) {
//     auto it = active_peers.find(remote_id);
//     if (it != active_peers.end()) {
//         SteamNetworking()->AcceptP2PSessionWithUser(remote_id);
//         it->second->state = STATE_CONNECTED;
//     }
// }

// void SteamPacketPeer::OnP2PSessionConnectFail(CSteamID remote_id, P2PSessionError error) {
//     auto it = active_peers.find(remote_id);
//     if (it != active_peers.end()) {
//         it->second->state = STATE_ERROR;
//         it->second->packets_lost++;
//     }
// }

// // 数据接收线程
// void SteamPacketPeer::poll_network() {
//     while (true) {
//         uint32 msg_size;
//         if (!SteamNetworking()->IsP2PPacketAvailable(&msg_size, 0)) 
//             break;

//         std::vector<uint8_t> buffer(msg_size);
//         CSteamID remote_id;
//         uint32 actual_size;
//         int channel;

//         if (SteamNetworking()->ReadP2PPacket(
//             buffer.data(), msg_size, &actual_size, &remote_id, &channel)) {
            
//             if (auto it = active_peers.find(remote_id); it != active_peers.end()) {
//                 std::lock_guard<std::mutex> lock(it->second->queue_mutex);
//                 it->second->packet_queue.push(std::move(buffer));
//             }
//         }
//     }
// }