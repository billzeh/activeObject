//
// Created by William Zeh on 9/6/24.
//

#include <vector>

#include <gmock/gmock.h>

#include "activeObject/ActiveObject.h"

TEST(TestActiveObject, test)
{
    std::cout << "1: Begin Main" << std::endl;

    std::vector<int> order;
    order.push_back(1);
    {
        ActiveObject ao;
        ao.async([&]() {
            std::this_thread::sleep_for (std::chrono::seconds(1));
        });

        ao.async([&]() {
            order.push_back(3);
            std::cout << "3: Async first" << std::endl;
        });

        ao.async([&]() {
            order.push_back(4);
            std::cout << "4: Async second" << std::endl;
        });

        order.push_back(2);
        std::cout << "2: Pushed Async Work... " << std::endl;

        auto didBlock = ao.asyncAndBlock<bool>([&]() {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            order.push_back(5);
            return true;
        });
        order.push_back(6);
        std::cout << "5: Async last and blocked? " << (didBlock ? "True" : "False")
                  << std::endl;
    }
    std::cout << "6: End Main " << std::endl;
    ASSERT_THAT(order, ::testing::ElementsAre(1, 2, 3, 4, 5, 6));
}