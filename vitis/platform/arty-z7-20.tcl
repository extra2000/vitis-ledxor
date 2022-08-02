platform create -name {ledxor} -hw {../vivado/run/ledxor/arty_z7_20_wrapper.xsa} -proc {ps7_cortexa9} -os {linux} -out {./}

platform write
platform active {ledxor}
domain config -bif {../petalinux/arty-z7-20/images/linux/bootgen.bif}
platform write
domain config -boot {../petalinux/arty-z7-20/images/linux}
platform write
domain config -image {../petalinux/arty-z7-20/images/linux}
platform write
domain config -sysroot {../petalinux/arty-z7-20/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi}
platform write
domain config -rootfs {../petalinux/arty-z7-20/images/linux/rootfs.cpio}
platform write
domain active {zynq_fsbl}
platform generate
