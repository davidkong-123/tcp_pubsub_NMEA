// Copyright (c) Continental. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include <iostream>
#include <sstream>
#include <thread>

#include <tcp_pubsub/executor.h>
#include <tcp_pubsub/publisher.h>
#include <time.h>                                                               
#include <stdio.h> 

//  Customized checksum
int hash(std::string s){
    long long k = 7;
    for(int i = 0; i < s.length(); i++){
        k *= 23;
        k += s[i];
        k *= 13;
        k %= 1000000009;
    }
    return k;
}

int main()
{
  const std::shared_ptr<tcp_pubsub::Executor> executor = std::make_shared<tcp_pubsub::Executor>(6);

  int counter = 0;
  const tcp_pubsub::Publisher GPZDA_publisher(executor, 1588);
  time_t now;
  struct tm *tm;

  for (;;)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    now = time(0);
    if ((tm = localtime (&now)) == NULL) {
        printf ("Error extracting time stuff\n");
        return 1;
    }
    
    std::ostringstream oss;
    // 0. Topic
    oss << "GPZDA,";
    // 1. UTC time
    oss << tm->tm_hour << tm->tm_min << tm->tm_sec << ","; 
    // 2. Day, 01 to 31
    oss << tm->tm_mday << ",";
    // 3. Month, 01 to 12
    oss << tm->tm_mon+1 << ",";
    // 4. Year (4 digits)
    oss << tm->tm_year+1900 << ",";
    // 5. Local zone description, 00 to +- 13 hours
    oss << "00" << ",";
    // 6. Local zone minutes description, 00 to 59, apply same sign as local hours
    oss << "00" << "*";
    // 7. Checksum
    std::string gp_zda_data = oss.str();
    int check_sum = hash(gp_zda_data);
    gp_zda_data += std::to_string(check_sum);

    auto now = std::chrono::steady_clock::now();

    std::cout << "Sending " << gp_zda_data << std::endl;
    GPZDA_publisher.send(gp_zda_data.data(), gp_zda_data.size());
  }

  return 0;
}
