# Lamp Manager

Application to manage the lamp stack on Linux systems

Built with C++ and Qt

![Control Panel](https://i.imgur.com/WGxdxVL.png)

![Manage Virtual Hosts](https://i.imgur.com/juAjkOq.png)

## Requirements

This project requires Qt5 

## Installation

To install lampman,

1. Clone or download the repository and open a terminal in the project folder

2. Compile using cmake
```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install
```

3. Run lampman
```
lampman
```

