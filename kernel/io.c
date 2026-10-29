#include "kernel.h"
#include "../drivers/virtio/virtio.h"
#include "../common/common.h"

struct virtio_virtq *blk_request_vq;
struct virtio_blk_req *blk_req;
paddr_t blk_req_paddr;
uint64_t blk_capacity;

// The device is reset (although this isn't required on initial start up).
void reset_io_device(const unsigned reg_device_status, const uint32_t status) {
    virtio_reg_write32(reg_device_status, status);
}

// The ACKNOWLEDGE status bit is set, signifying kernel recognizes new device.
void acknowledge_device(const unsigned reg_device_status, const uint32_t status) {
    virtio_reg_fetch_and_or32(reg_device_status, status);
}

// the DRIVER_AVAIL bit is set signifying the driver is present and device drivable.
void get_driver(const unsigned reg_device_status, uint32_t status) {
    virtio_reg_fetch_and_or32(reg_device_status, status);
}

// Allocate page size for virtio device.
void set_device_page(const size_t reg_page_size, const size_t page_size) {
    virtio_reg_write32(reg_page_size, page_size);
}

// DRIVER_OK status bit set, ready to go.
void set_driver_ok(const unsigned reg_device_status, uint32_t status) {
    virtio_reg_write32(reg_device_status, status);
}

/**
 * virtio_blk_init handles the initialization process of a virtio device.
 */
void virtio_blk_init(void) {
    if (virtio_reg_read32(VIRTIO_REG_MAGIC) != 0x74726976)
        PANIC("virtio: invalid magic value");
    if (virtio_reg_read32(VIRTIO_REG_VERSION) != 1)
        PANIC("virtio: invalid version");
    if (virtio_reg_read32(VIRTIO_REG_VERSION) != 1)
        PANIC("virtio: invalid device id");

    reset_io_device(VIRTIO_REG_DEVICE_STATUS, 0);
    acknowledge_device(VIRTIO_REG_DEVICE_STATUS, VIRTIO_STATUS_ACK);
    get_driver(VIRTIO_REG_DEVICE_STATUS, VIRTIO_STATUS_DRIVER_AVAIL);

    /*
     * Device specific setup, including Device Feature Bites, virtqueue discovery, MSI-X
     * setup (if required) and reading and writing to the virtio config space.
     */
    set_device_page(VIRTIO_REG_PAGE_SIZE, PAGE_SIZE);
    blk_request_vq = virtq_init(0);
    set_driver_ok(VIRTIO_REG_DEVICE_STATUS, VIRTIO_STATUS_DRIVER_OK);


    blk_capacity = virtio_reg_read64(VIRTIO_REG_DEVICE_CONFIG + 0) * SECTOR_SIZE;
    printf("virtio-blk: capcity is %d bytes\n", (int)blk_capacity);

    blk_req_paddr = alloc_pages(align_up(sizeof(*blk_req), PAGE_SIZE) / PAGE_SIZE);
    blk_req = (struct virtio_blk_req *) blk_req_paddr;

}