# liblogger
a simple, elegant log library written in C.

## building
### debug
```
meson setup build --prefix=/usr/local
ninja -C build install
```

### release
```
meson setup build --prefix=/usr --buildtype=release
ninja -C build install
```

### archlinux (aur)
so first install yay/paru  
```
pacman -Syu
yay -S liblogger
```

## usage
check [DOCS.md](DOCS.md)