#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

#include "util/price.h"

class L3Book {
 public:
    void ProcessAdd(int64_t order_id, bool is_buy, double price, int64_t qty);
    void ProcessReplace(int64_t order_id, bool is_buy, double price, int64_t qty);
    void ProcessDelete(int64_t order_id);
    void ProcessExec(int64_t order_id, int64_t exec_qty);

 public:
    template <typename F>
    void ForEachLevel(F&& f) const {
        // TODO 
        /* f could be either a lambda function or a functor with the following function signature:
         * 
         * bool process_level(double bid_price, int64_t bid_qty, int64_t bid_count, 
         *                    double ask_price, int64_t ask_qty, int64_t ask_count);
         * 
         * NOTE: the return type of "f" is bool
         * -> true: continue the iteration if there's any more level
         * -> false: break the loop and stop the iteration
         * 
         * With the below event sequence, if f(99.0, 9, 3, 102.0, 11, 2) returns false, there should be no call with f( 0.0, 0, 0, 103.0, 12, 3)
         * Below is the sequence of events that should be delivered to f
         * - f(100.0, 10, 2, 101.0, 11, 3);
         * - f(99.0, 9, 3, 102.0, 11, 2);
         * - f( 0.0, 0, 0, 103.0, 12, 3);
         */ 
         
         //define max size to iterate through
        auto buyItr = buy_side_.begin();
        auto sellItr = sell_side_.begin();
        const size_t max = std::max(buy_side_.size(), sell_side_.size());

        for (size_t i = 0; i < max; i++){
            
            double bid_price = 0.0;
            int64_t bid_qty = 0;
            int64_t bid_count = 0;

            double ask_price = 0.0;
            int64_t ask_qty = 0;
            int64_t ask_count = 0;

            if (buyItr != buy_side_.end()) {
                bid_price = buyItr->second.price;
                bid_qty = buyItr->second.qty;
                bid_count = buyItr->second.count;
            }
            
            if (sellItr != sell_side_.end()) {
                ask_price = sellItr->second.price;
                ask_qty = sellItr->second.qty;
                ask_count = sellItr->second.count;
            }
            
            //break the loop and stop iteration
            if (!f(bid_price, bid_qty, bid_count, ask_price, ask_qty, ask_count)) 
                break;
            
            if (buyItr != buy_side_.end()) 
                buyItr++;
            
            if (sellItr != sell_side_.end()) 
                sellItr++;
        }
    }

    template <typename F>
    void ForEachOrder(bool is_buy, bool inner_to_outer, F&& f) const {
        // TODO 
        // check if inner_to_outer and iterate accordingly on buy and sell side
        if(is_buy) {
            if(inner_to_outer) {
                for (auto buyItr = buy_side_.begin(); buyItr != buy_side_.end(); buyItr++) {
                    for (auto pos = buyItr->second.orders.rbegin(); pos != buyItr->second.orders.rend(); pos++) {
                        f(is_buy, (double) buyItr->first, buyItr->second.qty, (*pos)->qty, (*pos)->order_id);
//                        f(is_buy, buyItr->first, buyItr->second.qty, (*pos)->qty, (*pos)->order_id);
                    }
                }
            }
        }
        
        else {
            if(!inner_to_outer) {
                for (auto sellItr = sell_side_.rbegin(); sellItr != sell_side_.rend(); sellItr++) {
                    
                    Level::Orders level_o = sellItr->second.orders;
                    for (Level::Orders::reverse_iterator revItr = level_o.rbegin(); revItr != level_o.rend(); revItr++){
                        f(is_buy,(double) sellItr->first, sellItr->second.qty, (*revItr)->qty, (*revItr)->order_id);
//                        f(is_buy, sellItr->first, sellItr->second.qty, (*revItr)->qty, (*revItr)->order_id);
                    }
                }
            }
        }  
    }

    // to uncross the book by removing any offensive orders from the given book side
    // - is_buy: true. If the sell side is newer, and any offensive orders on the buy side should be removed
    void UncrossBookSide(bool is_buy);

 private:
    struct Order;
    
    struct Level {
        using Orders = std::list<Order*>;

        Level(double price) : price(price), qty(0), count(0) {}

        Orders orders;
        double price;
        int64_t qty;
        int64_t count;
    };
    struct Order {
        Order(int64_t order_id, bool is_buy, double price, int64_t qty)
            : order_id(order_id), is_buy(is_buy), price(price), qty(qty) {} 

        int64_t order_id;
        bool is_buy;
        double price;
        int64_t qty;

        Level::Orders::iterator pos;        
        Level* level;
    };

    using BuySide = std::map<Price, Level, std::greater<Price>>;
    using SellSide = std::map<Price, Level, std::less<Price>>;
    using Orders = std::unordered_map<int64_t, Order>;

 private:
    Orders orders_;
    BuySide buy_side_;
    SellSide sell_side_;
};

// the requirement, the ops time complexity should be less than O(N), i.e. either O(1) or O(logN)

// OrderBook Update operation
// - add order: find the level and append to the level end 
// - update order: 
//   1) if priority is unchanged, update the qty inplace
//   2) if priority is changed, remove(order) and add(order)
// - delete order: find the level and remove from the level 

// OrderBook Query operation
// - iterate the levels up to some provide level count, to get the price, qty, ocount for each level.
// 
