// Copyright (c) Continental. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include <iostream>
#include <thread>

#include <tcp_pubsub/executor.h>
#include <tcp_pubsub/subscriber.h>

int main()
{
  const std::shared_ptr<tcp_pubsub::Executor> executor = std::make_shared<tcp_pubsub::Executor>(4);

  tcp_pubsub::Subscriber GPZDA_subscriber(executor);
  auto session1 = GPZDA_subscriber.addSession("127.0.0.1", 1588);

  const std::function<void(const tcp_pubsub::CallbackData& callback_data)>callback_function
        = [](const tcp_pubsub::CallbackData& callback_data) -> void
          {
            const std::string temp_string_representation(callback_data.buffer_->data(), callback_data.buffer_->size());
            std::cout << "Received playload: " << temp_string_representation << std::endl;
          };

  GPZDA_subscriber.setCallback(callback_function);
    
  // Prevent the application from exiting immediatelly
  for (;;) std::this_thread::sleep_for(std::chrono::milliseconds(500));

  return 0;
}
