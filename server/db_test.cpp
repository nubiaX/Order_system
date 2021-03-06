#include "db.hpp"
#include <iostream>
using namespace order_system;
using namespace Json;

void TestDishTable() {
 bool ret = false;
 // 更友好的格式化显示 Json
 Json::StyledWriter writer;
 MYSQL* mysql = mysqlinit();
 Json::Value dish;
 dish["name"] = "红烧肉";
 dish["price"] = 2300;
 std::cout << "==============测试插入=====================" << std::endl;
 dish_table dish_table(mysql);
 ret = dish_table.Insert(dish);
 std::cout << "Insert: " << ret << std::endl;
 std::cout << "==============测试查找=====================" << std::endl;
 Json::Value dishes;
 ret = dish_table.SelectAll(&dishes);
 std::cout << "SelectAll: " << ret << std::endl
 << writer.write(dishes) << std::endl;
 std::cout << "==============测试更新=====================" << std::endl;
 dish["dish_id"] = 5;
 dish["name"] = "毛家红烧肉";
 dish["price"] = 2700;
 Json::Value dish_out;
 ret = dish_table.Update(dish);
 std::cout << "Update: " << ret << std::endl;
 ret = dish_table.SelectOne(5, &dish_out);
 std::cout << "SelectOne: " << ret << std::endl
 << writer.write(dish_out) << std::endl;
 std::cout << "==============测试删除=====================" << std::endl;
 int dish_id = 6;
 ret = dish_table.Delete(dish_id);
 std::cout << "Delete: " << ret << std::endl;
 mysqlrealse(mysql);
}
void TestOrderTable() {
 bool ret = false;
 Json::StyledWriter writer;
 MYSQL* mysql = mysqlinit();
 order_table order_table(mysql);
 std::cout << "==============测试插入=====================" << std::endl;
 Json::Value order;
 order["table_id"] = "忠义堂";
 order["time"] = "2019-05-17 12:00";
 order["dish_ids"] = "1,2,3";
 order["state"] = 0;
 ret = order_table.Insert(order);
 std::cout << "Insert: " << ret << std::endl;
 std::cout << "==============测试查看=====================" << std::endl;
 Json::Value orders;
 ret = order_table.Select(&orders);
 std::cout << "SelectAll: " << ret << std::endl
 << writer.write(orders) << std::endl;
 std::cout << "==============测试修改状态=====================" << std::endl;
 Json::Value state;
 state["order_id"] = 3;
 state["state"] = 1;
 ret = order_table.UpdateState(order);
 std::cout << "ChangeState ret:" << ret << std::endl;
 mysqlrealse(mysql);
}
int main() {
 TestDishTable();
 // TestOrderTable();
 return 0;
} 

