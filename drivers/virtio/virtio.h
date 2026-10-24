#pragma once
#ifdef VIRTIO_H
#define VIRTIO_H

#include "virtio_types.h"
#include "virtio_ids.h"
#include "virtio_config.h"
#include "virtio_mmio.h"
#include "virtio_ring.h"
#include "virtio_blk.h"

/*
 * Driver for virtio.
 * For reference see spec: https://docs.oasis-open.org/virtio/virtio/v1.3/csd01/virtio-v1.3-csd01.html
 */


struct virtio_blk {
    volatile uint32_t *regs;
    struct virtio_virtq *vq;
    uint64_t capacity;
};

void virtio_blk_init(void);
int virtio_blk_read(uint32_t sector, void *buf, uint32_t count);
int virtio_blk_write(uint32_t sector, const void *buf, uint32_t count);

#endif // VIRTIO_H