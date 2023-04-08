[![Windows](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-windows.yml/badge.svg)](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-windows.yml) [![Ubuntu](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-ubuntu.yml/badge.svg)](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-ubuntu.yml) [![macOS](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-macos.yml/badge.svg)](https://github.com/eclipse-ecal/tcp_pubsub/actions/workflows/build-macos.yml)

# GPZDA via tcp_pubsub - TCP Publish/Subscribe library

# Environment
Distributor ID: Ubuntu
Description:    Ubuntu 18.04.6 LTS
Release:        18.04
Codename:       bionic


## How to checkout and build

There are several examples provided that aim to show you the functionality.

1. Install cmake and git / git-for-windows

2. Checkout this repo and the asio submodule
	```console
	https://github.com/davidkong-123/tcp_pubsub_NMEA.git
	cd tcp_pubsub
	git submodule init
	git submodule update
	```

3. CMake the project *(Building as debug will add some debug output)*
	```console
	mkdir _build
	cd _build
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
	```

4. Build the project
	- Linux: `make`

5. Start one publisher and several subscriber
  - `cd samples/` 
  - `./GPZDA_publisher/GPZDA_publisher` (one prompt for GPZDA_publisher)
  - `./GPZDA_subscriber/GPZDA_subscriber` (serveral prompts for GPZDA_subscriber)
