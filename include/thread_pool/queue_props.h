#pragma once

#include <algorithm>

namespace dp {

struct queue_props final{
    enum class overflow_action { DISCARD_OLDEST, DISCARD_NEWEST };
private:
    size_t queue_size_;
    overflow_action overflow_action_;
    bool notify_;
public:
    queue_props():
        queue_size_{0}, 
        overflow_action_{overflow_action::DISCARD_NEWEST}, 
        notify_{false} 
    {}
    queue_props(size_t queueSize, bool notify=false):
        queue_size_{queueSize},
        overflow_action_{overflow_action::DISCARD_NEWEST},
        notify_{notify}
    {}
    queue_props(size_t queueSize, overflow_action overflowAction, bool notify=false):
        queue_size_{queueSize},
        overflow_action_{overflowAction},
        notify_{notify}
    {}

    bool will_notify() const { return notify_; }
    bool is_infinite() const { return queue_size_ == 0; }
    bool no_queue() const { return queue_size_ == 1; }
    size_t get_queue_size() const { return queue_size_; }
    overflow_action get_overflow_action() const { return overflow_action_; }
    size_t num_threads(size_t requested) const { return overflow_action_ == overflow_action::DISCARD_OLDEST ? std::min((size_t)1,requested) : requested; }
};

}  // namespace dp
