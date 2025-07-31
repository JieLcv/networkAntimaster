//
// Created by 赵伟 on 2024/12/16.
//

#include "MyTest.h"
#include "Person.pb.h"
#include "Address.pb.h"

void MyTest::test()
{
    //序列化
    Erbing::Person p;
    p.set_id(10);
    p.set_age(32);
    p.set_sex("man");
    p.add_name();
    p.set_name(0, "路飞");
    p.add_name("艾斯");
    p.add_name("萨博");
    p.mutable_addr()->set_addr("北京市长安区天安门");
    p.mutable_addr()->set_num(1001);
    p.set_color(Erbing::Color::Blue);
    //序列化对象，最终的到一个字符串
    std::string output;
    //序列化为二进制
    p.SerializeToString(&output);
    std::cout <<"序列化后：" << output << std::endl;
    //反序列化数据
    Erbing::Person pp;
    pp.ParseFromString(output);
    std::cout <<"反序列化后：" << pp.id() << "  " << pp.sex() << " " << "  " << pp.age() << std::endl;
    std::cout << pp.addr().addr() << ", " << pp.addr().num() << std::endl;
    int size = pp.name_size();
    for(int i = 0; i < size; i++)
    {
        std::cout << p.name(i) << std::endl;
    }
    std::cout << pp.color() << std::endl;
}
