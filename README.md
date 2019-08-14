# Lamp Manager

Application to manage the lamp stack on Linux systems

Built with C++ and Qt

![Control Panel](https://i.imgur.com/WGxdxVL.png)

![Manage Virtual Hosts](https://i.imgur.com/juAjkOq.png)

## Requirements

This project requires Qt5 and the [meson build system](https://mesonbuild.com)

## Installation

To install lampman,

1. Clone or download the repository and open a terminal in the project folder

2. Install with meson and ninja
```
meson buildir
sudo ninja -C builddir
```

3. Run lampman
```
sudo lampman
```

