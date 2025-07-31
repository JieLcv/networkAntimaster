//
// Created by 赵伟 on 2024/12/25.
//

#include "Codec.h"

Codec::Codec(Message *msg)
{
    reload(msg);
}

Codec::Codec(std::string msg)
{
    reload(msg);
}

std::string Codec::encodeMsg()
{
    m_obj.SerializeToString(&m_msg);
    return m_msg;
}

std::shared_ptr<Message> Codec::decodeMsg()
{
    m_obj.ParseFromString(m_msg);
    Message *msg = new Message;
    msg->userName = m_obj.username();
    msg->roomName = m_obj.roomname();
    msg->data1 = m_obj.data1();
    msg->data2 = m_obj.data2();
    msg->data3 = m_obj.data2();
    msg->rescode = m_obj.rescode();
    msg->reqcode = m_obj.reqcode();

    std::shared_ptr<Message> ptr(msg, [this](Message *pt){
        delete pt;
        std::cout << "Message被析构了";
    });
    return ptr;
}

void Codec::reload(std::string msg)
{
    m_msg = msg;
}

void Codec::reload(Message *msg)
{
    m_obj.set_username(msg->userName);
    m_obj.set_roomname(msg->roomName);
    m_obj.set_data1(msg->data1);
    m_obj.set_data2(msg->data2);
    m_obj.set_data3(msg->data3);
    m_obj.set_rescode(msg->rescode);
    m_obj.set_reqcode(msg->reqcode);
}
