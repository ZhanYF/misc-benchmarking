### Measure fault latency

By default vmm.c is configured to measure 2 things:

1. the latency from the guest Linux VM faulting, to VMM handling the fault with a custom fault handler
2. the latency from the seL4 kernel passed the fault to VMM, to VMM resolved to the custom fault handler

For 1, the VM first reads the cycle count, then trigger a fault which when delivered to VMM, will cause VMM to get the cycle count as well, by comparing the 2 cycle count we can find the latency.

For 2, the VMM records the cycle count when a virtual memory fault is delivered to it, and then records another cycle count by the time it has resolved to the custom fault handler, then by comparing the 2 cycle count we can find the latency.

#### Run

To run the benchmark, copy the measure.bin to the VM, either via packing a rootfs or via base64+gzip, run it from the guest, and it should do the benchmark and print out all the results.
