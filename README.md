# misc-benchmarking
Notes and simple tools for benchmarking libvmm, unstable and experimental

## Build image for benchmarking libvmm on Odroidc4

### Prepare microkit and sel4 kernel

```
# this will track the seL4 microkit branch
git clone git@github.com:ZhanYF/seL4.git
cd seL4
git switch yifei/optimization 
cd -
git clone git@github.com:au-ts/microkit.git
cd microkit
git switch yifei/optimization
cd -
git clone git@github.com:au-ts/libvmm.git
cd libvmm
git switch yifei/optimization
cd -
```

## Build microkit and libvmm image, with the benchmark profile

```
cd microkit
# refers to README.md to setup pyenv...
./pyenv/bin/python build_sdk.py --sel4=../seL4 --skip-docs --skip-tar \
--boards odroidc4 --configs benchmark
```

```
cd libvmm/examples/simple
rm -r build; make MICROKIT_BOARD=odroidc4 MICROKIT_CONFIG=benchmark MICROKIT_SDK=../../../microkit/release/microkit-sdk-1.4.1/
```


## Boot the image on actual hardware (qemu is not cycle accurate)

```
mq run -c 'randomstr934ihwuefh' -s odroidc4_1 -f ./build/loader.img -l console.output
```


## Usage

To record cycle count at any point in libvmm, call ` sel4bench_record_cycle_count(int tag);`, by default the results will be printed the console after 2000 measurements, the number of samples and buffer size is defined in `libvmm/examples/simple/vmm.c`

## Example

See [measure.fault.md](measure.fault.md)
