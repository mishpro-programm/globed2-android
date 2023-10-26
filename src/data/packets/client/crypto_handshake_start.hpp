#pragma once
#include <data/packets/packet.hpp>
#include <data/connection.hpp>

class CryptoHandshakeStartPacket : public Packet {
    GLOBED_PACKET(10001, false)

    void encode(ByteBuffer& buf) override {
        buf.writeValue(data);
    }

    GLOBED_DECODE_UNIMPL

    CryptoHandshakeStartPacket(HandshakeData _data) : data(_data) {}
    CryptoHandshakeStartPacket() {}

    static CryptoHandshakeStartPacket* create(HandshakeData data) {
        return new CryptoHandshakeStartPacket(data);
    }

    HandshakeData data;
};