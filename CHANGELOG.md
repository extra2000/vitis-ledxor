# Changelog

## [1.1.1](https://github.com/extra2000/vitis-ledxor/compare/v1.1.0...v1.1.1) (2022-08-16)


### Documentations

* **README:** allow non-root R/W access to GPIO and change to non-root systemd unit ([0128956](https://github.com/extra2000/vitis-ledxor/commit/01289566525a1d5b4926eaadccb6d81d48dab30f))

## [1.1.0](https://github.com/extra2000/vitis-ledxor/compare/v1.0.0...v1.1.0) (2022-08-02)


### Features

* **engine:** add shutdown feature to ensure mainloop properly exit ([c47dedc](https://github.com/extra2000/vitis-ledxor/commit/c47dedcbd30f1bb2c0470eae23e499ccca883c2a))


### Code Refactoring

* **engine.hpp:** remove unused LED namespace ([6a39118](https://github.com/extra2000/vitis-ledxor/commit/6a39118f539b7ca683f4fafecce043ff5f75ddf5))
* **engine:** reduce `event_wait()` duration from 10 seconds to 1 second ([0172ad8](https://github.com/extra2000/vitis-ledxor/commit/0172ad883ef07e394752b48a5c70a65a9f303085))
* **engine:** simplify event dumping into `print_event_info()` ([604c328](https://github.com/extra2000/vitis-ledxor/commit/604c32800fa62c4b49b7537d6856a66a0500b5e3))
* **main:** move the mainloop into a separate thread because the `event_wait()` is sleeping the thread which halts ASIO ([107e8c9](https://github.com/extra2000/vitis-ledxor/commit/107e8c9434e6b14e53d2c11aa76e4c98efcf81df))

## 1.0.0 (2022-08-02)


### Features

* initial implementations ([978167a](https://github.com/extra2000/vitis-ledxor/commit/978167ad20f33b2d45acde561c1bbc14165015ea))


### Documentations

* **README:** update `README.md` ([88eced7](https://github.com/extra2000/vitis-ledxor/commit/88eced7f5d8ea6c85f0b5fa3bbd0223bfb95e3c8))


### Continuous Integrations

* add AppVeyor with `semantic-release` ([82ad34d](https://github.com/extra2000/vitis-ledxor/commit/82ad34dd4c3ab9fd3978f6fe606cda9ad19f932b))
