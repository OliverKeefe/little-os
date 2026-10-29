#pragma once
#ifdef VIRTIO_H
#define VIRTIO_H

#include "virtio_types.h"
#include "virtio_ids.h"
#include "virtio_config.h"
#include "virtio_mmio.h"
#include "virtio_ring.h"
#include "virtio_blk.h"
#include "../../common/common.h"

/*
 * Driver for virtio.
 * For reference see spec: https://docs.oasis-open.org/virtio/virtio/v1.3/csd01/virtio-v1.3-csd01.html
 */

#define VIRTIO_REG_MAGIC           0x00
#define VIRTIO_REG_VERSION         0x04
#define VIRTIO_REG_DEVICE_ID       0x08
#define VIRTIO_REG_DEVICE_STATUS   0x70
#define VIRTIO_REG_PAGE_SIZE       0x28
#define VIRTIO_REG_QUEUE_SEL       0x30
#define VIRTIO_REG_QUEUE_NUM_MAX   0x34
#define VIRTIO_REG_QUEUE_NUM       0x38
#define VIRTIO_REG_QUEUE_PFN       0x40
#define VIRTIO_REG_QUEUE_READY     0x44
#define VIRTIO_REG_QUEUE_NOTIFY    0x50
#define VIRTIO_REG_DEVICE_CONFIG   0x100

#define VIRTIO_STATUS_ACK          1
#define VIRTIO_STATUS_DRIVER_AVAIL 2
#define VIRTIO_STATUS_DRIVER_OK    4


struct virtio_blk {
    volatile uint32_t *regs;
    struct virtio_virtq *vq;
    uint64_t capacity;
};

void virtio_blk_init(void);
int virtio_blk_read(uint32_t sector, void *buf, uint32_t count);
int virtio_blk_write(uint32_t sector, const void *buf, uint32_t count);


// MMIO (Memory-Mapped I/O) Access Layer for the virtio device.

// virtio_reg_read32 casts address to a volatile uint32_t* and dereferences it, returning the value.
uint32_t virtio_reg_read32(unsigned offset);

// virtio_reg_read32 casts address to a volatile uint64_t* and dereferences it, returning the value.
uint64_t virtio_reg_read64(unsigned offset);

// virtio_reg_read32 casts address to a volatile uint32_t* and dereferences it, storing the value.
void virtio_reg_write32(unsigned offset, uint32_t value);

// Reads the register at `offset`, OR the bits in `value`, then write back to `offset`.
void virtio_reg_fetch_and_or32(unsigned offset, uint32_t value);