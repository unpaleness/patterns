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
  static std::shared_ptr<Singleton> GetInstance(const size_t value);
  size_t GetValue() const { return value_; }

 protected:
  Singleton(const size_t value) : value_(value) {
    std::cout << "Constructing Singleton with value " << value_ << '\n';
  }

 private:
  static std::shared_ptr<Singleton> singleton_ptr_;
  static std::mutex mutex_;
  size_t value_{0};
};

std::shared_ptr<Singleton> Singleton::singleton_ptr_;
std::mutex Singleton::mutex_;
std::shared_ptr<Singleton> Singleton::GetInstance(const size_t value) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!singleton_ptr_) {
    singleton_ptr_ = std::make_shared<Singleton>(value);
  }
  return singleton_ptr_;
}

void UseSingleton(const size_t thread_index) {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  const auto value = Singleton::GetInstance(thread_index)->GetValue();
  std::cout << "Thread: " << thread_index << ", Singleton value: " << value
            << '\n';
}

void ClientCode() {
  static const size_t amount_of_threads{10};
  std::cout << "Client creates " << amount_of_threads
            << " threads, all threads use singleton. Singleton will be "
               "initialized only in one of them.\n";
  std::array<std::unique_ptr<std::thread>, amount_of_threads> threads;
  for (size_t i = 0; i < amount_of_threads; ++i) {
    threads[i] = std::make_unique<std::thread>(UseSingleton, i + 1);
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
