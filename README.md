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

## usage
check [DOCS.md](DOCS.md)