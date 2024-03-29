#include "pattern.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

namespace singleton {

namespace {

class Singleton {
public:
    Singleton(const Singleton& other) = delete;
    void operator=(const Singleton& other) = delete;
    static const Singleton* GetInstance(const size_t value);
    size_t GetValue() const { return value_; }

private:
    Singleton(const size_t value) : value_(value) {
        std::cout << "Constructing Singleton with value " << value_ << '\n';
    }

private:
    static const Singleton* singleton_ptr_;
    static std::mutex mutex_;
    size_t value_{0};
};

const Singleton* Singleton::singleton_ptr_;
std::mutex Singleton::mutex_;
const Singleton* Singleton::GetInstance(const size_t value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!singleton_ptr_) {
        singleton_ptr_ = new Singleton(value);
    }
    return singleton_ptr_;
}

void UseSingleton(const size_t thread_index,
                  std::shared_ptr<std::mutex> client_mutex) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    const auto value = Singleton::GetInstance(thread_index)->GetValue();
    {
        std::lock_guard<std::mutex> lock(*client_mutex);
        std::cout << "Thread: " << thread_index
                  << ", Singleton value: " << value << '\n';
    }
}

void ClientCode() {
    static const size_t amount_of_threads{4};
    auto client_mutex = std::make_shared<std::mutex>();
    std::cout << "Client creates " << amount_of_threads
              << " threads, all threads use singleton. Singleton will be "
                 "initialized only in one of them.\n";
    std::array<std::unique_ptr<std::thread>, amount_of_threads> threads;
    for (size_t i = 0; i < amount_of_threads; ++i) {
        threads[i] =
            std::make_unique<std::thread>(UseSingleton, i + 1, client_mutex);
    }
    for (auto& thread : threads) {
        thread->join();
    }
}

}  // namespace

void run() {
    std::cout << "\n=== Singleton ===\n\n";
    ClientCode();
    std::cout << '\n';
}

}  // namespace singleton
